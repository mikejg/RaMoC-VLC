#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStringList>
#include <QPixmap>

#include "log.h"
#include "socket.h"

class Server : public QObject
{
  Q_OBJECT

  private:
  QString ipAddress;
  QTcpServer* tcpServer;

  Socket* socket;

  public:
  Server(QObject *parent = 0);
  QString getIP() { return ipAddress; }

signals:
  void sig_ArchiveMovie(QString);
  void sig_Backward();
  void sig_DeleteMovie(QString);
  void sig_DeletePlaylist();
  void sig_GetArtistAlben(QString);
  void sig_GetAudio();
  void sig_GetFavorite();
  void sig_GetPlaylist();
  void sig_GetRandom();
  void sig_GetSubtitle();
  void sig_GetUnsortedFiles();
  void sig_IncSpeed();
  void sig_GetTracks(QString, QString);
  void sig_InsertMovie(QString, QString);
  void sig_InsertMovies();
  void sig_MinutesBackward();
  void sig_MinutesForward();
  void sig_Mute();
  void sig_NewState(quint8);
  void sig_Play(QString);
  void sig_PlayedSet();
  void sig_PlayStream(QString);
  void sig_PlayTrack(int);
  void sig_PlayYoutube(QString);
  void sig_RestoreMovie(QString);
  void sig_SendArtistAlben(QStringList);
  void sig_SendPlaylist(QString);
  void sig_SendUnsortedFiles(QString);
  void sig_SetAudio(QString);
  void sig_SetFavorite(QString);
  void sig_SetID3Tag(QString);
  void sig_SetSubtitle(QString);
  void sig_SetVolume(QString);
  void sig_SetTime(QString);
  void sig_Stop();
  void sig_ToggleSubtitle();
  void sig_WriteData(QString, bool);

public slots:
  void onNewConnection();
  void onDisconnected();
};

#endif // SERVER_H
