#include "imagesource.h"
#include <QDebug>

namespace deliberate {


ImageSource::ImageSource(QQmlImageProviderBase::ImageType tipo,
                           QQmlImageProviderBase::Flags flags)
  : QQuickImageProvider(QQmlImageProviderBase::Image,flags)
{
  qDebug() << Q_FUNC_INFO << tipo << flags;
}

QImage
ImageSource::requestImage(const QString &id,
                          QSize *size,
                          const QSize &requestedSize)
{
  qDebug() << Q_FUNC_INFO;
  QImage fakeImg ("/home/bernd/mywork/sattrack/sattrack/CAN.jpg");
  return fakeImg;
}

QPixmap
ImageSource::requestPixmap(const QString &id,
                           QSize *size,
                           const QSize &requestedSize)
{
  qDebug() << Q_FUNC_INFO;
  return QPixmap();

}

QQuickTextureFactory *
ImageSource::requestTexture(const QString &id,
                            QSize *size,
                            const QSize &requestedSize)
{
  qDebug() << Q_FUNC_INFO;
  return nullptr;
}

} // namespace


