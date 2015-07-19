#ifndef COLORCOMBOBOX_H
#define COLORCOMBOBOX_H

#include <QComboBox>
#include <QColor>

class ColorComboBox : public QComboBox {
  Q_OBJECT
public:
  ColorComboBox();
  ~ColorComboBox();

private:
  void addColor(QString name);

signals:
  void colorChanged(QColor);

private slots:
  void currentChanged(int i);
};

#endif // COLORCOMBOBOX_H
