#include "socket.h"

Socket::Socket(QTcpSocket* ts, QObject* parent) : QObject(parent)
{
  tcpSocket = ts;
  
  settings = new QSettings("RaMoC", "server");
  string_NAS_IP             = settings->value("NAS_IP", " ").toString();
  string_Freigabe           = settings->value("Freigabe", " ").toString();
  string_User               = settings->value("User", " ").toString();
  string_Passwort           = settings->value("Passwort", " ").toString();
  string_DataBase           = settings->value("mysql_IP", "localhost").toString();
  string_MAC_Adresse        = settings->value("MAC_Adresse", " ").toString();
  string_TVHeadEndIP        = settings->value("TVHeadEndIP", " ").toString();
  string_TVHeadEndUser      = settings->value("TVHeadEndUser", " ").toString();
  string_TVHeadEndPassword  = settings->value("TVHeadEndPassword", " ").toString();

  connect(tcpSocket, SIGNAL(disconnected()),  this, SLOT(onDisconnected()));
  connect(tcpSocket, SIGNAL(readyRead()),     this, SLOT(onReadData()));
}

Socket::~Socket()
{
  //trenne alle Signal Slot Verbindungen
  tcpSocket->disconnect();

  tcpSocket->disconnectFromHost();
}


void Socket::handleGetSettings()
{
//    QString str_State = QString("%1").arg(player->playerState());
    QString str_State = "0";
    QString str_Settings = "001|" +
                  string_NAS_IP + "|" +
                  string_Freigabe + "|" +
                  string_User + "|" +
                  string_Passwort + "|" +
                  string_DataBase + "|" +
                  string_MAC_Adresse + "|" +
                  string_TVHeadEndIP + "|" +
                  string_TVHeadEndUser + "|" +
                  string_TVHeadEndPassword + "|" +
                  str_State + "|";
    writeData(str_Settings, true);
}

void Socket::handleNewTVChannel(QString str)
{
  QStringList strList = str.split("\n");
  if(strList.size() > 0)
  {
    QString string = strList.at(0);
    string = string.remove("\n");
    QStringList list = string.split("|");
    if(list.size() == 3)
    {
      sig_PlayStream(list.at(1));
    }
  }
}

void Socket::handleNextArtistAlben()
{
  if(!stringList_ArtistAlben.isEmpty())
    {
      writeData(ArtistAlben + "|" + stringList_ArtistAlben.first(), true);
      stringList_ArtistAlben.removeFirst();
    }
  else
  {
      writeData(endArtistAlben, true );
  }
}

void Socket::handlePlay(QStringList strList)
{
      if(strList.size() == 2)
      {
        //connected with PlayerWindow::onPlay(QString)
        sig_Play(strList.at(1));
      }
}

void Socket::onDisconnected()
{
  Log::tcp("Verbindung mit " + peerAddress() + " wurde getrennte");
  sig_Disconnected();
}

void Socket::onNewState(quint8 state)
{
  writeData(newState + "|" + QString("%1").arg(state),true);
}

void Socket::onPlayedSet()
{
  writeData(playedSet, true);
}

void Socket::onReadData()
{
  int len = tcpSocket->bytesAvailable();

  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_4_0);

  char char_Input[len];
  in.readRawData ( char_Input, len );
  QString string = QString::fromUtf8(char_Input, len-1);
  Log::tcp("Neue Daten: " + string);

  if(!string.startsWith(newTVChannel))
  {
    string = string.remove("\n");
    strList_Data = string.split("|");
  }
 
  if(string.startsWith(archiveMovie))
    //connected with DataBase::onArchive(QString);
    sig_ArchiveMovie(strList_Data.at(1));

  if(string.startsWith(ArtistAlben))
    //connected with DataBase::onGetArtistAlben(QString);
    sig_GetArtistAlben(strList_Data.at(1));

  if(string.startsWith(backward))
      sig_Backward();

  if(string.startsWith(bell))
    system("omxplayer /home/pi/RaMoC/beep.mp3");

//  if(string.startsWith(bufferAndPlay))
//    handleBufferAndPlay(strList_Data);

  if(string.startsWith(deleteMovie))
    //connected with DataBase::onDelete(QString);
    sig_DeleteMovie(strList_Data.at(1));

  if(string.startsWith(deletePlaylist))
    //connected with Playerwindow::onDeletePlaylist()
    sig_DeletePlaylist();

  if(string.startsWith(forward))
    sig_IncSpeed();

  if(string.startsWith(getAudio))
    sig_GetAudio();

  if(string.startsWith(getFavorite))
    sig_GetFavorite();

  if(string.startsWith(getSettings))
    handleGetSettings();

  if(string.startsWith(getSubtitle))
    sig_GetSubtitle();

  if(string.startsWith(getRandom))
    sig_GetRandom();

  if(string.startsWith(insertAlbum))
    //connected with DataBase::onTracksFrom_A_A(QString, QString);
    sig_GetTracks(strList_Data.at(1), strList_Data.at(2));

  if(string.startsWith(insertMovie))
    //connected with MainWindow::onInsertMovie(QString, QString);
    sig_InsertMovie(strList_Data.at(1), strList_Data.at(3));

  if(string.startsWith(minutesBackward))
    sig_MinutesBackward();

  if(string.startsWith(minutesForward))
    sig_MinutesForward();

  if(string.startsWith(mute))
    sig_Mute();

  if(string.startsWith(newTVChannel))
    handleNewTVChannel(string);

  if(string.startsWith(nextArtistAlben))
    handleNextArtistAlben();

  if(string.startsWith(play))
    handlePlay(strList_Data);

  if(string.startsWith(playTrack))
    //connected with PlayerWindow::playTrack(QString)
    sig_PlayTrack(strList_Data.at(1).toInt());

  if(string.startsWith(playYoutube))
    //connected with PlayerWindow::onPlayYoutube(QString)
    sig_PlayYoutube(strList_Data.at(1));

  if(string.startsWith(restoreMovie))
    //connected with DataBase::onRestore(QString);
    sig_RestoreMovie(strList_Data.at(1));

  if(string.startsWith(scannForNewFiles))
  {
    //connected with MainWindow::onInsertMovies()
    sig_InsertMovies();
  }

  if(string.startsWith(sendPlaylist))
    //connected with PlayerWindow::onGetPlaylist
    sig_GetPlaylist();
  
  if(string.startsWith(setAudio))
    //connected with Player::onSetSubtitle
    sig_SetAudio(strList_Data.at(1));

  if(string.startsWith(setFavorite))
    //connected with PlayerWindow::onSetFavorite
    sig_SetFavorite(strList_Data.at(1));

  if(string.startsWith(setID3Tag))
    //connected with DataBase::onSetID3Tag
    sig_SetID3Tag(string);

  if(string.startsWith(setSubtitle))
    //connected with Player::onSetSubtitle
    sig_SetSubtitle(strList_Data.at(1));

  if(string.startsWith(setVolume))
    //connected with Player::onSetVolume
    sig_SetVolume(strList_Data.at(1));

  if(string.startsWith(setTime))
    //connected with Player::onSeek
    sig_SetTime(strList_Data.at(1));

  if(string.startsWith(stop))
    sig_Stop();
  
  if(string.startsWith(toggleSubtitle))
    sig_ToggleSubtitle();

  if(string.startsWith(unsortedFiles))
  {
    //connectet with DataBase::onGetUnsortedFiles()
    sig_GetUnsortedFiles();
  }
}

void Socket::onReceivePlaylist(QString str)
{
  Log::info(Q_FUNC_INFO);
  writeData(sendPlaylist + "|" + str, true);
}

void Socket::onReceiveArtistAlben(QStringList strList)
{
  Log::info(Q_FUNC_INFO);
  stringList_ArtistAlben = strList;
  if(!stringList_ArtistAlben.isEmpty())
  {
    writeData(ArtistAlben + "|"  + stringList_ArtistAlben.first(), true);
    stringList_ArtistAlben.removeFirst();
  }
}

void Socket::onUnsortedFiles(QString str)
{
  writeData(unsortedFiles + "|" + str, true);
}

void Socket::onWriteData(QString string_Data, bool debug)
{
  string_Data = string_Data + "\n";
  if(debug)
    Log::tcp("Sende: " + string_Data);

    tcpSocket->write(string_Data.toUtf8());
}

void Socket::writeData(QString string_Data, bool debug)
{
  string_Data = string_Data + "\n";
  if(debug)
    Log::tcp("Sende: " + string_Data);

    tcpSocket->write(string_Data.toUtf8());
}

