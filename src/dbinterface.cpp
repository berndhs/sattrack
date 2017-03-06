#include "dbinterface.h"

namespace deliberate {


DBInterface::DBInterface(QObject *parent)
  : QObject(parent),
  m_date(QString())
{

}

void
DBInterface::setDate(const QString &dt)
{
  m_date = dt;
  emit dateChanged(m_date);
}

QString
DBInterface::date()
{
  if (m_date.isEmpty()) {
    QString now = QDateTime::currentDateTime().toString(Qt::ISODate);
    setDate(now);
  }
  return m_date;
}

} // namespace
