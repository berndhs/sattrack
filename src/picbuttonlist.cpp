#include "picbuttonlist.h"
#include <QFileInfo>

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

PicButtonList::PicButtonList (QObject *parent)
  : QAbstractItemModel(parent)
{
  m_dataMap.clear();
  m_roles[int(PicRole::R_Ident)] = "ident";
  m_roles[int(PicRole::R_Remark)] = "remark";
  m_roles[int(PicRole::R_Stamp)] = "stamp";
  m_roles[int(PicRole::R_Image)] = "image";
  m_roles[int(PicRole::R_Picname)] = "picname";
  checkTimer = new QTimer(this);
  checkTimer->setInterval(3000);
  connect(checkTimer,SIGNAL(timeout()),this,SLOT(dumpKeys()));
//  checkTimer->start(30000);
  dumpKeys();

}

void
PicButtonList::dumpKeys()
{
  return;
  qDebug() << Q_FUNC_INFO << "I am " << this << "\n\t\tkeys are " << m_dataKey;
}

int
PicButtonList::columnCount(const QModelIndex & parent) const
{
  return 1;
}

int PicButtonList::rowCount(const QModelIndex &parent) const
{
  return m_dataMap.size();
}

QVariant
PicButtonList::data(const QModelIndex &index, int role) const
{
  QVariant result;
  int row = index.row();
  int max = m_dataMap.size();
  if (row >= 0 || row < max) {
    QString key = m_dataKey[row];
    if (role > int(PicRole::R_TooSmall) || role < int(PicRole::R_TooBig)) {
      PicRole pRole = PicRole(role);
      Image *im = m_dataMap[key];
      if (!im) {
        qDebug() << "Fatal: image memory map corrupt" ;
        abort();
      }
//      qDebug() << Q_FUNC_INFO << row << role << m_roles[role];
      switch (pRole) {
        case PicRole::R_Ident:
          result.setValue(im->ident);
          break;
        case PicRole::R_Picname:
          result.setValue(im->picname);
          break;
        case PicRole::R_Remark:
          result.setValue(im->remark);
          break;
        case PicRole::R_Stamp:
          result.setValue(im->stamp);
          break;
        case PicRole::R_Image:
          result.setValue(im->image);
          break;
        default:
          result = QVariant();
      }
    }
  }
//  qDebug() << Q_FUNC_INFO << "returns " << result;
  return result;
}

QModelIndex
PicButtonList::index(int row, int column, const QModelIndex &parent) const
{
  return createIndex (row,column);
}

QString
PicButtonList::buttonLabel(int row) const
{
  return QString();
}

QByteArray
PicButtonList::buttonImage(const QString &ident, const QString &picname) const
{
  qDebug() << Q_FUNC_INFO << ident<< picname << "this " << this;
  QString key = composeKey(ident,picname);
  if (m_dataMap.contains(key)) {
    qDebug() << Q_FUNC_INFO << "yes we have " << key;
    return m_dataMap[key]->image;
  } else {
    qDebug() << Q_FUNC_INFO << "NO KEY " << key;
    qDebug() << "\t\t" << "keys are " << m_dataKey;
    return QByteArray();
  }
}

void
PicButtonList::clear()
{
  qDebug() << Q_FUNC_INFO;
  beginResetModel();
  m_dataKey.clear();
//  for (auto d=m_dataMap.begin(); d !=m_dataMap.end(); ++d) {
//    Image *im = d.value();
//    delete im;
//    m_dataMap.erase(d);
//  }
  m_dataMap.clear();
  endResetModel();
}

QModelIndex
PicButtonList::parent(const QModelIndex &child) const
{
  return QModelIndex();
}

QHash<int, QByteArray>
PicButtonList::roleNames() const
{
  return m_roles;
}

bool
PicButtonList::addItem(const QString &ident,
                       const QString &picname,
                       const QString &remark,
                       const QString &stamp,
                       const QByteArray &image)
{/*
  qDebug() << Q_FUNC_INFO << ident << picname
           << remark << stamp << image.size();*/
  beginResetModel();
  Image *im (new Image (ident,picname,remark,stamp));
  im->setImage(image);
  QString key =  composeKey(ident,picname);
  m_dataKey.append(key);
  m_dataMap[key] = im;
  endResetModel();
  return true;
}

bool PicButtonList::haveKey(const QString &ident, const QString &picname)
{
  QString key = composeKey(ident,picname);
  if (m_dataMap.contains(key)) {
    return true;
  }
  return false;
}

void PicButtonList::dump()
{
  qDebug() << Q_FUNC_INFO ;
  dumpKeys();
  for (auto k=m_dataMap.begin(); k!=m_dataMap.end(); ++k) {
    qDebug() << "\t" << k.key() << k.value()->dump();
  }
}

QString
PicButtonList::composeKey(const QString &id, const QString &file) const
{
  QFileInfo nameInfo (file);
  QString base = nameInfo.fileName();
  return id + "<=>" + base;
}

} // namespace
