#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    currentIndex = -1;
    vlcProcess = new VLCProcess(this);
    omxProcess = new OMXProcess(this);

    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    isRadio = false;

    Phonon::createPath(mediaObject, audioOutput);
    connect(vlcProcess, SIGNAL(sig_NewState(quint8)), 
            this,       SIGNAL(sig_NewState(quint8)));
    connect(vlcProcess, SIGNAL(sig_SetPlayed(QString)), 
            this,       SIGNAL(sig_SetPlayed(QString)));
    connect(vlcProcess, SIGNAL(sig_WriteData(QString, bool)),
            this,        SIGNAL(sig_WriteData(QString, bool)));

    connect(mediaObject, SIGNAL(finished()),
            this,        SLOT(onTrackFinished()));
    connect(mediaObject, SIGNAL(metaDataChanged()),
            this,        SLOT(onMetaDataChanged()));

    connect(omxProcess, SIGNAL(sig_NewState(quint8)), 
            this,       SIGNAL(sig_NewState(quint8)));
    connect(omxProcess, SIGNAL(sig_SetPlayed(QString)), 
            this,       SIGNAL(sig_SetPlayed(QString)));

    connect(&youtube_dl, SIGNAL(readyReadStandardOutput()), 
                   this, SLOT(onYouTubeReadStdOut()));
    connect(&youtube_dl, SIGNAL(finished(int,QProcess::ExitStatus)), 
                   this, SLOT(onYouTubeFinished(int,QProcess::ExitStatus)));
}

Player::~Player()
{

}

void Player::unUsed()
{
  Log::player("Unused");
}

QString Player::genJsonTracks(QList<Track> tracklist)
{
  QString jsonString;
  jsonString = "[";
  foreach(Track track, tracklist)
  {
    jsonString = jsonString +
                 "{\"id\":\"" + track.ramoc_ID + "\"," +
                 "\"album_id\":\"" + track.album_ID + "\"," +
                 "\"title\":\"" + track.title + "\"," +
                 "\"pfad\":\"" + track.path + "\"," +
                 "\"artist\":\"" + track.artist + "\"," +
                 "\"album\":\"" + track.album + "\"," +
                 "\"favorite\":\"" + track.favorite + "\"," +
                 "\"sampler\":\"" + track.sampler + "\"" +
                 "},";
  }
  //letztes Komma wegschneiden
  if(jsonString.length() > 1)
    jsonString = jsonString.left(jsonString.length() - 1);

  jsonString = jsonString + "]";
//  qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << jsonString;
  return jsonString;
}

Track Player::getCurrentTrack()
{
  Track returnTrack;
  if(currentIndex > -1)
    returnTrack = playlist.at(currentIndex);

  return returnTrack;
}

void Player::onBackward()
{
  vlcProcess->rewind();
}

void Player::onDeletePlaylist()
{
  onStop();
  currentIndex = -1;
  playlist.clear();
}

void Player::onGetPlaylist()
{
  QList<Track> playlist = getPlaylist();
  QString jsonString = genJsonTracks(playlist);

  sig_SendPlaylist(jsonString + "|" + QString("%1").arg(currentIndex));
}

void Player::onGetSubtitle()
{
  vlcProcess->getSubtitle();
}

void Player::onGetAudio()
{
  vlcProcess->getAudio();
}
void Player::onIncSpeed()
{
  vlcProcess->faster();
}

void Player::onMetaDataChanged()
{
  QMultiMap<QString, QString> map = mediaObject->metaData();
  QStringList strList;
  QString strValue;

  strList = map.values("ARTIST");
  foreach(strValue, strList)
  {
    track.artist = strValue;
    Log::player("ARTIST: " + strValue);
  }

  strList = map.values("TITLE");
  foreach(strValue, strList)
  {
    track.title = strValue;
    Log::player("TITLE: " + strValue);
  }
  sig_PlayingTrack(track);
}

void Player::onMinutesBackward()
{
  vlcProcess->minutesBackward();
}

void Player::onMinutesForward()
{
  vlcProcess->minutesForward();
}

void Player::onMute()
{
  vlcProcess->mute();
}

void Player::onPlay(QString str)
{
  Log::player(Q_FUNC_INFO);
  vlcProcess->play(str);
  sig_SetBlack();
  //omxProcess->play(str);
}

void Player::onPlayStream(QString str)
{
  Log::player(Q_FUNC_INFO);
  //omxProcess->stop();
  mediaObject->stop();
  vlcProcess->playStream(str);
}

void Player::onPlayTrack(int tracknumber)
{
  Log::player(Q_FUNC_INFO);
  if(isRadio)
  {
    onStop();
    return;
  }

  if(tracknumber >= playlist.size())
  {
    return;
  }

  if(currentIndex == tracknumber && mediaObject->state() == Phonon::PlayingState )
  {
    mediaObject->pause();
    sig_WriteData("004|2", true);
    return;
  }

  if(currentIndex == tracknumber && mediaObject->state() == Phonon::PausedState )
  {
    mediaObject->play();
    sig_WriteData("004|1", true);
    return;
  }

  currentIndex = tracknumber;
  track = playlist.at(tracknumber);
  track.playlistPos = QString("%1").arg(currentIndex);

  QString path = playlist.at(tracknumber).path;
  Log::player(path);

  mediaObject->setCurrentSource(Phonon::MediaSource(
                                      playlist.at(tracknumber).path));
  mediaObject->play();
//  sig_PlayingTrack(track);
  sig_WriteData("104|" + track.playlistPos, true);

//musicObject->setCurrentSource(Phonon::MediaSource("http://www.schwarze-welle.de:7500"));
//      musicObject->setCurrentSource(Phonon::MediaSource("http://swr-swr3-live.cast.addradio.de/swr/swr3/live/mp3/128/stream.mp3"));
}

void Player::onPlayRadio(QString str)
{
  Log::player(Q_FUNC_INFO);
  isRadio = true;
  mediaObject->setCurrentSource(Phonon::MediaSource(str));
  mediaObject->play();
}

void Player::onPlayYoutube(QString str)
{
  Log::player(Q_FUNC_INFO);
  Log::player(str);

  QStringList youtube_dlArgsList;
  youtube_dlArgsList << "-g" << "-f" << "best" << str;
  youtube_dl.start("/usr/bin/youtube-dl", youtube_dlArgsList);
}

void Player::onReceiveTracks(QList<Track> trackList)
{
  Log::player(Q_FUNC_INFO);
  QString jsonString;

  jsonString = "[";
  foreach(Track track, trackList)
  {
    playlist << track;
    jsonString = jsonString + 
                 "{\"id\":\"" + track.ramoc_ID + "\"," +
                 "\"album_id\":\"" + track.album_ID + "\"," +
                 "\"title\":\"" + track.title + "\"," +
                 "\"pfad\":\"" + track.path + "\"," +
                 "\"artist\":\"" + track.artist + "\"," +
                 "\"album\":\"" + track.album + "\"," +
                 "\"favorite\":\"" + track.favorite + "\"," +
                 "\"sampler\":\"" + track.sampler + "\"" +
                 "},"; 
  }
  //letztes Komma wegschneiden
  if(jsonString.length() > 1)
    jsonString = jsonString.left(jsonString.length() - 1);

  jsonString = jsonString + "]";
  sig_WriteData("103|" + jsonString, true);
}

void Player::onStop()
{
  Log::player(Q_FUNC_INFO);
  vlcProcess->stop(); 
  //omxProcess->stop();
  mediaObject->stop();
  isRadio = false;
  sig_VLCStopped();
}

void Player::onSetSubtitle(QString str)
{
  vlcProcess->setSubtitle(str);
}

void Player::onSeek(QString str)
{
  vlcProcess->seek(str);
}

void Player::onSetAudio(QString str)
{
  vlcProcess->setAudio(str);
}

void Player::onSetVolume(QString str)
{
  vlcProcess->setVolume(str);
}

void Player::onTrackFinished()
{
  currentIndex++;
  onPlayTrack(currentIndex);
}

void Player::onToggleSubtitle()
{
  Log::player(Q_FUNC_INFO);
}
void Player::onUpdateID3Tag_Title(QString oldTitle, QString newTitle)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.title == oldTitle)
       playlist[i].title = newTitle;
  }
  sig_WriteData("114", true);
}

void Player::onUpdateID3Tag_Album(QString oldAlbum, QString newAlbum)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.album == oldAlbum)
       playlist[i].album = newAlbum;
  }
  sig_WriteData("114", true);
}

void Player::onUpdateID3Tag_Artist(QString oldArtist, QString newArtist)
{
  Track tr;
  for(int i = 0; i < playlist.size(); i++)
  {
    tr = playlist.at(i);
    if(tr.artist == oldArtist)
       playlist[i].artist = newArtist;
  }
  sig_WriteData("114", true);
}

void Player::onYouTubeFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
      Log::player("youtube-dl finished. Returned: " + QString("%1").arg(exitCode) 
                        + "; exit status: " + QString("%1").arg(exitStatus));
}

void Player::onYouTubeReadStdOut()
{
    Log::player(Q_FUNC_INFO);
    QString url = youtube_dl.readAllStandardOutput();
    url = url.remove("\n");
    Log::player(url);
    onPlayStream(url);
}
