
#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

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


#include <QQmlImageProviderBase>
#include <QQuickImageProvider>
#include <QTimer>
#include "picbuttonlist.h"
#include "timerchecker.h"

namespace deliberate {
class ImageSource : public QQuickImageProvider
{

public:
  ImageSource(QQmlImageProviderBase::ImageType tipo = QQmlImageProviderBase::Image,
              QQmlImageProviderBase::Flags flags = 0);

  QImage requestImage(const QString & id,
                              QSize * size,
                              const QSize & requestedSize);
  QPixmap requestPixmap(const QString & id,
                               QSize * size,
                               const QSize & requestedSize);
  QQuickTextureFactory * requestTexture(const QString & id,
                                               QSize * size,
                                               const QSize & requestedSize);

  static QString nopic();

  PicButtonList* buttonDB() const
  {
    return m_thePics;
  }

public slots:
  void checkDB ();

  void setButtonDB(PicButtonList* buttonDB);
\
private:

  PicButtonList * m_thePics;

  TimerChecker  timeCheck;

};
} // namespace

#endif // IMAGESOURCE_H
