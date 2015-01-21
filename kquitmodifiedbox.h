#ifndef KQUITMODIFIEDBOX_H
#define KQUITMODIFIEDBOX_H

#include <QMessageBox>

class KQuitModifiedBox : public QMessageBox
{
  Q_OBJECT
public:
  explicit KQuitModifiedBox();

signals:

public slots:

protected:
  virtual void showEvent ( QShowEvent * e );

};

#endif // KQUITMODIFIEDBOX_H
