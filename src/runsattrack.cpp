#include "runsattrack.h"


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

#include <QDebug>

namespace deliberate {
RunSattrack::RunSattrack(QObject *parent) : QObject(parent),
  m_app(nullptr)
{

}

void
RunSattrack::runMore(QObject *obj,
                         QUrl url)
{
  qDebug() << Q_FUNC_INFO << obj << url;
  QObject * root = engine.rootObjects().at(0);
  QList<QObject*>  dbfCandidates = root->findChildren<QObject*>();
  DBInterface * dbf(nullptr);
  for (auto p=dbfCandidates.begin(); p != dbfCandidates.end(); ++p) {
    dbf = qobject_cast<DBInterface*>(*p);
    if (dbf) {
      break;
    }
  }
  if (dbf == nullptr) {
    abort();
  }
  imgSrc.setButtonDB(dbf->imageModel());
  dbf->setApp(*m_app);
}

void
RunSattrack::run(QGuiApplication &app)
{
  m_app = &app;
  qDebug() << Q_FUNC_INFO << m_app;

  engine.addImageProvider("satpics",&imgSrc);
  qmlRegisterType<DBInterface>("com.berndhs",1,0,"DBIF");
  connect (&engine,SIGNAL(objectCreated(QObject*,QUrl)),this,SLOT(runMore(QObject*, QUrl)));
  engine.load(QUrl(QString("qrc:/qml/main.qml")));


}


} // namespace
