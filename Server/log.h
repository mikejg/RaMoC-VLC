
#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QDebug>
#include <QDateTime>

class Log : QObject
{
  Q_OBJECT
  
  public:
  Log( QObject *parent = 0);

  static void info(QString str);
  static void error(QString str);
  static void db(QString str);
  static void player(QString str);
  static void tcp(QString str);
};
#endif
