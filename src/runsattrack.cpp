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
  QQmlContext * ctx = engine.rootContext();
  qDebug() << Q_FUNC_INFO << "ctx" << ctx;
  QList<DBInterface*>  dbf = ctx->findChildren<DBInterface*>();
  qDebug() << Q_FUNC_INFO << "dbf" << dbf;
  if (!dbf.at(0)) {
    abort();
  }
  imgSrc.setButtonDB(dbf.at(0)->imageModel());
  dbf.at(0)->setApp(*m_app);
  qDebug() << Q_FUNC_INFO << "image model at " << dbf.at(0)->imageModel();
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
