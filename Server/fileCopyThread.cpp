#include "fileCopyThread.h"


FileCopyThread::FileCopyThread(QObject *parent ) : QThread(parent)
{
}

void FileCopyThread::run()
{
  QFile file(source);
  QFile target("/tmp/buffer");
  QFileInfo fileInfo(source);

  if(target.exists())
  {
    target.remove();
  }

  if(!file.exists())
  {
    Log::player("File existiert nicht: " + source);
    return;
  }

  if(!file.open(QIODevice::ReadOnly))
  {
    Log::player("File kann nicht geöffnet werden: " + source);
    return;
  }

  if(!target.open(QIODevice::ReadWrite))
  {
    Log::player("target kann nicht geöffnet werden: " + source);
    return;
  }

  QDataStream in(&file);
  int len = 16384;
  int count = 0;
  bool b = false;

  char data[len];

  Log::player("starte While ");
  while(!in.atEnd())
  {
    if(in.readRawData(data, len) == -1)
      Log::player("error readRawData:");

    if(target.write(data, len) == -1)
      Log::player("error writeData");

    count = count + len;
    if(count > 262144 && !b)
    {
      b = true;
      playBuffer();
    }

  }

  file.close();
  target.close();

  Log::player("Ende While ");
}

void FileCopyThread::setSource(QString str)
{
  if(isRunning())
  {
    this->terminate();
  }
  source = str;
  if(this->wait())
  this->start();
}
