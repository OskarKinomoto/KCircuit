#include "mainwindow.h"

#define STOP_ACTION if(this->mainWidget->getCurrent()->circuitWidget->grabedMouse && _selectedTool == K::WIRE) return;

K::tool MainWindow::_selectedTool = K::MOUSE;
InfoWidget * MainWindow::infoWidget = nullptr;

#if defined(_MSC_VER) || defined(__clang__)
bool Circuit::showGrid = true;
#else
extern bool Circuit::showGrid;
#endif

#define infoWidgetSize 100

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  initFonts();
  initIcons();
  loadSettings();
  initWidgets();
  initActions();
  initMenus();
  initToolBars();
  initDialogs();

  //After everything open new file
  newFileInit();
}

MainWindow::~MainWindow()
{
  delete newFileAction;
  delete saveFileAction;
  delete saveFileAsAction;
  delete openFileAction;
  delete exportToAction;
  delete quitAction;
  delete mouseSelectAction;
  delete wireSelectAction;
  delete resistorSelectAction;
  delete coilSelectAction;
  delete capacitorSelectAction;
  delete VDCSelectAction;
  delete ADCSelectAction;
  delete diodeSelectAction;
  delete generatorSelectAction;
  delete opAmpSelectAction;
  delete zoomInAction;
  delete zoomInAction2;
  delete zoomInAction3;
  delete zoomOutAction;
  delete showGridAction;
  delete rotateAction;
  delete smallRotateAction;
  delete aboutApplicationAction;
  delete fileMenu;
  delete editMenu;
  delete viewMenu;
  delete helpMenu;
  delete applicationBar;
  delete toolBar;
  delete aboutDialog;
}

void MainWindow::initWidgets()
{
  splitter = new QSplitter();
  mainWidget = new MainWidget(splitter);
  infoWidget = new InfoWidget(splitter);
  splitter->setCollapsible(0, false);
  splitter->setCollapsible(1, false);
  splitter->setStretchFactor(0, 10);
  splitter->setStretchFactor(1, 0);
  splitter->setSizes(QList<int>({splitter->width() - infoWidgetSize,infoWidgetSize}));
  this->setCentralWidget(splitter);
}

void MainWindow::initIcons()
{
  appIcon = QIcon(":/icons/app.svg");
  this->setWindowIcon(appIcon);

  wireIcon = QIcon(":/icons/wire.svg");
  resistorIcon = QIcon(":/icons/R.svg");
  coilIcon = QIcon(":/icons/L.svg");
  capacitorIcon = QIcon(":/icons/C.svg");
  diodeIcon = QIcon(":/icons/diode.svg");
  sineIcon = QIcon(":/icons/sine.svg");
  vdcIcon = QIcon(":/icons/vdc.svg");
  adcIcon = QIcon(":/icons/adc.svg");
  opampIcon = QIcon(":/icons/opamp.svg");
  pointerIcon = QIcon(":/icons/pointer.svg");
}

void MainWindow::initActions()
{
  //newFileAction
  newFileAction = new QAction(QIcon::fromTheme("document-new"), tr("&New..."), nullptr);
  newFileAction->setShortcut(QKeySequence::New);
  connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

  //openFileAction
  openFileAction = new QAction(QIcon::fromTheme("document-open"), tr("&Open"), nullptr);
  openFileAction->setShortcut(QKeySequence::Open);
  connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

  //saveFileAction
  saveFileAction = new QAction(QIcon::fromTheme("document-save"), tr("&Save"), nullptr);
  saveFileAction->setShortcut(QKeySequence::Save);
  connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));

  //exportToAction
  exportToAction = new QAction(tr("&Export to..."), nullptr);
  connect(exportToAction, SIGNAL(triggered()), this, SLOT(exportFile()));

  //saveFileAsAction
  saveFileAsAction = new QAction(QIcon::fromTheme("document-save-as"), tr("Save as"), nullptr);
  saveFileAsAction->setShortcut(QKeySequence::SaveAs);
  connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAs()));

  //quitAction
  quitAction = new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), nullptr);
  quitAction->setShortcut(QKeySequence::Quit);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(quit()));

  //mouseSelectAction
  mouseSelectAction = new QAction(pointerIcon, tr("Mouse"), nullptr);
  mouseSelectAction->setCheckable(true);
  mouseSelectAction->setChecked(true);
  connect(mouseSelectAction, SIGNAL(triggered()), this, SLOT(mouseSelect()));

  //wireSelectAction
  wireSelectAction = new QAction(wireIcon, tr("Wire"), nullptr);
  wireSelectAction->setCheckable(true);
  connect(wireSelectAction, SIGNAL(triggered()), this, SLOT(wireSelect()));

  //resistorSelectAction
  resistorSelectAction = new QAction(resistorIcon, tr("Resistor"), nullptr);
  resistorSelectAction->setCheckable(true);
  connect(resistorSelectAction, SIGNAL(triggered()), this, SLOT(resistorSelect()));

  //coilSelectAction
  coilSelectAction = new QAction(coilIcon, tr("Coil"), nullptr);
  coilSelectAction->setCheckable(true);
  connect(coilSelectAction, SIGNAL(triggered()), this, SLOT(coilSelect()));

  //capacitorSelectAction
  capacitorSelectAction = new QAction(capacitorIcon, tr("Capacitor"), nullptr);
  capacitorSelectAction->setCheckable(true);
  connect(capacitorSelectAction, SIGNAL(triggered()), this, SLOT(capacitorSelect()));

  //VDCSelectAction
  VDCSelectAction = new QAction(vdcIcon, tr("VDC"), nullptr);
  VDCSelectAction->setCheckable(true);
  connect(VDCSelectAction, SIGNAL(triggered()), this, SLOT(VDCSelect()));

  //ADCSelectAction
  ADCSelectAction = new QAction(adcIcon, tr("ADC"), nullptr);
  ADCSelectAction->setCheckable(true);
  connect(ADCSelectAction, SIGNAL(triggered()), this, SLOT(ADCSelect()));

  //diodeSelectAction
  diodeSelectAction = new QAction(diodeIcon, tr("Diode"), nullptr);
  diodeSelectAction->setCheckable(true);
  connect(diodeSelectAction, SIGNAL(triggered()), this, SLOT(diodeSelect()));

  //generatorSelectAction
  generatorSelectAction = new QAction(sineIcon, tr("Generator"), nullptr);
  generatorSelectAction->setCheckable(true);
  connect(generatorSelectAction, SIGNAL(triggered()), this, SLOT(generatorSelect()));

  //opAmpSelectAction
  opAmpSelectAction = new QAction(opampIcon, tr("Operational Amplifier"), nullptr);
  opAmpSelectAction->setCheckable(true);
  connect(opAmpSelectAction, SIGNAL(triggered()), this, SLOT(opAmpSelect()));

  //aboutAction
  aboutApplicationAction = new QAction(QIcon::fromTheme("help-about"), tr("About"), nullptr);
  connect(aboutApplicationAction, SIGNAL(triggered()), this, SLOT(aboutApplication()));

  //showGridAction
  showGridAction = new QAction(tr("Show grid"), nullptr);
  showGridAction->setCheckable(true);
  QSettings set;
  Circuit::showGrid = set.value("showgrid", true).toBool();
  showGridAction->setChecked(Circuit::showGrid);
  connect(showGridAction, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));

  //zoomInAction
  zoomInAction = new QAction(QIcon::fromTheme("zoom-in"), tr("Zoom in"), nullptr);
  zoomInAction2 = new QAction(QIcon::fromTheme("zoom-in"), tr("Zoom in"), nullptr);
  zoomInAction3 = new QAction(QIcon::fromTheme("zoom-in"), tr("Zoom in"), nullptr);
  zoomInAction->setShortcut(QKeySequence::ZoomIn);
  zoomInAction2->setShortcut(QKeySequence(QString("ctrl+=")));
  ///zoomInAction3->setShortcut(QKeySequence(Qt::Key_1));
  connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
  connect(zoomInAction2, SIGNAL(triggered()), this, SLOT(zoomIn()));
  connect(zoomInAction3, SIGNAL(triggered()), this, SLOT(zoomIn()));
  this->addAction(zoomInAction2);
  this->addAction(zoomInAction3);

  //zoomOutAction
  zoomOutAction = new QAction(QIcon::fromTheme("zoom-out"), tr("Zoom out"), nullptr);
  zoomOutAction->setShortcut(QKeySequence::ZoomOut);
  connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

  rotateAction = new QAction(QIcon::fromTheme("object-rotate-right"), tr("Rotate 90°"), nullptr);
  rotateAction->setShortcut(tr("R"));
  this->addAction(rotateAction);
  connect(rotateAction, SIGNAL(triggered()), mainWidget, SLOT(rotate()));

  smallRotateAction = new QAction(QIcon::fromTheme("object-rotate-right"), tr("Rotate 45°"), nullptr);
  smallRotateAction->setShortcut(tr("Alt+R"));
  this->addAction(smallRotateAction);
  connect(smallRotateAction, SIGNAL(triggered()), mainWidget, SLOT(smallRotate()));

  undoAction = new QAction(QIcon::fromTheme("edit-undo"), tr("Undo"), nullptr);
  undoAction->setShortcut(QKeySequence::Undo);
  connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));

  redoAction = new QAction(QIcon::fromTheme("edit-redo"), tr("Redo"), nullptr);
  redoAction->setShortcut(QKeySequence::Redo);
  connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));

}

void MainWindow::initMenus()
{
  //fileMenu
  fileMenu = this->menuBar()->addMenu(tr("&File"));
  fileMenu->addActions({newFileAction, openFileAction, saveFileAction, saveFileAsAction});
  fileMenu->addSeparator();
  fileMenu->addAction(exportToAction);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAction);

  //editMenu
  editMenu = this->menuBar()->addMenu(tr("&Edit"));
  editMenu->addActions({undoAction, redoAction});

  //viewMenu
  viewMenu = this->menuBar()->addMenu(tr("&View"));
  viewMenu->addActions({zoomInAction, zoomOutAction});
  viewMenu->addSeparator();
  viewMenu->addAction(showGridAction);

  //helpMenu
  helpMenu = this->menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutApplicationAction);
}

void MainWindow::loadSettings()
{
  this->setFocusPolicy(Qt::WheelFocus);
  QSettings settings;
  settings.beginGroup("MainWindow");
  this->resize(settings.value("size", QSize(800, 600)).toSize());
  this->move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();

  QApplication::setDoubleClickInterval(300);
}

void MainWindow::saveSettings()
{
  QSettings settings;
  settings.beginGroup("MainWindow");
  settings.setValue("size", this->size());
  settings.setValue("pos", this->pos());
  settings.endGroup();
}

void MainWindow::initToolBars()
{
  applicationBar = new QToolBar(tr("application"));
  applicationBar->setMovable(false);
  applicationBar->addActions({newFileAction, openFileAction, saveFileAction});
  applicationBar->addSeparator();
  applicationBar->addActions({undoAction, redoAction});
  applicationBar->addSeparator();
  applicationBar->addActions({zoomInAction, zoomOutAction});
  this->addToolBar(Qt::TopToolBarArea, applicationBar);

  toolBar = new QToolBar(tr("items")); ///TODO nazwa :<
  toolBar->setMovable(false);
  toolBar->addAction(mouseSelectAction);
  toolBar->addAction(wireSelectAction);
  toolBar->addAction(resistorSelectAction);
  toolBar->addAction(coilSelectAction);
  toolBar->addAction(capacitorSelectAction);
  toolBar->addAction(diodeSelectAction);
  toolBar->addAction(VDCSelectAction);
  toolBar->addAction(ADCSelectAction);
  toolBar->addAction(generatorSelectAction);
  toolBar->addAction(opAmpSelectAction);
  this->addToolBar(Qt::LeftToolBarArea, toolBar);
}

void MainWindow::infoUpdate(Circuit * c)
{
  infoWidget->update(c);
}

void MainWindow::infoAdd(K::info info)
{
  infoWidget->addInfo(info);
}

void MainWindow::unselectLastUsed()
{
  switch(_selectedTool)
    {
    case K::MOUSE: mouseSelectAction->setChecked(false);
      break;

    case K::WIRE: wireSelectAction->setChecked(false);
      break;

    case K::RESISTOR: resistorSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::CAPACITOR: capacitorSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::COIL: coilSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::VDC: VDCSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::ADC: ADCSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::DIODE: diodeSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::GENERATOR: generatorSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    case K::OPAMP: opAmpSelectAction->setChecked(false);
      this->mainWidget->getCurrent()->circuitWidget->destroyDrawingObject();
      break;

    }
}

void MainWindow::initDialogs()
{
  // about dialog
  aboutDialog = new AboutDialog(nullptr);
}

void MainWindow::initFonts()
{
  QFontDatabase::addApplicationFont(":/fonts/oxygen.otf");
  CircuitOpAmp::oxy = QFont("Oxygen");
}

void MainWindow::newFile()
{
  STOP_ACTION
      this->mainWidget->newTab(new Circuit());
}

void MainWindow::newFileInit()
{
  this->mainWidget->newTab(new Circuit());
}

void MainWindow::saveFile()
{
  STOP_ACTION
      auto circ = this->mainWidget->getCurrent()->circuitWidget;

  if(circ->hasPath())
    {
      circ->saveFile();
      return;
    }

  QString fileName = QFileDialog::getSaveFileName(this, tr("Save..."), "/home/oskar/KCircuit/SAMPLE/", tr("KCircuit File (*.qtc)"), 0, QFileDialog::DontUseNativeDialog);
  if(fileName == "") return;
  circ->saveFileAs(fileName);
}

void MainWindow::saveFileAs()
{
  STOP_ACTION
      auto circ = this->mainWidget->getCurrent()->circuitWidget;
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "/home/oskar/KCircuit/SAMPLE/", tr("KCircuit File (*.qtc)"), 0, QFileDialog::DontUseNativeDialog);
  if(fileName == "") return;
  circ->saveFileAs(fileName);
}

void MainWindow::openFile()
{
  STOP_ACTION
      QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "/home/oskar/KCircuit/SAMPLE/", tr("KCircuit File (*.qtc)\n All files (*.*)"), 0, QFileDialog::DontUseNativeDialog);
  if(fileName == "") return;
  try{
    this->mainWidget->newTab(new Circuit(fileName));
  } catch(QString &s) {
    QMessageBox::warning(this, tr("KCircuit"), s, QMessageBox::Ok, QMessageBox::Ok);
  }
}

void MainWindow::exportFile()
{
  STOP_ACTION
      QString fileName = QFileDialog::getSaveFileName(this, tr("Export to..."), "/home/oskar/Qt/KCircuit/SAMPLE/", tr("PNG image (*.png)"), 0, QFileDialog::DontUseNativeDialog);
  if(fileName == "") return;
  auto type = QFileInfo(fileName).completeSuffix();
  if(type == "png") // export to png
    {
      this->mainWidget->getCurrent()->circuitWidget->exportToPNG(fileName);
    }
  else if(type == "")
    {this->mainWidget->getCurrent()->circuitWidget->exportToPNG(fileName+".png");

    }
}

void MainWindow::quit()
{
  saveSettings();
  QApplication::quit();
}

void MainWindow::wireSelect()
{
  STOP_ACTION
      unselectLastUsed();
  wireSelectAction->setChecked(true);
  _selectedTool = K::WIRE;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::mouseSelect()
{
  STOP_ACTION
      unselectLastUsed();
  mouseSelectAction->setChecked(true);
  _selectedTool = K::MOUSE;
  mainWidget->setMouseTrackingOnTabs(false);
}

void MainWindow::resistorSelect()
{
  STOP_ACTION
      unselectLastUsed();
  resistorSelectAction->setChecked(true);
  _selectedTool = K::RESISTOR;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::coilSelect()
{
  STOP_ACTION
      unselectLastUsed();
  coilSelectAction->setChecked(true);
  _selectedTool = K::COIL;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::capacitorSelect()
{
  STOP_ACTION
      unselectLastUsed();
  capacitorSelectAction->setChecked(true);
  _selectedTool = K::CAPACITOR;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::VDCSelect()
{
  STOP_ACTION
      unselectLastUsed();
  VDCSelectAction->setChecked(true);
  _selectedTool = K::VDC;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::ADCSelect()
{
  STOP_ACTION
      unselectLastUsed();
  ADCSelectAction->setChecked(true);
  _selectedTool = K::ADC;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::diodeSelect()
{
  STOP_ACTION
      unselectLastUsed();
  diodeSelectAction->setChecked(true);
  _selectedTool = K::DIODE;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::generatorSelect()
{
  STOP_ACTION
      unselectLastUsed();
  generatorSelectAction->setChecked(true);
  _selectedTool = K::GENERATOR;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::opAmpSelect()
{
  STOP_ACTION
      unselectLastUsed();
  opAmpSelectAction->setChecked(true);
  _selectedTool = K::OPAMP;
  mainWidget->setMouseTrackingOnTabs(true);
}

void MainWindow::aboutApplication()
{
  STOP_ACTION
      aboutDialog->show();
}

void MainWindow::showGrid(bool b)
{
  STOP_ACTION
      QSettings set;
  set.setValue("showgrid", b);
  Circuit::showGrid = b;
  mainWidget->updateCurrent();
}

void MainWindow::zoomIn()
{
  this->mainWidget->getCurrent()->circuitWidget->scaleUp();
}

void MainWindow::zoomOut()
{
  this->mainWidget->getCurrent()->circuitWidget->scaleDown();
}

void MainWindow::undo()
{
  this->mainWidget->getCurrent()->circuitWidget->undo();
}

void MainWindow::redo()
{
  this->mainWidget->getCurrent()->circuitWidget->redo();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
  event->ignore();
  this->quit();
}

void MainWindow::leaveEvent(QEvent *event)
{
  mouseGrabRestore = this->mainWidget->getCurrent()->circuitWidget->grabedMouse;
  //mouseGrabRestoreIndex = this->mainWidget->currentIndex();
  this->mainWidget->getCurrent()->circuitWidget->releaseMouse();
  QWidget::leaveEvent(event);
}

void MainWindow::enterEvent(QEvent *event)
{
  if(mouseGrabRestore)
    {
      this->mainWidget->getCurrent()->circuitWidget->grabMouse();
      mouseGrabRestore = false;
    }
  QWidget::enterEvent(event);
}
