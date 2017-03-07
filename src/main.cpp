

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


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


#include <QQmlImageProviderBase>
#include <QQuickImageProvider>

#include "dbinterface.h"
#include "picbuttonlist.h"
#include "imagesource.h"

using namespace deliberate;

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  DBInterface dbface;
  dbface.setApp(app);


  QQmlApplicationEngine engine;
  ImageSource imgSrc;

  engine.addImageProvider("satpics",&imgSrc);
  qmlRegisterType<DBInterface>("com.berndhs",1,0,"DBIf");
  engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

  return app.exec();
}
