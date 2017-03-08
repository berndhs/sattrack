#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QQmlImageProviderBase>
#include <QQuickImageProvider>
#include "picbuttonlist.h"

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

  PicButtonList* buttonDB() const
  {
    return m_thePics;
  }

public slots:
  void setButtonDB(PicButtonList* buttonDB)
  {
    if (m_thePics == buttonDB)
      return;
  }
\
private:

  PicButtonList * m_thePics;
};
} // namespace

#endif // IMAGESOURCE_H
