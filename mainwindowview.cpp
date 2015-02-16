#include "mainwindowview.h"

MainWindowView::MainWindowView(QWidget *parent) : QMainWindow(parent)
{
}

void MainWindowView::init()
{
  actionInit();
  menuInit();
  toolBarInit();
  centralWidgetInit();
  sizePositionInit();
}

MainWindowView::~MainWindowView()
{
  QSettings settings;
  settings.beginGroup("MainWindow");
  settings.setValue("size", this->size());
  settings.setValue("pos", this->pos());
  settings.endGroup();
}

void MainWindowView::actionInit()
{
  newA = new QAction(QIcon::fromTheme("document-new"), tr("New file"), nullptr);
  newA->setShortcut(QKeySequence::New);

  openA = new QAction(QIcon::fromTheme("document-open"), tr("Open"), nullptr);
  openA->setShortcut(QKeySequence::Open);

  saveA = new QAction(QIcon::fromTheme("document-save"), tr("Save"), nullptr);
  saveA->setShortcut(QKeySequence::Save);

  saveAsA = new QAction(QIcon::fromTheme("document-save-as"), tr("Save as..."), nullptr);
  saveAsA->setShortcut(QKeySequence::SaveAs);

  saveAllA = new QAction(QIcon::fromTheme("document-save-all"), tr("Save all"), nullptr);
  //saveAllA->setShortcut();

  quitA = new QAction(QIcon::fromTheme("application-exit"), tr("Quit"), nullptr);
  quitA->setShortcut(QKeySequence::Quit);

  rotate90A = new QAction(nullptr);
  rotate90A->setShortcut(QKeySequence(QString("R")));

  rotate45A = new QAction(nullptr);
  rotate45A->setShortcut(QKeySequence(QString("Alt+R")));

  zoomInA = new QAction(QIcon::fromTheme("zoom-in"), tr("Zoom in"), nullptr);
  zoomInA->setShortcut(QKeySequence::ZoomIn);

  zoomIn2A = new QAction(nullptr);
  zoomIn2A->setShortcut(tr("Ctrl+=", "zoom in shortcut without shift"));
  this->addAction(zoomIn2A);

  zoomOutA = new QAction(QIcon::fromTheme("zoom-out"), tr("Zoom out"), nullptr);
  zoomOutA->setShortcut(QKeySequence::ZoomOut);

  undoA = new QAction(QIcon::fromTheme("edit-undo"), tr("Undo"), nullptr);
  undoA->setShortcut(QKeySequence::Undo);

  redoA = new QAction(QIcon::fromTheme("edit-redo"), tr("Redo"), nullptr);
  redoA->setShortcut(QKeySequence::Redo);

  this->addActions({rotate90A, rotate45A});
}

void MainWindowView::menuInit()
{
  fileM = this->menuBar()->addMenu(tr("File"));
  fileM->addActions({newA, openA});
  fileM->addSeparator();
  fileM->addActions({saveA, saveAsA, saveAllA});
  fileM->addSeparator();
  fileM->addActions({quitA});

  editM = this->menuBar()->addMenu(tr("Edit"));
  editM->addActions({undoA, redoA});

  viewM = this->menuBar()->addMenu(tr("View"));
  viewM->addActions({zoomInA, zoomOutA});
}

void MainWindowView::toolBarInit()
{

}

void MainWindowView::centralWidgetInit()
{
  tabWidget = new TabWidget();
  this->setCentralWidget(tabWidget);
  this->setStyleSheet("QMainWindow { background: auto; }"); /// strange fix for strange line, really strange!
}

void MainWindowView::sizePositionInit()
{
  QSettings settings;
  settings.beginGroup("MainWindow");
  this->resize(settings.value("size", QSize(800, 600)).toSize());
  this->move(settings.value("pos", QPoint(200, 200)).toPoint());
  settings.endGroup();
}

void MainWindowView::keyPressEvent(QKeyEvent *event)
{
  if(event->modifiers() == 0x24000000)
    {
      if(event->key() == 0x2b) zoomInA->trigger();
      else if(event->key())
        switch(event->key())
          {
          case 0x2b: zoomInA->trigger(); break;
          case 0x2d: zoomOutA->trigger(); break;
          default: QMainWindow::keyPressEvent(event); break;
          }
    }
  else QMainWindow::keyPressEvent(event);
}

