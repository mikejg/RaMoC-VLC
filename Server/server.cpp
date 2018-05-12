#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
  tcpServer = new QTcpServer(this);

  if (!tcpServer->listen(QHostAddress::Any, 4444))
    Log::error("Server " + tcpServer->errorString());

  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // use the first non-localhost IPv4 address
  for (int i = 0; i < ipAddressesList.size(); ++i)
  {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
        ipAddressesList.at(i).toIPv4Address())
    {
      ipAddress = ipAddressesList.at(i).toString();
      break;
    }
  }

  // if we did not find one, use IPv4 localhost
  if (ipAddress.isEmpty())
  ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void Server::onNewConnection()
{
  socket = new Socket(tcpServer->nextPendingConnection(), this);
  Log::info("Server wurde mit " + socket->peerAddress() +" verbunden");

  connect(this,   SIGNAL(sig_SendPlaylist(QString)),
          socket, SLOT(onReceivePlaylist(QString)));
  connect(this,   SIGNAL(sig_SendUnsortedFiles(QString)), 
          socket, SLOT(onUnsortedFiles(QString)));
  connect(this,   SIGNAL(sig_SendArtistAlben(QStringList)), 
          socket, SLOT(onReceiveArtistAlben(QStringList)));

  connect(socket, SIGNAL(sig_ArchiveMovie(QString)),         this,
                  SIGNAL(sig_ArchiveMovie(QString)));
  connect(socket, SIGNAL(sig_Backward()),                    this,
                  SIGNAL(sig_Backward()));
  connect(socket, SIGNAL(sig_DeleteMovie(QString)),          this,
                  SIGNAL(sig_DeleteMovie(QString)));
  connect(socket, SIGNAL(sig_DeletePlaylist()),              this,
                  SIGNAL(sig_DeletePlaylist()));
  connect(socket, SIGNAL(sig_Disconnected()),                this,
                  SLOT(onDisconnected()));
  connect(socket, SIGNAL(sig_GetArtistAlben(QString)),       this,
                  SIGNAL(sig_GetArtistAlben(QString)));
  connect(socket, SIGNAL(sig_GetFavorite()),                 this,
                  SIGNAL(sig_GetFavorite()));
  connect(socket, SIGNAL(sig_GetSubtitle()),                 this,
                  SIGNAL(sig_GetSubtitle()));
  connect(socket, SIGNAL(sig_GetTracks(QString, QString)), this,
                  SIGNAL(sig_GetTracks(QString, QString)));
  connect(socket, SIGNAL(sig_GetPlaylist()),                 this,
                  SIGNAL(sig_GetPlaylist()));
  connect(socket, SIGNAL(sig_GetRandom()),                 this,
                  SIGNAL(sig_GetRandom()));
  connect(socket, SIGNAL(sig_GetUnsortedFiles()),            this,
                  SIGNAL(sig_GetUnsortedFiles()));
  connect(socket, SIGNAL(sig_IncSpeed()),                    this,
                  SIGNAL(sig_IncSpeed()));
  connect(socket, SIGNAL(sig_InsertMovies()),                this,
                  SIGNAL(sig_InsertMovies()));
  connect(socket, SIGNAL(sig_InsertMovie(QString, QString)), this,
                  SIGNAL(sig_InsertMovie(QString, QString)));
  connect(socket, SIGNAL(sig_MinutesBackward()),             this,
                  SIGNAL(sig_MinutesBackward()));
  connect(socket, SIGNAL(sig_MinutesForward()),              this,
                  SIGNAL(sig_MinutesForward()));
  connect(socket, SIGNAL(sig_Mute()),                        this,
                  SIGNAL(sig_Mute()));
  connect(socket, SIGNAL(sig_Play(QString)),                 this,
                  SIGNAL(sig_Play(QString)));
  connect(socket, SIGNAL(sig_PlayStream(QString)),           this,
                  SIGNAL(sig_PlayStream(QString)));
  connect(socket, SIGNAL(sig_PlayTrack(int)),                this,
                  SIGNAL(sig_PlayTrack(int)));
  connect(socket, SIGNAL(sig_PlayYoutube(QString)),           this,
                  SIGNAL(sig_PlayYoutube(QString)));
  connect(socket, SIGNAL(sig_RestoreMovie(QString)),         this,
                  SIGNAL(sig_RestoreMovie(QString)));
  connect(socket, SIGNAL(sig_SetFavorite(QString)),          this,
                  SIGNAL(sig_SetFavorite(QString)));
  connect(socket, SIGNAL(sig_SetID3Tag(QString)),            this,
                  SIGNAL(sig_SetID3Tag(QString)));
  connect(socket, SIGNAL(sig_SetSubtitle(QString)),            this,
                  SIGNAL(sig_SetSubtitle(QString)));
  connect(socket, SIGNAL(sig_Stop()),                        this,
                  SIGNAL(sig_Stop()));
  connect(socket, SIGNAL(sig_ToggleSubtitle()),              this,
                  SIGNAL(sig_ToggleSubtitle()));

  connect(this, SIGNAL(sig_NewState(quint8)), socket, SLOT(onNewState(quint8)));
  connect(this, SIGNAL(sig_PlayedSet()),      socket, SLOT(onPlayedSet()));
  connect(this, SIGNAL(sig_WriteData(QString, bool)),
          socket, SLOT(onWriteData(QString, bool)));
}

void Server::onDisconnected()
{
  sender()->deleteLater();
}
