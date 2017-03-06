#ifndef DBINTERFACE_H
#define DBINTERFACE_H

#include <QObject>
#include <QDateTime>
#include <QString>

namespace deliberate {

class DBInterface : public QObject
{
  Q_OBJECT

public:
  explicit DBInterface(QObject *parent = 0);

  Q_PROPERTY(QString date READ date NOTIFY dateChanged)

QString date();

public slots:

  void setDate (const QString & dt);


signals:

void dateChanged(QString date);

private:

  QString m_date;
};

} // namespace

#endif // DBINTERFACE_H
