#ifndef OMXPROCESS_H
#define OMXPROCESS_H

#include <QObject>

#include "log.h"
#include "database.h"

class OMXProcess : public QObject
{
  Q_OBJECT

  private:
    qint8 state;
    QString currentMovieFilePath;
    QString playerProgramPath;
    QProcess playerProcess;


  public:
    typedef enum {
                PLAYER_STATE_IDLE       =   0x00,
                PLAYER_STATE_PLAYING    =   0x01,
                PLAYER_STATE_PAUSED     =   0x02,
                PLAYER_STATE_ERROR      =   0xFF
                 } MOVIE_PLAYER_STATE;
 
    explicit 		 OMXProcess(QObject *parent = 0);
                 ~OMXProcess();
    void play(const QString filename);
    void stop();

  signals:
    void sig_NewState(quint8 s);
    void sig_SetPlayed(QString);

  public slots:
    void playerFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus);
    void playerStartedHandler();
    void setPlayed();

};

#endif
