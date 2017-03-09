#include "imagesource.h"
#include <QDebug>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QByteArray>
#include <QImage>
#include <QString>
#include <QObject>
#include <stdlib.h>
#include "dbinterface.h"

namespace deliberate {


ImageSource::ImageSource(QQmlImageProviderBase::ImageType tipo,
                           QQmlImageProviderBase::Flags flags)
  : QQuickImageProvider(QQmlImageProviderBase::Image,flags),
    m_thePics(nullptr)
{
  qDebug() << Q_FUNC_INFO << tipo << flags;
  timeCheck.installImageSource(this);
  timeCheck.go();
}

void
ImageSource::checkDB()
{
   qDebug() << Q_FUNC_INFO << buttonDB() ;
   if (buttonDB()) {
     qDebug() << Q_FUNC_INFO << "\t" << buttonDB()->objectName() ;
   }
}

void
ImageSource::setButtonDB(PicButtonList *buttonDB)
{
  m_thePics = buttonDB;
}

QImage
ImageSource::requestImage(const QString &id,
                          QSize *size,
                          const QSize &requestedSize)
{
  if (buttonDB() == nullptr) {
    qDebug() << Q_FUNC_INFO << "not present";
    return QImage(":pics/nopic.jpg");
  }
  if (buttonDB()->size() < 1) {
    buttonDB()->db()->doConnect();
    buttonDB()->db()->getImages();
  }
  QFileInfo info(id);

  QByteArray img;
  qDebug() << Q_FUNC_INFO << "m_thePics " << m_thePics
           << "\n\t\tlook for" << info.path() << info.fileName();
  if (buttonDB()) {
    img = buttonDB()->buttonImage(info.path(),info.fileName());
  } else {
    return QImage(":pics/nopic.jpg");
  }
  QImage retImg;
  if (img.length() < 1) {
    return  QImage(":pics/nopic.jpg");
  }
  unsigned char * uc = (unsigned char *) (img.data());
  retImg.loadFromData(uc,img.length());
  return retImg;
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


