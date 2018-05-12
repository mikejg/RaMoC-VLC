#include "omx_process.h"

OMXProcess::OMXProcess(QObject *parent) : QObject(parent)
{
	playerProgramPath = "/usr/bin/omxplayer";

	connect(&playerProcess, SIGNAL(started()), this, SLOT(playerStartedHandler()));
	connect(&playerProcess, SIGNAL(finished(int,QProcess::ExitStatus)), 
					this, 					SLOT(playerFinishedHandler(int, QProcess::ExitStatus)));
}

OMXProcess::~OMXProcess()
{
}

void OMXProcess::play(const QString filename)
{
  Log::info(Q_FUNC_INFO);

	if (state == PLAYER_STATE_PLAYING)
    {
				state = PLAYER_STATE_PAUSED;
        sig_NewState(PLAYER_STATE_PAUSED);

        Log::player("Pausing omxplayer movie:" + currentMovieFilePath);
        Log::player("omxplayer state = PLAYER_STATE_PAUSE");
        playerProcess.write("p");
				return;
    }

	if (state == PLAYER_STATE_PAUSED)
    {
				state = PLAYER_STATE_PLAYING;
        sig_NewState(PLAYER_STATE_PLAYING);
        playerProcess.write("p");
        Log::player("omxplayer state = PLAYER_STATE_PLAYING");
        Log::player("Resuming omxplayer movie:" + currentMovieFilePath);
				return;
    }

  if (!QFile::exists(filename))
  {
      Log::player("Movie file does not exists:" + filename);
      return;
  }

    if (state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
		{
        //stop();
    }

    QStringList playerArgsList;
    playerArgsList << "-b" << "-t" << "1" << "-o" << "hdmi" << filename;
    currentMovieFilePath = filename;

    Log::player("omxplayer starting playing file:" + filename);

    //playing_Type = IMoviePlayer::PLAYING_MOVIE;
    //sig_PlayingMovie();
    playerProcess.start(playerProgramPath, playerArgsList);
}


void OMXProcess::stop()
{
    if (playerProcess.state() != QProcess::Running)
		{
        Log::player("Player ins not running" );
        return;
    }

    Log::player("omxplayer stoppe " + currentMovieFilePath);
    playerProcess.write("q");

    if (!playerProcess.waitForFinished(1000))
    {
        Log::player("omxplayer stopping timeout. Terminating...");
        playerProcess.terminate();
        if (!playerProcess.waitForFinished(2000))
        {
            Log::player("omxplayer terminate timeout. Killing...");
            playerProcess.kill();
        }
    }
}

void OMXProcess::playerFinishedHandler(int exitCode, QProcess::ExitStatus exitStatus)
{
    Log::player("omxplayer finished. Returned: " + QString("%1").arg(exitCode)
              + "; exit status: " + QString("%1").arg(exitStatus));

		state = PLAYER_STATE_IDLE;
    sig_NewState(PLAYER_STATE_IDLE);
    Log::player("omxplayer state = PLAYER_STATE_IDLE");
}

void OMXProcess::playerStartedHandler()
{
  Log::player("omxplayer started");
  Log::player("omxplayer state = PLAYER_STATE_PLAYING");

	state = PLAYER_STATE_PLAYING;
  sig_NewState(PLAYER_STATE_PLAYING);
  QTimer::singleShot(500, this, SLOT(setPlayed()));
}

void OMXProcess::setPlayed()
{
	Log::player(Q_FUNC_INFO);

	sig_SetPlayed(currentMovieFilePath);
}
