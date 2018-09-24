#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include <QSettings>
#include <QHostAddress>
#include <QDataStream>
#include <QFileInfo>
#include <QDir>
#include <QTimer>

#include "log.h"
#include "constants.h"
#include "structs.h"

using namespace constants;

class Socket : public QObject
{
    Q_OBJECT

  private:
    QTcpSocket*   tcpSocket;

    QSettings* settings;
    QString string_NAS_IP;
    QString string_MAC_Adresse;
    QString string_Freigabe;
    QString string_Passwort;
    QString string_User;
    QString string_DataBase;
    QString string_TVHeadEndIP;
    QString string_TVHeadEndUser;
    QString string_TVHeadEndPassword;

    QStringList strList_Data;
    QStringList stringList_ArtistAlben;
    
    bool isPlayStream;
    void handleGetSettings();
    void handleInsertMovie();
    void handleNewTVChannel(QString);
    void handleNextArtistAlben();
    void handlePlay(QStringList);

public:
    explicit Socket(QTcpSocket* ts, QObject *parent = 0);
    ~Socket();

    QString peerAddress() { return tcpSocket->peerAddress().toString(); }
    void writeData(QString string_Data, bool debug = false);

signals:
    void sig_ArchiveMovie(QString);
    void sig_Backward();
    void sig_DeleteMovie(QString, QString);
    void sig_DeletePlaylist();
    void sig_Disconnected();
    void sig_GetArtistAlben(QString);
    void sig_GetAudio();
    void sig_GetFavorite();
    void sig_GetPlaylist();
    void sig_GetRandom();
    void sig_GetSubtitle();
    void sig_GetTracks(QString, QString);
    void sig_GetUnsortedFiles();
    void sig_IncSpeed();
    void sig_InsertMovie(Movie);
    void sig_InsertMovies();
    void sig_MinutesBackward();
    void sig_MinutesForward();
    void sig_Mute();
    void sig_Play(QString);
    void sig_PlayStream(QString);
    void sig_PlayRadio(QString);
    void sig_PlayTrack(int);
    void sig_PlayYoutube(QString);
    void sig_RestoreMovie(QString);
    void sig_SetAudio(QString);
    void sig_SetFavorite(QString);
    void sig_SetID3Tag(QString);
    void sig_SetSubtitle(QString);
    void sig_SetVolume(QString);
    void sig_SetTime(QString);
    void sig_Stop();
    void sig_ToggleSubtitle();

public slots:
    void onDisconnected();
    void onFreePlayStream() { isPlayStream = true; }
    void onNewState(quint8);
    void onPlayedSet();
    void onReadData();
    void onReceiveArtistAlben(QStringList);
    void onReceivePlaylist(QString);
    void onUnsortedFiles(QString);
    void onWriteData(QString, bool);
};

#endif // SOCKET_H

