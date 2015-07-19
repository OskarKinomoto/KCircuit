#include "tabwidget.h"

TabWidget::TabWidget() {
  K::tabWidget = this;
  this->newDefaultTab();
  this->setTabsClosable(true);
  this->setMovable(true);
  this->setDocumentMode(true);

  connect(this->tabBar(), SIGNAL(tabMoved(int, int)), this,
          SLOT(tabMoved(int, int)));
  connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
}

TabWidget::~TabWidget() {}

void TabWidget::setName(QString name, int index) {
  this->setTabText(index, name);
}

Circuit *TabWidget::circuit() {
  return static_cast<MainWidget *>(this->currentWidget())->circuit;
}

void TabWidget::newDefaultTab() {
  MainWidget *w = new MainWidget(CircuitSettings::base());
  int i = this->addTab(w, "");
  w->setIndex(i);
  this->setCurrentIndex(i);
  w->circuit->updateTitle();
}

void TabWidget::newTab(QString path) {
  MainWidget *w = new MainWidget(path);
  int i = this->addTab(w, "");
  w->setIndex(i);
  this->setCurrentIndex(i);
  w->circuit->updateTitle();

  auto c = static_cast<MainWidget *>(this->widget(i - 1))->circuit;
  if (!c->hasPath() && !c->isModyfied()) {
    this->removeTab(i - 1);
    this->updateIndex();
  }
}

bool TabWidget::save() {
  if (circuit()->hasPath())
    circuit()->save();
  else {
    QString fileName = QFileDialog::getSaveFileName(
        this->parentWidget(), tr("Save as..."), K::home + "/KCircuit/SAMPLE/",
        tr("KCircuit File (*.ktc)"), 0, QFileDialog::DontUseNativeDialog);
    if (fileName == "")
      return false;
    circuit()->saveAs(fileName);
  }
  return true;
}

void TabWidget::saveAs() {
  QString fileName = QFileDialog::getSaveFileName(
      this->parentWidget(), tr("Save as..."), K::home + "/KCircuit/SAMPLE/",
      tr("KCircuit File (*.ktc)"), 0, QFileDialog::DontUseNativeDialog);
  if (fileName == "")
    return;
  circuit()->saveAs(fileName);
}

void TabWidget::saveAll() {
  int index = this->currentIndex();
  for (int i = 0; i < this->count(); ++i) {
    this->setCurrentIndex(i);
    this->save();
  }
  this->setCurrentIndex(index);
}

void TabWidget::changeTitle(QString title, int index) {
  this->setTabText(index, title);
}

void TabWidget::open() {
  QString fileName = QFileDialog::getOpenFileName(
      this->parentWidget(), tr("Save as..."), K::home + "/KCircuit/SAMPLE/",
      tr("KCircuit File (*.ktc)"), 0, QFileDialog::DontUseNativeDialog);
  if (fileName == "")
    return;
  try {
    this->newTab(fileName);
  } catch (QString &s) {
    QMessageBox::warning(this, tr("KCircuit"), s, QMessageBox::Ok,
                         QMessageBox::Ok);
  }
}

bool TabWidget::closeTab(int i, bool *saveAll, bool close) {
  if (static_cast<MainWidget *>(this->widget(i))->circuit->isModyfied()) {
    this->setCurrentIndex(i);
    int ret;
    if (!(*saveAll)) {
      QMessageBox msgBox;
      msgBox.setText(
          tr("<center><h3>The document has been modified.</h3></center>"));
      msgBox.setInformativeText(
          tr("<center>Do you want to save your changes?</center>"));
      if (close && this->count() != 1) {
        msgBox.setStandardButtons(QMessageBox::SaveAll | QMessageBox::Save |
                                  QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::SaveAll);
      } else {
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard |
                                  QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
      }
      ret = msgBox.exec();
    } else {
      ret = QMessageBox::SaveAll;
    }
    switch (ret) {
    case QMessageBox::Save:
      if (!this->save())
        return false;
      break;
    case QMessageBox::Discard:
      break;
    case QMessageBox::Cancel:
      return false;
      break;
    case QMessageBox::SaveAll:
      if (!this->save())
        return false;
      *saveAll = true;
      return true;
      break;
    }
  }

  auto w = static_cast<MainWidget *>(this->widget(i));

  if (!close) {
    this->removeTab(i);
    if (this->count() == 0)
      this->newDefaultTab();
    updateIndex();
    delete saveAll;
    delete w;
  }
  return true;
}

bool TabWidget::closeAllTab() {
  auto b = new bool(false);
  for (int i = 0; i < this->count(); ++i)
    if (!this->closeTab(i, b, true))
      return false;
  return true;
}

void TabWidget::zoomIn() {
  static_cast<MainWidget *>(this->currentWidget())->scroll->zoom(true);
}

void TabWidget::zoomOut() {
  static_cast<MainWidget *>(this->currentWidget())->scroll->zoom(false);
}

void TabWidget::tabMoved(int, int) { this->updateIndex(); }

void TabWidget::updateIndex() {
  for (int i = 0; i < this->count(); ++i)
    static_cast<MainWidget *>(this->widget(i))->circuit->setIndex(i);
}
