#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QQmlImageProviderBase>
#include <QQuickImageProvider>


class ImageSource : public QQuickImageProvider
{

public:
  ImageSource();

  ImageType imageType() const;
  Flags     flags() const;
};

#endif // IMAGESOURCE_H
