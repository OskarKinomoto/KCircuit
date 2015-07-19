#include "mainwidget.h"

MainWidget::MainWidget(CircuitSettings settings) : MainWidgetView(settings) {
  this->init();
}

MainWidget::MainWidget(QString path) : MainWidgetView(path) { this->init(); }

MainWidget::~MainWidget() {}

void MainWidget::setIndex(int index) { circuit->setIndex(index); }

void MainWidget::setPointer() { circuit->setTool(K::tool::POINTER); }

void MainWidget::setWire() { circuit->setTool(K::tool::WIRE); }

void MainWidget::setResistor() { circuit->setTool(K::tool::RESISTOR); }

void MainWidget::setCoil() { circuit->setTool(K::tool::COIL); }

void MainWidget::setCapacitor() { circuit->setTool(K::tool::CAPACITOR); }

void MainWidget::init() {
  connect(scroll, SIGNAL(scale(bool)), circuit, SLOT(scale(bool)));
  connect(selectA, SIGNAL(triggered()), this, SLOT(setPointer()));
  this->setPointer();
  connect(resistorA, SIGNAL(triggered()), this, SLOT(setResistor()));
  connect(wireA, SIGNAL(triggered()), this, SLOT(setWire()));
  connect(coilA, SIGNAL(triggered()), this, SLOT(setCoil()));
  connect(capacitorA, SIGNAL(triggered()), this, SLOT(setCapacitor()));
  connect(circuit, SIGNAL(moveMiddle(int, int)), scroll,
          SLOT(scrollMiddle(int, int)));
  connect(circuit, SIGNAL(centering()), scroll, SLOT(centering()));
  connect(circuit, SIGNAL(updatedSize()), scroll, SLOT(updatePosition()));
}
