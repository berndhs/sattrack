#ifndef PICBUTTONLIST_H
#define PICBUTTONLIST_H



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
#include <QAbstractItemModel>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QByteArray>
#include <QMap>
#include <QHash>
#include <QDebug>
#include <QTimer>

namespace deliberate {


class DBInterface;


class PicButtonList : public QAbstractItemModel
{
  Q_OBJECT

public:
  PicButtonList(QObject *parent = Q_NULLPTR);

  Q_PROPERTY(bool dbConnected READ dbConnected WRITE setDbConnected NOTIFY dbConnectedChanged)

  void setDB (DBInterface * db) { m_dbif = db; }
  DBInterface * db () { return m_dbif; }

  int columnCount(const QModelIndex & parent=QModelIndex()) const;
  int rowCount(const QModelIndex & parent=QModelIndex()) const;
  QVariant data (const QModelIndex & index, int role = Qt::DisplayRole) const;
  QModelIndex index (int row, int column, const QModelIndex & parent=QModelIndex()) const;
  Q_INVOKABLE QString buttonLabel (int row) const;
  Q_INVOKABLE QByteArray buttonImage (const QString &ident, const QString &picname) const;
  Q_INVOKABLE void clear();
  QModelIndex parent (const QModelIndex &child) const;
  QHash<int, QByteArray> roleNames() const;
  int size() { return m_dataMap.size(); }

  bool addItem (const QString &ident, const QString &picname,
                const QString &remark, const QString &stamp,
                const QByteArray & image);
  bool haveKey (const QString &ident, const QString &picname);

  enum class PicRole {
    R_TooSmall = Qt::UserRole,
    R_Ident,
    R_Picname,
    R_Remark,
    R_Stamp,
    R_Image,
    R_TooBig
  };

  bool dbConnected() const
  {
    return m_dbConnected;
  }

  void dump();

public slots:

  void dumpKeys();

  void setDbConnected(bool dbConnected)
  {
    if (m_dbConnected == dbConnected)
      return;

    m_dbConnected = dbConnected;
    emit dbConnectedChanged(dbConnected);
  }

signals:
  void dbConnectedChanged(bool dbConnected);

private:

  QString composeKey (const QString & id, const QString & file) const;

  struct Image {
    Image (const QString &id,
           const QString &p,
           const QString &r,
           const QString &s)
      :ident(id),
        picname(p),
        remark(r),
        stamp(s),
        image(QByteArray())
    {}
    void setImage(const QByteArray & bytes) { image = bytes; }
    QStringList dump()
    {
      QStringList res;
      res << ident;
      res << picname;
      res << remark;
      res << stamp;
      return res;
    }

    QString ident;
    QString picname;
    QString remark;
    QString stamp;
    QByteArray image;
  };

  QHash<int, QByteArray>  m_roles;

  QList<QString>         m_dataKey;
  QMap<QString, Image*>  m_dataMap;

  QTimer * checkTimer ;

  bool m_dbConnected;
  DBInterface * m_dbif;
};

} // namespace

#endif // PICBUTTONLIST_H
