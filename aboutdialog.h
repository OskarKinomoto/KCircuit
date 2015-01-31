#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QtWidgets>

class AboutDialog : public QWidget
{
  Q_OBJECT
public:
  explicit AboutDialog(QWidget *parent = 0);
  ~AboutDialog();
private:
  QPushButton * closeButton;
signals:

public slots:
  void close();
};

#endif // ABOUTDIALOG_H
