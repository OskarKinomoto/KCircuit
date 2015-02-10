#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QWidget(parent)
{
  this->setLayout(new QVBoxLayout());
  QString text = tr("<center><b>KCircuit</b><br>Version: ")+QString(VERSION)+tr("<br>Author: Oskar Kinomoto<br><a href='https://kinomoto.me/'>kinomoto.me</a><br><a href='https://github.com/OskarKinomoto/KCircuit'><img src=':/img/github.png' height=30></a></center>");
  this->l = new QLabel(text);
  this->l->setTextInteractionFlags(Qt::TextBrowserInteraction);
  this->l->setOpenExternalLinks(true);
  this->layout()->addWidget(l);

  closeButton = new QPushButton(QIcon::fromTheme("window-close"), tr("Close"));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  this->layout()->addWidget(closeButton);
  this->setWindowTitle(tr("About KCircuit"));
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

