#ifndef FILECOPYTHREAD_H
#define FILECOPYTHREAD_H

#include <QThread>
#include <QFile>
#include <QDataStream>
#include <log.h>

class FileCopyThread : public QThread
{
  Q_OBJECT

  private:
    QString source;

  public:
    FileCopyThread (QObject *parent = 0);
    void setSource(QString str);

  protected:
    virtual void run();

  signals:
    void playBuffer();
};
#endif
