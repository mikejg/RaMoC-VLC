#include "vlc_process.h"
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDebug>

VLCProcess::VLCProcess(QObject *parent) : QObject(parent)
{
    Log::player(Q_FUNC_INFO);

    fileCopyThread = new FileCopyThread(this);

    argsList << "--verbose" << "0" << "-I" << "oldrc" << "-f";
    system("killall vlc");

    currentFile = "";

    connect(&process, SIGNAL(started()), this, SLOT(onVLCStarted()));
    connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)), 
            this,     SLOT(onVLCFinished(int,QProcess::ExitStatus)));
    connect(&process, SIGNAL(readyReadStandardOutput()), 
            this,     SLOT(onVLCReadStdOut()));
    connect(&process, SIGNAL(readyReadStandardError()), 
            this,     SLOT(onVLCReadError()));

    connect(&vlcSocket, SIGNAL(readyRead()),this, SLOT(onVLCSocketRead()));

    connect(&youtube_dl, SIGNAL(readyReadStandardOutput()), 
            this,        SLOT(onYouTubeReadStdOut()));
    connect(&youtube_dl, SIGNAL(finished(int,QProcess::ExitStatus)), 
            this,        SLOT(onYouTubeFinished(int,QProcess::ExitStatus)));
    connect(fileCopyThread, SIGNAL(playBuffer()), this, SLOT(onPlayBuffer()));
    
    connect(&getTimeTimer, SIGNAL(timeout()), this, SLOT(onVLCGetTime()));
    process.start("vlc", argsList);

    isMinutesBackward = false;
    isMinutesForward = false;
    isFastForward = false;
    isRewind      = false;
    isGetTime = false;
    isGetLength = false;
   subtitle = false;
   audioTrack = false;
}

VLCProcess::~VLCProcess()
{
  process.disconnect();
  process.kill();
}

void VLCProcess::faster()
{
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
//  if(isFastForward)
//  {
//    w1riteToVLCSocket("normal");
//    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
//    isFastForward = false;
//  }
//  else
//  {
    writeToVLCSocket("faster");
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
//    isFastForward = true;
//  }
}

void VLCProcess::getSubtitle()
{
  Log::player(Q_FUNC_INFO);
  QString strReturn = "[";

  for (int i = 0; i < subTitleList.size(); i++)
  {
    //letzter Eintrag ohne abschliessendem ','
    if(i == subTitleList.size() -1)
      strReturn = strReturn + "{\"path\":\"" + subTitleList.at(i) + "\"}";
    else
      strReturn = strReturn + "{\"path\":\"" + subTitleList.at(i) + "\"},";
  }

  strReturn = strReturn + "]";

  sig_WriteData("027|" + strReturn, true);
}

void VLCProcess::getAudio()
{
  Log::player(Q_FUNC_INFO);
  QString strReturn = "[";

  for (int i = 0; i < audioList.size(); i++)
  {
    //letzter Eintrag ohne abschliessendem ','
    if(i == audioList.size() -1)
      strReturn = strReturn + "{\"path\":\"" + audioList.at(i) + "\"}";
    else
      strReturn = strReturn + "{\"path\":\"" + audioList.at(i) + "\"},";
  }

  strReturn = strReturn + "]";

  sig_WriteData("029|" + strReturn, true);
}
void VLCProcess::rewind()
{
  Log::player(Q_FUNC_INFO);
//  if(isRewind)
//  {
//    writeToVLCSocket("normal");
//    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
//    isRewind  = false;
//  }
//  else
//  {
    writeToVLCSocket("slower");
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
//    isRewind = true;
//  }
}

void VLCProcess::minutesBackward()
{
    writeToVLCSocket("get_time");
    isMinutesBackward = true;
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::minutesForward()
{
  Log::player(Q_FUNC_INFO);
    isMinutesForward = true;
    writeToVLCSocket("get_time");
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::mute()
{
  Log::player(Q_FUNC_INFO);
    static bool m = false;
    if (m)
    {  
      writeToVLCSocket("volume 250");
      m = false;
    }
    else
    {
      writeToVLCSocket("volume 0");
      m= true;
    }
}

bool VLCProcess::isVLCConnected()
{
  if(vlcSocket.state() == QLocalSocket::ConnectedState)
  {
 //   Log::player("VLCSocket is connected");
    return true;
  }

  vlcSocket.connectToServer("/tmp/vlc.sock");
  if(vlcSocket.waitForConnected(4000))
  {
      Log::player("VLCSocket connected");
      return true;

  }
  else
      Log::error("can't connect VLCSocket");
}

void VLCProcess::onVLCGetTime()
{
//    Log::player(Q_FUNC_INFO);
    isGetTime = true;
    writeToVLCSocket("get_time");
}

void VLCProcess::onVLCGetLength()
{
//    Log::player(Q_FUNC_INFO);
    isGetLength = true;
    writeToVLCSocket("get_length");
    onVLCStatus();
}

void VLCProcess::onVLCGetVolume()
{
    Log::player(Q_FUNC_INFO);
    writeToVLCSocket("volume");
    onVLCStatus();
}

void VLCProcess::onVLCStarted()
{
  Log::player(Q_FUNC_INFO);

  if(currentFile != "")
    QTimer::singleShot(500, this, SLOT(onVLCRestart()));
}

void VLCProcess::onVLCReadError()
{
  //Log::player(Q_FUNC_INFO);
  QString url = process.readAllStandardError();
  Log::error(url);
}

void VLCProcess::onVLCRestart()
{
    writeToVLCSocket("add " + currentFile);
}

void VLCProcess::onVLCStatus()
{
  writeToVLCSocket("status");
}

void VLCProcess::onVLCSubtitle()
{
  writeToVLCSocket("strack");
  QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::onVLCAudio()
{
  writeToVLCSocket("atrack");
  QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::onVLCSocketRead()
{
  //Log::player(Q_FUNC_INFO);
  QString str;
 // bool subtitle = false;
 // bool audioTrack = false;

  while(vlcSocket.canReadLine())
  {
    str = vlcSocket.readLine(512);
    Log::player("VLCSocket: " + str);
    
    if(str.contains("audio volume"))
    {
      QString v;

      for(int i = 0; i < str.length(); i++)
      {
        if(str[i].isDigit())
        {
          v = v + str[i];
        }
      }
        Log::player("Volume: " + v);
        sig_WriteData("032|" + QString("%1").arg(v),false);
    }

    if(str.contains("end of Subtitle Track") ||
        str.contains("end of Untertitelspur"))
    {
      subtitle = false;
      foreach(QString string, subTitleList)
        Log::error(string);
      QTimer::singleShot(500, this, SLOT(onVLCAudio()));
      return;
    }

    if(str.contains("end of Audio Track") ||
        str.contains("end of Audiospur"))
    {
      audioTrack = false;
      foreach(QString string, audioList)
        Log::error(string);
      QTimer::singleShot(500, this, SLOT(onVLCGetLength()));
      return;
    }

    if(subtitle)
    {
      str = str.remove("\n");
      str = str.remove("\r");
      while(!str.at(0).isDigit())
      {
        str = str.remove(0,1);
      }
      subTitleList << str;
    }

    if(audioTrack)
    {
      str = str.remove("\n");
      str = str.remove("\r");
      while(!str.at(0).isDigit())
      {
        str = str.remove(0,1);
      }
      audioList << str;
    }

    if(str.contains("play state:"))
    {
        parseState(str);
        return;
    }

    if(str.contains("stop state:"))
    {
        sig_NewState(0);
        state = 0;
        return;
    }

    if(str.contains("Type 'pause' to continue"))
    {
      state = 2;
      sig_NewState(2);
      return;
    }

    if(str.contains("Subtitle Track") || 
        str.contains("Untertitelspur"))
    {
      subtitle = true;
      subTitleList.clear();
    }

    if(str.contains("Audio Track") || 
        str.contains("Audiospur"))
    {
      audioTrack = true;
      audioList.clear();
    }

    if(str.at(0).isDigit() && (isGetTime || isGetLength ))
    {
      parseTime(str);
    }
  }
}

void VLCProcess::onVLCReadStdOut()
{
  Log::player(Q_FUNC_INFO);
  QString url = process.readAllStandardOutput();
  Log::player(url);
}

void VLCProcess::onVLCFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  Log::player(Q_FUNC_INFO);
  Log::player("VLC finished. Returned: " + QString("%1").arg(exitCode) + 
              " Status: " + QString("%1").arg(exitStatus));
  process.start("vlc", argsList);
}

void VLCProcess::onYouTubeFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Log::player("youtube-dl finished. Returned: " + QString("%1").arg(exitCode) 
              + "; exit status: " + QString("%1").arg(exitStatus));
}

void VLCProcess::onYouTubeReadStdOut()
{
  Log::player(Q_FUNC_INFO);
  QString url = youtube_dl.readAllStandardOutput();
  url = url.remove("\n");
  Log::player(url);
}

void VLCProcess::parseState(QString str)
{
  Log::player(Q_FUNC_INFO);
  int s;
  for (int var = 0; var < str.length(); ++var)
  {
    if (str.at(var).isDigit())
    {
      s = str.at(var).digitValue();
    }
  }

  if(s == 4 && state != 0)
  {
    sig_NewState(0);
    state = 0;
    return;
  }

  if(s == 3 && state != 1)
  {
    sig_NewState(1);
    state = 1;
    return;
  }
}

void VLCProcess::parseTime(QString str)
{
  //Log::player(Q_FUNC_INFO);
  str = str.remove("\n");
  str = str.remove("\r");

  //Log::player( str );
  int t = str.toInt();
  //Log::player(QString("%1").arg(t));

  if(isMinutesForward) t = t + 300;
  if(isMinutesBackward) t = t - 300;
  if(isGetTime)
  {
     //Log::player("Time: " + QString("%1").arg(t));
     sig_WriteData("033|" + QString("%1").arg(t),false);
  }

  if(isGetLength)
  {
     Log::player("Length: " + QString("%1").arg(t));
     sig_WriteData("034|" + QString("%1").arg(t),true);
     //getTimeTimer.start(2000);
  }

//  if(isGetVolume)
//  {
//     Log::player("Volume: " + QString("%1").arg(t));
//     sig_WriteData("032|" + QString("%1").arg(t),false);
//  }

  isMinutesForward = false;
  isMinutesBackward = false;
  isGetTime = false;
  isGetLength = false;
}

void VLCProcess::play(QString str)
{
  Log::player(Q_FUNC_INFO);
  if(currentFile == str)
  {
    writeToVLCSocket("pause");
    writeToVLCSocket("normal");
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
    return;
  }

  currentFile = str;
//  if(QSysInfo::currentCpuArchitecture() == "arm")
//  {
    writeToVLCSocket("clear");
    writeToVLCSocket("add " + str);
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));

    sig_SetPlayed(currentFile);
    QTimer::singleShot(1000, this, SLOT(onVLCSubtitle()));
//  }
//  else
//  {
//    fileCopyThread->setSource(str);
//  }
}

void VLCProcess::playStream(QString str)
{
  Log::player(Q_FUNC_INFO);
  if(currentFile == str)
  {
    writeToVLCSocket("pause");
    writeToVLCSocket("normal");
    QTimer::singleShot(500, this, SLOT(onVLCStatus()));
    return;
  }

  currentFile = str;
  writeToVLCSocket("clear");
  writeToVLCSocket("add " + str);
  QTimer::singleShot(1000, this, SLOT(onVLCGetVolume()));

//  sig_SetPlayed(currentFile);
//  QTimer::singleShot(500, this, SLOT(onVLCSubtitle()));
}

void VLCProcess::onPlayBuffer()
{
  writeToVLCSocket("clear");
//  writeToVLCSocket("add " + str);
  writeToVLCSocket("add /tmp/buffer");

  sig_SetPlayed(currentFile);
  QTimer::singleShot(500, this, SLOT(onVLCSubtitle())); 
}

void VLCProcess::setVolume(QString str)
{
  writeToVLCSocket("volume " + str);
}

void VLCProcess::seek(QString str)
{
  Log::player(Q_FUNC_INFO);
  writeToVLCSocket("seek " + str);
}

void VLCProcess::setSubtitle(QString str)
{
  Log::player(Q_FUNC_INFO);
  writeToVLCSocket("strack " + str);
  QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::setAudio(QString str)
{
  Log::player(Q_FUNC_INFO);
  writeToVLCSocket("atrack " + str);
  QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::stop()
{
  Log::player(Q_FUNC_INFO);

  fileCopyThread->terminate();
  currentFile = "";
  getTimeTimer.stop();
  if(state == 2)
  {
    writeToVLCSocket("pause");
  }
  writeToVLCSocket("stop");
  writeToVLCSocket("clear");
  writeToVLCSocket("normal");
  QTimer::singleShot(500, this, SLOT(onVLCStatus()));
}

void VLCProcess::writeToVLCSocket(QString str)
{
  if(!isVLCConnected())
    return;

  vlcSocket.write(str.toLatin1().data());
  if(!vlcSocket.waitForBytesWritten(4000))
    Log::error("can't write to VLCSocket");


  vlcSocket.write(QString("\n").toLatin1().data());
  if(!vlcSocket.waitForBytesWritten(4000))
    Log::error("can't write newline to VLCSocket");
}
