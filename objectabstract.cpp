#include "objectabstract.h"

int ObjectAbstract::counter = 0;

ObjectAbstract::ObjectAbstract(K::objectType t, quint32 id) : type(t), ID(id)
{
  counter++;
  //qDebug() << counter;
}

ObjectAbstract::ObjectAbstract(K::objectType t, QDataStream &in) : type(t)
{
  in >> ID;
  counter++;
  //qDebug() << counter;
}

ObjectAbstract::~ObjectAbstract()
{
  counter--;
  qDebug() << counter;
}

bool ObjectAbstract::rotate45() { return false; }

bool ObjectAbstract::rotate90() { return false; }

bool ObjectAbstract::rotate315()
{
  return false;
}

bool ObjectAbstract::rotate270()
{
  return false;
}

K::objectInfo ObjectAbstract::info()
{
  return {type, name, this};
}

