#include "imagesource.h"
#include <QDebug>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QByteArray>
#include <QImage>
#include <QString>
#include <stdlib.h>
#include "dbinterface.h"

namespace deliberate {


ImageSource::ImageSource(QQmlImageProviderBase::ImageType tipo,
                           QQmlImageProviderBase::Flags flags)
  : QQuickImageProvider(QQmlImageProviderBase::Image,flags),
    m_thePics(nullptr)
{
  qDebug() << Q_FUNC_INFO << tipo << flags;
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
  QTemporaryFile tmp (QString("tmppicXXXXXX.jpg"));
  tmp.open();

  QByteArray img;
  qDebug() << Q_FUNC_INFO << "m_thePics " << m_thePics
           << "\n\t\tlook for" << info.path() << info.fileName();
  if (buttonDB()) {
    img = buttonDB()->buttonImage(info.path(),info.fileName());
    qDebug() << Q_FUNC_INFO << "images has" << img.size() << "bytes";
    int n = tmp.write(img.data(),img.size());
    tmp.close();
    qDebug() << Q_FUNC_INFO << "wrote " << n << "bytes";
    QString cp  = QString("cp %1 pic.jpg").arg(tmp.fileName());
    int ret = system (cp.toStdString().c_str());
    qDebug() << Q_FUNC_INFO << "system says " << ret;
  }
  QImage::Format fmt = QImage::Format_Indexed8;
  unsigned char * uc = (unsigned char *) img.data();
  qDebug() << Q_FUNC_INFO << "data in " << tmp.fileName();
  return QImage(tmp.fileName());
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


