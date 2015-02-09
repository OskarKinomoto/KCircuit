#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QWidget(parent)
{
  this->setLayout(new QVBoxLayout());

  this->layout()->addWidget(new QLabel(tr("<center><b>QtCircuit</b><br>Version: development<br>Author: Oskar Kinomoto</center>")));

  closeButton = new QPushButton(QIcon::fromTheme("window-close"), tr("Close"));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  this->layout()->addWidget(closeButton);
  this->setWindowTitle(tr("About QtCircuit"));

  //TODO treść
  //TODO pozycja
  this->resize(300,200);
  this->setMinimumSize(300, 200);

  this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
}

AboutDialog::~AboutDialog()
{

}

void AboutDialog::close()
{
  this->hide();
}

