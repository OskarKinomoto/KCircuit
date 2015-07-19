#ifndef OBJECTSETTINGSRESISTOR_H
#define OBJECTSETTINGSRESISTOR_H

#include "objectsettingsabstract.h"
#include "colorcombobox.h"

class ObjectResistor;

class ObjectSettingsResistor : public ObjectSettingsAbstract {
  Q_OBJECT
public:
  ObjectSettingsResistor(ObjectResistor *resistor, Circuit *c);
  ~ObjectSettingsResistor();

private:
  ObjectResistor *r;
  QLineEdit *name;
  QLineEdit *label;
  QComboBox *type;
  QAction *typeResistor;
  QAction *typePotentiometr;
  ColorComboBox *color;

private slots:
  void nameEdited(QString t);
  void labelEdited(QString t);
  void typeEdited(int i);
  void colorEdited(QColor c);
};

#endif // OBJECTSETTINGSRESISTOR_H
