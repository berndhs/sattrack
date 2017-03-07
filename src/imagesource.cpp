#include "imagesource.h"

ImageSource::ImageSource()
{

}

QQmlImageProviderBase::ImageType
ImageSource::imageType() const
{
  return ImageType::Image;
}

QQmlImageProviderBase::Flags
ImageSource::flags() const
{
   return QQmlImageProviderBase::Flags(1);
}
