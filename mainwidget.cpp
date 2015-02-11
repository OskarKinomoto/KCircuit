#include "mainwidget.h"

MainWidget * MainWidget::MAIN_WIDGET;

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
  vBox = new QVBoxLayout();

  tabWidget = new QTabWidget();
  tabWidget->setTabsClosable(true);
  tabWidget->setMovable(true);
  tabWidget->setDocumentMode(true);

  connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
  connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changedIndex(int)));

  statusBar = new QLabel(tr("TODO"));
  vBox->addWidget(tabWidget,1);
  vBox->addWidget(statusBar);
  this->setLayout(vBox);

  MAIN_WIDGET = this;
}

MainWidget::~MainWidget()
{

}

int MainWidget::newTab(Circuit *circuit)
{
  if(!circuit) throw QString(QString("nullptr in ") + __FILE__ + " line " + QString(__LINE__));
  CircuitScrollArea * c = new CircuitScrollArea(circuit, tabWidget);

  for(int i = 0; i < tabWidget->count(); ++i)
    {
      if(((CircuitScrollArea*)tabWidget->widget(i))->circuitWidget->isNew())
        closeTabI(i);
    }


  int i = tabWidget->addTab(c, circuit->name());
  tabWidget->setCurrentIndex(i);

  c->setMouseTrackingCircuit(mouseTracking);

  return i;
}

void MainWidget::setMouseTrackingOnTabs(bool enable)
{
  mouseTracking = enable;
  for(int i = 0; i < tabWidget->count(); ++i)
    {
      ((CircuitScrollArea*)tabWidget->widget(i))
          ->setMouseTrackingCircuit(enable);
    }
}

void MainWidget::updateCurrent()
{
  ((CircuitScrollArea*)tabWidget->currentWidget())->widget()->update();
}

void MainWidget::setName(QString name, CircuitScrollArea *w)
{
  tabWidget->setTabText(tabWidget->indexOf(w), name);
}

void MainWidget::closeTabI(int i)
{
  tabWidget->removeTab(i);
}

void MainWidget::closeTab(int i)
{
  if(((CircuitScrollArea*)tabWidget->widget(i))->circuitWidget)
    tabWidget->removeTab(i);
  if(!tabWidget->count()) this->newTab(new Circuit());
}

void MainWidget::changedIndex(int i)
{
  if(i > -1)
    this->getCurrent()->circuitWidget->updateInfoBox();
}

void MainWidget::rotate()
{
  this->getCurrent()->circuitWidget->rotate();
}

void MainWidget::smallRotate()
{
  this->getCurrent()->circuitWidget->smallRotate();
}



