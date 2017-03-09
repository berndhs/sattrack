#include "timerchecker.h"
#include "imagesource.h"

namespace deliberate {

TimerChecker::TimerChecker(QObject *parent) : QObject(parent)
{
  m_checkTimer = new QTimer(this);
  connect (m_checkTimer,SIGNAL(timeout()),this,SLOT(checkDB()));
  m_checkTimer->setInterval(1000);

}

void
TimerChecker::go()
{
   if (!m_checkTimer->isActive()) {
     m_checkTimer->start();
   }
}

void
TimerChecker::checkDB()
{
   if (m_imgSrc) {
     m_imgSrc->checkDB();
   }
}

} // namespace
