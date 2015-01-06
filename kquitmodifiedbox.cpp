#include "kquitmodifiedbox.h"

KQuitModifiedBox::KQuitModifiedBox() :
  QMessageBox()
{

  this->setText(tr("Dokument został zmodyfikowany."));
  this->setInformativeText(tr("Czy chcesz zapisać zmieny?"));
  this->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  this->setWindowTitle(tr("Zachowaj zmiany"));
  this->setIcon(QMessageBox::Question);
}

void KQuitModifiedBox::showEvent ( QShowEvent*e){
  this->setDefaultButton(QMessageBox::Save);
  QMessageBox::showEvent(e);
}
