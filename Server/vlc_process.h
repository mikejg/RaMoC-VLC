#ifndef VLCPROCESS_H
#define VLCPROCESS_H

#include <QObject>
#include <QTimer>
#include <QMimeDatabase>
#include <QMimeType>
#include <QProcess>
#include <QLocalSocket>
#include <QDir>
#include <QDataStream>
#include <QFile>

#include "log.h"
#include "database.h"
#include "fileCopyThread.h"

class VLCProcess : public QObject
{
    Q_OBJECT

private:
    QString currentMovieFilePath;

    qint8 state;
    QString      currentFile;
    QMimeDatabase           mimeDatabase;
    QMimeType               mimeType;
    QWidget*                musicWidget;
    QProcess                process;
    int                     timerID;
    QProcess                youtube_dl;
    QLocalSocket            vlcSocket;
    QStringList             argsList;
    QStringList             strackList;
    QStringList             subTitleList;
    bool                    isFastForward;
    bool                    isRewind;
    bool                    isMinutesBackward;
    bool                    isMinutesForward;
    FileCopyThread*         fileCopyThread;

    bool isVLCConnected();
    void parseState(QString);
    void parseTime(QString);
    void writeToVLCSocket(QString str);

public:
    typedef enum {
                PLAYER_STATE_IDLE       =   0x00,
                PLAYER_STATE_PLAYING    =   0x01,
                PLAYER_STATE_PAUSED     =   0x02,
                PLAYER_STATE_ERROR      =   0xFF
    } MOVIE_PLAYER_STATE;

    explicit 		 VLCProcess(QObject *parent = 0);
                 ~VLCProcess();
    void faster();
    void getSubtitle();
    void rewind();
    void minutesBackward();
    void minutesForward();
    void mute();
    void play(QString str);
    void setSubtitle(QString str);
    void stop();

protected:
//    void timerEvent(QTimerEvent *event);

signals:
    void sig_NewState(quint8 s);
    void sig_SetPlayed(QString);
	  void sig_WriteData(QString, bool);

public slots:
//	void onSetPlayed();
//	void onStarted();
  void onVLCFinished(int, QProcess::ExitStatus);
  void onVLCReadError();
  void onVLCReadStdOut();
  void onVLCRestart();
  void onVLCStarted();
  void onVLCStatus();
  void onVLCSubtitle();
  void onVLCSocketRead();
  void onYouTubeFinished(int exitCode, QProcess::ExitStatus exitStatus);
  void onYouTubeReadStdOut();
  void onPlayBuffer();
};

#endif
