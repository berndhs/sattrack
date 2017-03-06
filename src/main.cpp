#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dbinterface.h"

using namespace deliberate;

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  DBInterface dbface;


  QQmlApplicationEngine engine;

  QQmlContext ctxt (&engine);
  ctxt.setContextProperty("dbif",&dbface);
  engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

  return app.exec();
}
