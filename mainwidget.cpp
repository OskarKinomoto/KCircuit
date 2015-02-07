#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
  vBox = new QVBoxLayout();

  tabWidget = new QTabWidget();
  tabWidget->setTabsClosable(true);
  tabWidget->setMovable(true);
  tabWidget->setDocumentMode(true);

  connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

  statusBar = new QLabel(tr("TODO"));
  vBox->addWidget(tabWidget,1);
  vBox->addWidget(statusBar);
  this->setLayout(vBox);
}

MainWidget::~MainWidget()
{

}

int MainWidget::newTab(Circuit *circuit)
{
  if(!circuit) throw std::string("nullptr in MainWidget::newTab");

  for(int i = 0; i < tabWidget->count(); ++i)
    {
      if(((CircuitScrollArea*)tabWidget->widget(i))->circuitWidget->isNew())
        closeTabI(i);
    }

  int i = tabWidget->addTab(new CircuitScrollArea(circuit, tabWidget), circuit->name());
  tabWidget->setCurrentIndex(i);

  ((CircuitScrollArea*)tabWidget->widget(i))
      ->setMouseTrackingCircuit(mouseTracking);

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

void MainWidget::closeTabI(int i)
{
  tabWidget->removeTab(i);
}

void MainWidget::closeTab(int i)
{
  /// TODO ask save/cancel/don't save
  if(((CircuitScrollArea*)tabWidget->widget(i))->circuitWidget)
  tabWidget->removeTab(i);
  if(!tabWidget->count()) this->newTab(new Circuit());
}

void MainWidget::rotate()
{
  this->getCurrent()->circuitWidget->rotate();
}

void MainWidget::smallRotate()
{
  this->getCurrent()->circuitWidget->smallRotate();
}



