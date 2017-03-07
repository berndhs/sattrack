#ifndef DBINTERFACE_H
#define DBINTERFACE_H



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



#include <QObject>
#include <QDateTime>
#include <QString>
#include <QSqlDatabase>
#include <QDateTime>
#include <QGuiApplication>

#include "picbuttonlist.h"

namespace deliberate {

class DBInterface : public QObject
{
  Q_OBJECT

public:
  explicit DBInterface(QObject *parent = 0);
  void setApp (QGuiApplication & app) { m_app = &app; }

  Q_PROPERTY(QDateTime date READ date NOTIFY dateChanged)
  Q_INVOKABLE bool doConnect ();
  Q_INVOKABLE void getImages();
  Q_INVOKABLE void doDisConnect();
  Q_INVOKABLE void doQuit();
  Q_INVOKABLE void doRaise(const int index, const QString ident,const QString picname);
  Q_PROPERTY(int numImages READ numImages NOTIFY numImagesChanged)

  Q_PROPERTY(PicButtonList* imageModel READ imageModel NOTIFY imageModelChanged)

QDateTime date();

int numImages() const
{
  return m_thePics->rowCount();
}

PicButtonList* imageModel() const
{
  return m_thePics;
}

public slots:

  void setDate (const QString & dt);


signals:

void dateChanged(QDateTime date);

void numImagesChanged(int numImages);

void imageModelChanged(PicButtonList* imageModel);

private:

  QDateTime m_date;
  QSqlDatabase m_db;

  PicButtonList *m_thePics;
  QGuiApplication * m_app;
};

} // namespace

#endif // DBINTERFACE_H
