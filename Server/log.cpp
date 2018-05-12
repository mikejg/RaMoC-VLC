#include "log.h"
//#include <iostream>

Log::Log(QObject *parent) : QObject(parent)
{
}

void Log::info(QString str)
{
  //green
  qInfo() << QDateTime::currentDateTime().toString("hh:mm:ss") 
          << "INFO \033[32;1m" << str << "\033[0m";
}

void Log::error(QString str)
{
  QStringList list = str.split("\n");
  foreach(QString string, list)
    qInfo() << QDateTime::currentDateTime().toString("hh:mm:ss") << 
    "ERROR\033[31;1m" << string <<"\033[0m";
}

void Log::db(QString str)
{
  qInfo() << QDateTime::currentDateTime().toString("hh:mm:ss") << "DB   \033[34;1m" << str <<"\033[0m";
}

void Log::player(QString str)
{
  //purpel
  qInfo() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Player\033[35;1m" << str <<"\033[0m";
}

void Log::tcp(QString str)
{
  qInfo() << QDateTime::currentDateTime().toString("hh:mm:ss") << "TCP   \033[36;1m" << str <<"\033[0m";
}

