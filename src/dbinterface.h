#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QSqlDatabase>
#include <QDateTime>

namespace deliberate {

class DBInterface : public QObject
{
  Q_OBJECT

public:
  explicit DBInterface(QObject *parent = 0);

  Q_PROPERTY(QDateTime date READ date NOTIFY dateChanged)
  Q_INVOKABLE bool doConnect ();
  Q_INVOKABLE void getImages();
  Q_PROPERTY(int numImages READ numImages NOTIFY numImagesChanged)

QDateTime date();

int numImages() const
{
  return m_numImages;
}

public slots:

  void setDate (const QString & dt);


signals:

void dateChanged(QDateTime date);

void numImagesChanged(int numImages);

private:

  int       m_numImages;
  QDateTime m_date;
  QSqlDatabase m_db;
};

} // namespace

#endif // DBINTERFACE_H
