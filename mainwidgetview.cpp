#include "mainwidgetview.h"

MainWidgetView::MainWidgetView(QString path, QWidget *parent) : QWidget(parent)
{
  circuit = new Circuit(path);
  this->initView();
}

MainWidgetView::MainWidgetView(CircuitSettings settings, QWidget *parent) : QWidget(parent)
{
  circuit = new Circuit(settings);
  this->initView();
}

MainWidgetView::~MainWidgetView()
{
  delete circuit;
  delete statusBar;
  delete toolBar;
  delete rightWidget;
  delete scroll;
}

void MainWidgetView::initView()
{
  this->initToolbar();

  vBox = new QVBoxLayout(this);
  layoutCointerner = new QWidget();
  vBox->addWidget(layoutCointerner, 100);
  statusBar = new StatusBar();
  vBox->addWidget(statusBar);
  hBox = new QHBoxLayout(layoutCointerner);
  hBox->addWidget(toolBar);
  scroll = new ScrollArea();
  scroll->setWidget(circuit);
  hBox->addWidget(scroll, 100);
  rightWidget = new RightWidget(circuit);
  hBox->addWidget(rightWidget);

  hBox->setContentsMargins(0,0,0,0);
  vBox->setContentsMargins(0,0,0,0);
}

void MainWidgetView::initToolbar()
{
  toolBar = new QToolBar(tr("Tools"));
  toolBar->setOrientation(Qt::Vertical);
  ac = new QActionGroup(toolBar);

  selectA = new QAction(K::pointerI, tr("Select"), ac);
  resistorA = new QAction(K::resistorI, tr("Resitor"), ac);

  selectA->setCheckable(true);
  resistorA->setCheckable(true);

  selectA->setChecked(true);

  toolBar->addActions({selectA, resistorA});
}

