#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMimeDatabase>
#include <QMimeType>
#include <QProcess>

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

#include "log.h"
#include "database.h"
#include "vlc_process.h"
#include "omx_process.h"

class Player : public QObject
{
    Q_OBJECT

  private:
		int 				  currentIndex;
    QList<Track>  playlist;
    VLCProcess*   vlcProcess;
    OMXProcess*   omxProcess;
    Track         track;
    QProcess      youtube_dl;

    Phonon::MediaObject* mediaObject;
    Phonon::AudioOutput* audioOutput;

    QString 		 genJsonTracks(QList<Track> tracklist);

  public:
    explicit 		 Player(QObject *parent = 0);
                 ~Player();
    QList<Track> getPlaylist() { return playlist; }
    int     		 getCurrentIndex() { return currentIndex; }
		Track 			 getCurrentTrack();

  signals:
	  void sig_NewState(quint8);
	  void sig_SendPlaylist(QString);
	  void sig_SetPlayed(QString);
	  void sig_SetPlayed(Track);
    void sig_VLCStopped();
    void sig_PlayingTrack(Track);
    void sig_SetBlack();
	  void sig_WriteData(QString, bool);

  public slots:
    void onDeletePlaylist();
    void onBackward();
	  void onGetPlaylist();
    void onGetSubtitle();
	  void onIncSpeed();
	  void onMinutesBackward();
	  void onMinutesForward();
	  void onMute();
	  void onPlay(QString);
	  void onPlayStream(QString);
    void onPlayTrack(int);
    void onPlayYoutube(QString);
	  void onReceiveTracks(QList<Track>);
    void onSetSubtitle(QString);
	  void onStop();
	  void onToggleSubtitle();
    void onTrackFinished();
    void onUpdateID3Tag_Title(QString, QString);
    void onUpdateID3Tag_Album(QString, QString);
    void onUpdateID3Tag_Artist(QString, QString);
    void onYouTubeFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onYouTubeReadStdOut();
};

#endif
