#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QQmlImageProviderBase>
#include <QQuickImageProvider>

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
};
} // namespace

#endif // IMAGESOURCE_H
