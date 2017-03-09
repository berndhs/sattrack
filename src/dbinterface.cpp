#include "dbinterface.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>

/****************************************************************
 * This file is distributed under the following license:
 *
 * Copyright (C) 2017, Bernd Stramm
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/


namespace deliberate {

DBInterface::DBInterface(QObject *parent)
  : QObject(parent),
  m_date(QDateTime::currentDateTime()),
  m_haveDB(false),
  m_app(0)
{
  qDebug() << Q_FUNC_INFO ;
  static int dbcount(0);
  ++dbcount;
  m_thePics = new PicButtonList(this);
  m_thePics->setObjectName("In DBInterface");
  m_thePics->setDB(this);
  qDebug() << Q_FUNC_INFO << dbcount << m_thePics;

}

bool DBInterface::doConnect()
{
  qDebug() << Q_FUNC_INFO;
  m_db = QSqlDatabase::addDatabase("QMYSQL");
  m_db.setHostName("localhost");
  m_db.setDatabaseName("satview");
  m_db.setUserName("bernd");
  m_db.setPassword("geronimo");
  bool worked = m_db.open();
  m_haveDB = worked;
  m_thePics->setDbConnected(m_haveDB);
  qDebug() << Q_FUNC_INFO << worked;
  return worked;
}

void DBInterface::getImages()
{
  qDebug() << Q_FUNC_INFO;
  QSqlQuery qry(m_db);
  QString select ("select * from satpics order by ident DESC limit 10;");
  bool worked = qry.exec(select);
  qDebug() << Q_FUNC_INFO << worked << qry.size();

  QSqlRecord resultRec = qry.record();
  if (resultRec.count() < 5) {
    qDebug() << "database corrupt? only " << resultRec.count() << " columns";
    abort();
  }
  int identNdx = resultRec.indexOf("ident");
  int picnameNdx = resultRec.indexOf("picname");
  int imageNdx = resultRec.indexOf("image");
  int stampNdx = resultRec.indexOf("stamp");
  int remarkNdx = resultRec.indexOf("remark");
  qry.first();
  for (int i=0; i<qry.size(); ++i,qry.next()) {
    m_thePics->addItem(qry.value(identNdx).toString(),
                      qry.value(picnameNdx).toString(),
                      qry.value(remarkNdx).toString(),
                      qry.value(stampNdx).toString(),
                      qry.value(imageNdx).toByteArray());
  }
  emit numImagesChanged(m_thePics->rowCount());
}

void
DBInterface::doDisConnect()
{
  m_db.close();
}

void DBInterface::doQuit()
{
  qDebug() << Q_FUNC_INFO ;

  doDisConnect();
//  m_thePics->clear();
//  m_app->quit();

}

void DBInterface::doRaise(const int index, const QString ident, const QString picname)
{
  qDebug() << Q_FUNC_INFO << index << ident << picname;
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
