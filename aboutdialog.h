#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtWidgets>
#include "include.h"

class AboutDialog : public QWidget
{
  Q_OBJECT
public:
  explicit AboutDialog(QWidget *parent = 0);
  ~AboutDialog();
private:
  QPushButton * closeButton;
  QLabel * l;
signals:

public slots:
  void close();
};

#endif // ABOUTDIALOG_H
