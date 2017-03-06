#include "dbinterface.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlResult>

namespace deliberate {


DBInterface::DBInterface(QObject *parent)
  : QObject(parent),
    m_numImages(0),
  m_date(QDateTime::currentDateTime())
{
  qDebug() << Q_FUNC_INFO;

}

bool DBInterface::doConnect()
{
  m_db = QSqlDatabase::addDatabase("QMYSQL");
  m_db.setHostName("localhost");
  m_db.setDatabaseName("satview");
  m_db.setUserName("bernd");
  m_db.setPassword("geronimo");
  bool worked = m_db.open();
  qDebug() << Q_FUNC_INFO << worked;
  return worked;
}

void DBInterface::getImages()
{
  m_numImages = 0;
  QSqlQuery qry(m_db);
  QString select ("select * from satpics order by ident DESC;");
  bool worked = qry.exec(select);
  qDebug() << Q_FUNC_INFO << worked << qry.size();
  m_numImages = qry.size();
  emit numImagesChanged(m_numImages);
}

void
DBInterface::setDate(const QString &dt)
{
  m_date = QDateTime::fromString(dt);
  qDebug() << Q_FUNC_INFO << m_date.toString();
  emit dateChanged(m_date);
}

QDateTime DBInterface::date()
{
  m_date = QDateTime::currentDateTime();

  return m_date;
}

} // namespace
