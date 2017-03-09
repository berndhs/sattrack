#ifndef TIMERCHECKER_H
#define TIMERCHECKER_H

#include <QObject>
#include <QTimer>

namespace deliberate {

  class ImageSource;

class TimerChecker : public QObject
{
  Q_OBJECT
public:
  explicit TimerChecker(QObject *parent = 0);
  void go();

  void installImageSource (ImageSource *is) { m_imgSrc = is; }

signals:

public slots:

  void checkDB();

private:

  ImageSource  * m_imgSrc;
  QTimer       * m_checkTimer;

};

}

#endif // TIMERCHECKER_H
