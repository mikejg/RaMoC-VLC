#include "database.h"

DataBase::DataBase(QObject *parent, QString connectionName ) : QObject(parent)
{
  this->connectionName = connectionName;

  db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
  db.setHostName("localhost");
  db.setDatabaseName("ramoc");
  db.setUserName("ramocuser");
  db.setPassword("ramoc");

  networkAccessManager = new QNetworkAccessManager(this);

  if(!db.open())
    Log::error("Fehler beim oeffnen der DB auf " );
  else
    Log::db("DB auf localhost offen");
}

DataBase::~DataBase()
{
  QSqlDatabase::removeDatabase(connectionName);
  db.close();
}

QString DataBase::getAlbumCover(QString albumID)
{
  if(!db.isOpen())
    db.open();

  QString returnString;

  QSqlQuery query(db);
  query.exec("SELECT m_album.hasImage, m_album.image, m_album.id FROM m_album "
             "WHERE m_album.id = " + albumID);


  while (query.next())
  {
    if(query.value(0).toInt() == 1)
    returnString = query.value(1).toString();
  }

  return returnString;
}

void DataBase::onGetRandom()
{
    Log::db(Q_FUNC_INFO);
    QDateTime dateTime = QDateTime::currentDateTime();
    dateTime = dateTime.addMonths(-3);

    if(!db.isOpen())
        db.open();

    QList<Track> return_List;

    QSqlQuery query(db);
    query.exec("SELECT m_title.id, m_title.album, m_title.title, m_title.pfad,  m_artist.name, "
               "m_album.name, m_album.sampler, m_title.wertung, m_title.gespielt FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_title.gespielt < " + QString("%1").arg(dateTime.toTime_t()) + 
               " ORDER BY RAND() LIMIT 50");

    Log::db(query.lastError().databaseText());
    Log::db(query.lastQuery());

    while (query.next())
    {
      Track track;
      track.ramoc_ID =  query.value(0).toString();
      track.album_ID = query.value(1).toString();
      track.title =  query.value(2).toString();
      track.path =  query.value(3).toString();
      track.artist =  query.value(4).toString();
      track.album =  query.value(5).toString();
      track.sampler =  query.value(6).toString();
      track.favorite = query.value(7).toString();

      return_List << track;
    }
    sig_SendTracks(return_List);
    return ;
}

void DataBase::onGetFavorite()
{
    if(!db.isOpen())
        db.open();

    QList<Track> return_List;

    QSqlQuery query(db);
    query.exec("SELECT m_title.id, m_title.album, m_title.title, "
               "m_title.pfad, m_artist.name, "
               "m_album.name, m_album.sampler, m_title.wertung FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_title.wertung = 1 "
               "ORDER BY RAND() LIMIT 50"); // LIMIT 50");
    qDebug() << query.lastError();
    qDebug() << query.lastQuery();

    while (query.next())
    {
      Track track;
      track.ramoc_ID =  query.value(0).toString();
      track.album_ID =  query.value(1).toString();
      track.title =  query.value(2).toString();
      track.path =  query.value(3).toString();
      track.artist =  query.value(4).toString();
      track.album =  query.value(5).toString();
      track.sampler =  query.value(6).toString();
      track.favorite = query.value(7).toString();

      return_List << track;
    }
  //connected with PlayerWindow::onReceiveTracks(QList<Track>)
  sig_SendTracks(return_List);
    return ;
}

void DataBase::insertEpisode(Movie episode)
{
  QNetworkReply* reply;
  QHttpMultiPart *multiPart_Movie = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QEventLoop loop;

  QString id_File  = getID("t_Datei", "dateiname", episode.file_Path);

   QHttpPart textPart_ID;
   textPart_ID.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id_movie\""));
   textPart_ID.setBody(episode.ramoc_ID.toUtf8());

   QHttpPart textPart_ID_File;
   textPart_ID_File.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id_file\""));
   textPart_ID_File.setBody(id_File.toUtf8());

   multiPart_Movie->append(textPart_ID);
   multiPart_Movie->append(textPart_ID_File);

   reply= networkAccessManager->post(QNetworkRequest(QUrl("http://localhost/insertTVShow.php")), multiPart_Movie);
   multiPart_Movie->setParent(reply); // delete the multiPart with the reply
   connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
   loop.exec();
   reply->deleteLater();
}
bool DataBase::renameFile(QString oldName, QString newName)
{
  Log::db(oldName);
  Log::db(newName);

  oldName = oldName.replace(" ", "\\ ");
  oldName = oldName.replace(":", "\\:");
  newName = newName.replace(" ", "\\ ");
  newName = newName.replace(":", "\\:");
  
  QString execString;
  execString = "mv " + oldName + " " + newName;

  Log::db(execString);
  int errorCode = system(execString.toUtf8().data());
//  Log::db(QString("ErrorCode: %1").arg(errorCode));
  if(errorCode == 0) 
  {
    return true;
  }

  return false;
}

void DataBase::insertMovie(Movie movie)
{
  Log::db(Q_FUNC_INFO);
  Log::db("Titel: " + movie.title);
  Log::db("File: " + movie.file_Path);
  Log::db("Serie: " + movie.serie);
  Log::db("Archive: " + movie.archive);
  QNetworkReply* reply;
  QHttpMultiPart *multiPart_Movie = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QEventLoop loop;

  QString id_Actor;
  QString newFilePath;
  QString systemString;

  QHttpMultiPart *multiPart_Actor;

  if(movie.file_Path.contains("ä"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("ä", "ae");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("Ä"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("Ä", "Ae");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("ö"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("ö", "oe");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("Ö"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("Ö", "Oe");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("ü"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("ü", "ue");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("Ü"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("Ü", "Ue");

    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("ß"))
  {
    QFile file(movie.file_Path);
    newFilePath = movie.file_Path;
    newFilePath = newFilePath.replace("ß", "ss");
    if(!renameFile(movie.file_Path, newFilePath))
    {
      Log::error("Fehler beim umbenennen" + movie.file_Path);
      return;
    }
  movie.file_Path = newFilePath;
  }

  if(movie.file_Path.contains("&"))
    movie.file_Path = movie.file_Path.replace("&", "%26");

 //     trimmFilePath(movie.file_Path, "&");

  if(movie.title.contains("&"))
    movie.title = movie.title.replace("&", "%26");

  QString id_Movie = getID("t_Film", "titel", movie.title);

  QString id_File  = getID("t_Datei", "dateiname", movie.file_Path);

  QString id_Genre1 = getID("t_Genre", "genre1", " ");
  if(movie.strList_Genres.size() > 0)
    id_Genre1 = getID("t_Genre", "genre1", movie.strList_Genres.at(0));

  QString id_Genre2 = getID("t_Genre", "genre2", " ");
  if(movie.strList_Genres.size() > 1)
    id_Genre2 = getID("t_Genre", "genre2", movie.strList_Genres.at(1));

  QString id_Genre3 = getID("t_Genre", "genre3", " ");
  if(movie.strList_Genres.size() > 2)
    id_Genre3 = getID("t_Genre", "genre3", movie.strList_Genres.at(2));

  QString id_Genre4 = getID("t_Genre", "genre4", " ");
  if(movie.strList_Genres.size() > 3)
    id_Genre4 = getID("t_Genre", "genre4", movie.strList_Genres.at(3));

  movie.overview = movie.overview.replace("'", "''");

   QHttpPart textPart_Poster;
   textPart_Poster.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"cover\""));
   textPart_Poster.setBody(movie.poster_Hash.toUtf8());

   QHttpPart textPart_Backdrop;
   textPart_Backdrop.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"backdrop\""));
   textPart_Backdrop.setBody(movie.backdrop_Hash.toUtf8());

   QHttpPart textPart_Overview;
   textPart_Overview.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"beschreibung\""));
   textPart_Overview.setBody(movie.overview.toUtf8());

   QHttpPart textPart_Genre1;
   textPart_Genre1.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"genre1\""));
   textPart_Genre1.setBody(id_Genre1.toUtf8());

   QHttpPart textPart_Genre2;
   textPart_Genre2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"genre2\""));
   textPart_Genre2.setBody(id_Genre2.toUtf8());

   QHttpPart textPart_Genre3;
   textPart_Genre3.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"genre3\""));
   textPart_Genre3.setBody(id_Genre3.toUtf8());

   QHttpPart textPart_Genre4;
   textPart_Genre4.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"genre4\""));
   textPart_Genre4.setBody(id_Genre4.toUtf8());

   QHttpPart textPart_ID;
   textPart_ID.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id\""));
   textPart_ID.setBody(id_Movie.toUtf8());

   QHttpPart textPart_ID_File;
   textPart_ID_File.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id_file\""));
   textPart_ID_File.setBody(id_File.toUtf8());

   QHttpPart textPart_Trailer;
   textPart_Trailer.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"trailer\""));
   textPart_Trailer.setBody(movie.trailer.toUtf8());

   QHttpPart textPart_Runtime;
   textPart_Runtime.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"laufzeit\""));
   textPart_Runtime.setBody(movie.runtime.toUtf8());

   QHttpPart textPart_Vote_Average;
   textPart_Vote_Average.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"note\""));
   textPart_Vote_Average.setBody(movie.vote_Average.toUtf8());

   QHttpPart textPart_Vote_Count;
   textPart_Vote_Count.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"stimmen\""));
   textPart_Vote_Count.setBody(movie.vote_Count.toUtf8());

   QHttpPart textPart_Year;
   textPart_Year.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"jahr\""));
   textPart_Year.setBody(movie.year.toUtf8());

   QHttpPart textPart_Serie;
   textPart_Serie.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"serie\""));
   textPart_Serie.setBody(movie.serie.toUtf8());

   QHttpPart textPart_fsk;
   textPart_fsk.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"fsk\""));
   textPart_fsk.setBody(movie.fsk.toUtf8());

   QHttpPart textPart_Archive;
   textPart_Archive.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"archive\""));
   textPart_Archive.setBody(movie.archive.toUtf8());

   multiPart_Movie->append(textPart_Poster);
   multiPart_Movie->append(textPart_Backdrop);
   multiPart_Movie->append(textPart_Overview);
   multiPart_Movie->append(textPart_Genre1);
   multiPart_Movie->append(textPart_Genre2);
   multiPart_Movie->append(textPart_Genre3);
   multiPart_Movie->append(textPart_Genre4);
   multiPart_Movie->append(textPart_ID);
   multiPart_Movie->append(textPart_ID_File);
   multiPart_Movie->append(textPart_Trailer);
   multiPart_Movie->append(textPart_Runtime);
   multiPart_Movie->append(textPart_Vote_Average);
   multiPart_Movie->append(textPart_Vote_Count);
   multiPart_Movie->append(textPart_Year);
   multiPart_Movie->append(textPart_Serie);
   multiPart_Movie->append(textPart_fsk);
   multiPart_Movie->append(textPart_Archive);

   Log::db("Schreibe " + movie.title + " in Datenbank");
   sig_NewInfo("Schreibe " + movie.title + " in Datenbank");
   reply= networkAccessManager->post(QNetworkRequest(QUrl("http://localhost/updateMovie.php")), multiPart_Movie);
   multiPart_Movie->setParent(reply); // delete the multiPart with the reply
   connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
   loop.exec();
   reply->deleteLater();

   foreach(Person person, movie.list_Person)
   {
     multiPart_Actor = new QHttpMultiPart(QHttpMultiPart::FormDataType);
     id_Actor = getID("t_Person", "name", person.name);

     QHttpPart textPart_Portrait;
     textPart_Portrait.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"portrait\""));
     textPart_Portrait.setBody(person.profile_Hash.toUtf8());

     QHttpPart textPart_ID_Actor;
     textPart_ID_Actor.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id_actor\""));
     textPart_ID_Actor.setBody(id_Actor.toUtf8());

     QHttpPart textPart_ID_Movie;
     textPart_ID_Movie.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"id_movie\""));
     textPart_ID_Movie.setBody(id_Movie.toUtf8());

     QHttpPart textPart_Character;
     textPart_Character.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"character\""));
     person.character = person.character.replace("'", "''");
     textPart_Character.setBody(person.character.toUtf8());

     multiPart_Actor->append(textPart_Portrait);
     multiPart_Actor->append(textPart_ID_Actor);
     multiPart_Actor->append(textPart_ID_Movie);
     multiPart_Actor->append(textPart_Character);

     Log::db("Schreibe " + person.name + " in Datenbank");

     sig_NewInfo("Schreibe " + person.name + " in Datenbank");
     reply = networkAccessManager->post(QNetworkRequest(QUrl("http://localhost/updateActor.php")), multiPart_Actor);
     multiPart_Actor->setParent(reply); // delete the multiPart with the nReply_Film
     connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();
     reply->deleteLater();
   }
}

bool DataBase::open()
{
  if(db.isOpen()) db.close();

  db.setHostName("localhost");
  db.setDatabaseName("ramoc");
  db.setUserName("ramocuser");
  db.setPassword("ramoc");

  if(!db.open())
  {
    Log::error("Fehler beim oeffnen der DB auf localhost");
    return false;
  }

  Log::db("DB auf localhost offen");
  return true;
}

void DataBase::onArchive(QString ramoc_ID)
{
  Log::db(Q_FUNC_INFO);

  QSqlQuery query(db);
  QStringList fileList;
  QString stringExec;
  QString newPath;

  if(!open())
    return;

  query.exec("UPDATE t_Film set archives = 1 WHERE id = " + ramoc_ID);
  fileList = getFiles(ramoc_ID);
  foreach(QString strFileName, fileList)
  {
    QStringList strListSplit = strFileName.split("/");
    QString newName;
    foreach(QString part, strListSplit)
    {
      if(part == "Movie" || part == "TVShow")
      {
        newName = newName + "/" + "Archive";
      }
      newName = newName + "/" + part;
    }
    newName = newName.remove(0,1);
    query.exec("UPDATE t_Datei set dateiname = '" + newName + "' WHERE "
               "dateiname = '" + strFileName + "'");

    QFileInfo fileInfo(newName);
    newPath = fileInfo.absolutePath();

    //Log::db(strFileName + " : " + newName + " : " + newPath);

    strFileName = strFileName.replace(" ", "\\ ");
    newName = newName.replace(" ", "\\ ");
    newPath = newPath.replace(" ", "\\ ");

    Log::db(strFileName + " : " + newName + " : " + newPath);
    stringExec ="mkdir --parents " + newPath +" ; "+ "mv " + strFileName + " " 
                + newName;
    system(qPrintable(stringExec));
  }
}

void DataBase::onRestore(QString ramoc_ID)
{
  QSqlQuery query(db);
  QStringList fileList;
  QString stringExec;
  QString newPath;

  if(!open())
    return;

  query.exec("UPDATE t_Film set archives = 0 WHERE id = " + ramoc_ID);
  fileList = getFiles(ramoc_ID);
  foreach(QString strFileName, fileList)
  {
    QStringList strListSplit = strFileName.split("/");
    QString newName;
    foreach(QString part, strListSplit)
    {
      if(part != "Archive" )
      {
        newName = newName + "/" + part;
      }
    }
    newName = newName.remove(0,1);
    query.exec("UPDATE t_Datei set dateiname = '" + newName + "' WHERE "
               "dateiname = '" + strFileName + "'");

    QFileInfo fileInfo(newName);
    newPath = fileInfo.absolutePath();

    Log::db(strFileName + " : " + newName + " : " + newPath);

    strFileName = strFileName.replace(" ", "\\ ");
    newName = newName.replace(" ", "\\ ");
    newPath = newPath.replace(" ", "\\ ");

    stringExec ="mkdir --parents " + newPath +" ; "+ "mv " + strFileName + " " + newName;
    system(stringExec.toLatin1().data());
  }
}

void DataBase::onSetFavorite(QString ramoc_ID)
{
  Log::db(Q_FUNC_INFO);

  QSqlQuery query(db);
  QString pfad;
  QString wertung;
  QString lastPlayed;
  QString comment;

  if(!open())
    return;

  query.exec("SELECT m_title.id, m_title.pfad, m_title.wertung, m_title.gespielt "
             "FROM m_title "
               "WHERE "
               "m_title.id = " + ramoc_ID);

  if(query.first())
  {
    pfad       = query.value(1).toString();
    lastPlayed = query.value(3).toString();
    wertung = query.value(2).toString();
    wertung = (wertung == "1") ? "0" : "1";
    comment = QString("QMDB#%1#%2").arg(wertung).arg(lastPlayed); 
    QByteArray fileName = QFile::encodeName( pfad );
    TagLib::MPEG::File f(fileName);
    if(f.isValid())
    {
      TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();
      id3v2->setComment(Qt4StringToString(comment));
      f.save();
    }
    query.exec("UPDATE m_title SET wertung = " + wertung +
               " WHERE id = " + ramoc_ID);
  }
}

void DataBase::onSetID3Tag(QString str)
{
  Log::db(Q_FUNC_INFO);
  Log::db(str);

  str = str.remove("\n");

  QStringList arguments = str.split("|");

  QString ramocID = arguments.at(1);
  QString title   = arguments.at(2);
  QString album   = arguments.at(3);
  QString artist  = arguments.at(4);

  Track track = getTrack(ramocID);

  if(title != track.title)
  {
    Log::info("Aendere Titel");
    updateTitle(track, title);
    sig_UpdateID3Tag_Title(track.title, title);
  }

  if(album != track.album)
  {
    Log::info("Aendere Album");
    updateAlbum(track, album);
    sig_UpdateID3Tag_Album(track.album, album);
  }

  if(artist != track.artist)
  {
    Log::info("Aendere Artist");
    updateArtist(track, artist);
    sig_UpdateID3Tag_Artist(track.artist, artist);
  }
}

void DataBase::onSetPlayed(Track track)
{
  Log::db(Q_FUNC_INFO);
  QSqlQuery query(db);
  QString pfad;
  QString lastPlayed;
  QString comment;
  QString wertung;

  QDateTime dateTime = QDateTime::currentDateTime();
  lastPlayed = QString("%1").arg(dateTime.toTime_t());

  if(!open())
    return;

  query.exec("SELECT m_title.id, m_title.pfad, m_title.wertung "
             "FROM m_title "
               "WHERE "
               "m_title.id = " + QString("%1").arg(track.ramoc_ID));

  if(query.first())
  {
    pfad       = query.value(1).toString();
    wertung = query.value(2).toString();
    comment = QString("QMDB#%1#%2").arg(wertung).arg(lastPlayed); 
    QByteArray fileName = QFile::encodeName( pfad );
    TagLib::MPEG::File f(fileName);
    if(f.isValid())
    {
      TagLib::ID3v2::Tag* id3v2 = f.ID3v2Tag();
      id3v2->setComment(Qt4StringToString(comment));
      f.save();
    }
    query.exec("UPDATE m_title SET gespielt = " + lastPlayed +
               " WHERE id = " + QString("%1").arg(track.ramoc_ID));
  }
}

void DataBase::setSampler(QString ramoc_ID)
{
  QSqlQuery query(db);

  if(!open())
    return;

  query.exec("UPDATE m_album SET sampler = 1 "
             "WHERE id = " + ramoc_ID);
}

void DataBase::onSetPlayed(QString string_File)
{

	Log::db(Q_FUNC_INFO);
  QSqlQuery query(db);
  QString string_tmp = string_File.replace("'", "''");

  if(!open())
    return;

  if(query.exec("UPDATE t_Datei set played = 1 WHERE dateiname = '" + string_tmp + "'"))
  {
    Log::db("Set Played " + string_File);
    //connected with Socket::onPlayedSet
    sig_PlayedSet();
  }
}

QStringList DataBase::getFileList()
{
  QSqlQuery query(db);
  QStringList stringListReturn;
  QString genre;
  QString tmp;

  if(!open())
    return stringListReturn;


  query.exec("SELECT dateiname FROM t_Datei");
  while(query.next())
  {
    stringListReturn << query.value(0).toString();
  }


  query.exec("SELECT pfad FROM m_title");

  while(query.next())
  {
    stringListReturn << query.value(0).toString();
  }

  return stringListReturn;
}

QList<Movie> DataBase::getTVShow()
{
  QNetworkReply* reply;
  QEventLoop loop;
  QList<QVariant> result;
  QList<Movie> returnList;
  reply = networkAccessManager->get(QNetworkRequest(QUrl("http://localhost/getTVShowList.php")));
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  QString string = reply->readAll();
  QJsonParseError* jError = new QJsonParseError();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), jError);
  result = jsonDocument.toVariant().toList();
  foreach(QVariant variant, result)
  { 
    Movie movie;
    QVariantMap map = variant.toMap();
    movie.title = map["titel"].toString();
    movie.ramoc_ID = map["id"].toString();
    returnList << movie;
  } 
  return returnList;
}

QList<Movie> DataBase::getAllTVShow()
{
  Log::db(Q_FUNC_INFO);
  QNetworkReply* reply;
  QEventLoop loop;
  QList<QVariant> result;
  QList<Movie> returnList;
  reply = networkAccessManager->get(QNetworkRequest(QUrl("http://localhost/getAllTVShowList.php")));
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  QString string = reply->readAll();
  QJsonParseError* jError = new QJsonParseError();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), jError);
  result = jsonDocument.toVariant().toList();
  foreach(QVariant variant, result)
  { 
    Movie movie;
    QVariantMap map = variant.toMap();
    movie.title = map["titel"].toString();
    movie.ramoc_ID = map["id"].toString();
    returnList << movie;
  } 
  return returnList;
}

QString DataBase::getID(QString table, QString column, QString value)
{
  QNetworkReply* reply;
  QEventLoop loop;
  QList<QVariant> result;
  QString str_Return = "1";

  value = value.replace("'", "''");
  reply = networkAccessManager->get(QNetworkRequest(QUrl("http://localhost/getId.php?table=" + table +
                                                                   "&column=" + column +
                                                                   "&value=" + value)));
  connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  QString string = reply->readAll();
  QJsonParseError* jError = new QJsonParseError();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), jError);
  result = jsonDocument.toVariant().toList();
  foreach(QVariant variant, result)
  {
    QVariantMap map = variant.toMap();
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << table << " " 
    //                                                              << column << ": " 
    //                                                              << map["id"].toString();
    str_Return = map["id"].toString();
  }
  return str_Return;
}

void DataBase::onGetUnsortedFiles()
{
    QStringList stringList_databaseFiles = getFileList();
    QStringList strList_MovieFiles;
    QStringList strList_Files;

    //Lese alle Dateien aus /Bigpod/Filme und ueberpruefe sie
    //mit der Datenbank

    strList_Path.clear();
    strList_Path.append("/media");
    strList_Path.append("/mnt/smb/Movie");
    //strList_Path.append("/mnt/smb/Archive");
    QString path;
    while(strList_Path.size() > 0)
    {
      path = strList_Path.takeFirst();
      check_HDD(path, &strList_Files);
    }

    foreach(QString strFile, strList_Files)
    {
      if(!stringList_databaseFiles.contains(strFile, Qt::CaseInsensitive))
          strList_MovieFiles << strFile;
    }

  QString strReturn = "[";

  for (int i = 0; i < strList_MovieFiles.size(); i++)
  {
    //letzter Eintrag ohne abschliessendem ','
    if(i == strList_MovieFiles.size() -1)
      strReturn = strReturn + "{\"path\":\"" + strList_MovieFiles.at(i) + "\"}";
    else
      strReturn = strReturn + "{\"path\":\"" + strList_MovieFiles.at(i) + "\"},";
  }

  strReturn = strReturn + "]";

  sig_SendUnsortedFiles(strReturn);
  //return strReturn;
}

void DataBase::check_HDD(QString string_DirPath, QStringList* stringList)
{
      if(string_DirPath.contains("Trailer"))
          return;

      QDir dir = QDir(string_DirPath);
      if(!dir.exists())
      {
        Log::error("DataBase::check_HDD " + string_DirPath + 
                   " Verzeichnis existiert nicht");
        return;
      }

      QFileInfoList fileInfoList = dir.entryInfoList();
      QFileInfo fileInfo;

      foreach(fileInfo, fileInfoList)
      {
        if(fileInfo.fileName() != "." && fileInfo.fileName() != "..")
        {
          if(fileInfo.isDir())
          {
            strList_Path.append(fileInfo.absoluteFilePath());
            //check_HDD(fileInfo.absoluteFilePath(), stringList);
          }
          else
          {
            if(fileInfo.absoluteFilePath().contains("Movie"))
            {
              stringList->append(fileInfo.absoluteFilePath());
            }
          }
        }
      }
}

void DataBase::trimmFilePath(QString& file_path, QString c)
{
  QFileInfo info(file_path);
  QFile file(file_path);
  QDir dir = info.dir();
  QString title = info.baseName().replace(c, " -");
  file_path = dir.absolutePath() + "/" + title + "." + info.suffix();
  file.rename(file_path);
}

void DataBase::onDelete(QString movieID, QString del)
{
  QStringList strList_FilesToDelete = getFiles(movieID);

  QNetworkReply* reply;
  QHttpMultiPart *multiPart_Movie = new QHttpMultiPart(QHttpMultiPart::FormDataType);
  QEventLoop loop;

   QHttpPart textPart_ID;
   textPart_ID.setHeader(QNetworkRequest::ContentDispositionHeader, 
                         QVariant("form-data; name=\"id_movie\""));
   textPart_ID.setBody(movieID.toUtf8());

   multiPart_Movie->append(textPart_ID);

   reply= networkAccessManager->post(QNetworkRequest(
                                     QUrl("http://localhost/deleteFilm.php")),
                                     multiPart_Movie);
   multiPart_Movie->setParent(reply); // delete the multiPart with the reply
   connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
   loop.exec();
   reply->deleteLater();

  if(del == "true")
  {
  foreach(QString fileName, strList_FilesToDelete)
  {
     Log::info("Delete " + fileName);
     QFile file(fileName);
     if(!file.remove())
      Log::error("Fehler beim Loeschen von " + fileName);
  }
  }
}

QStringList DataBase::getFiles(QString movie_ID)
{
  QStringList returnList;
  QSqlQuery query(db);

  if(!open())
    return returnList;

  query.exec("SELECT film, t_Datei.dateiname from t_Datei_Film "  
             "INNER JOIN t_Datei on t_Datei_Film.datei = t_Datei.id "  
             "WHERE film = " + movie_ID );

  while(query.next())
  {
    returnList << query.value(1).toString();
  }

  return returnList;
}

QStringList DataBase::getUrl()
{
    if(!db.isOpen())
      db.open();
  QStringList list;
  QSqlQuery query(db);
  query.exec("SELECT pfad FROM m_title");

  while(query.next())
  {
    list << query.value(0).toString();
  }

  return list;
}

void DataBase::onArtistAlben(QString str)
{
  Log::info(Q_FUNC_INFO);
  Log::info(str);
  QStringList returnList;
  QStringList list_Artist;

  QSqlQuery query(db);
  QSqlQuery queryAlben(db);
  QString db_Artist;

  if(!open())
  sig_SendArtistAlben(returnList);
  //  return returnList;

  if(str == "Sampler")
  sig_SendArtistAlben(getSampler());
  //  return getSampler();

  QString str0 = str.mid(0,1);
  QString str1 = str.mid(1,1);
  QString str2 = str.mid(2,1);

  query.exec("SELECT name FROM m_artist "
             "WHERE name LIKE '" + str0 + "%' "
             "OR name LIKE '" + str1 + "%' "
             "OR name LIKE '" + str2 + "%' "
             "order by name");

  while(query.next())
  {
    QString string = query.value(0).toString();
    db_Artist = query.value(0).toString();
    db_Artist.replace("'", "''");

    queryAlben.exec("SELECT DISTINCT m_artist.name, m_album.name FROM m_title "
                   "INNER JOIN m_artist ON m_title.artist = m_artist.id "
                   "INNER JOIN m_album ON m_title.album = m_album.id "
                   "WHERE "
                   "m_artist.name = '" + db_Artist + "'");
    while(queryAlben.next())
    {
      string = string + "|" + queryAlben.value(1).toString();
    }
   
   Log::db(string);
   returnList << string;
  }

  //connected with Socket::onReceiveArtistAlben(QStringList)
  sig_SendArtistAlben(returnList);
//  return returnList;
}

QStringList DataBase::getSampler()
{
  QStringList returnList;
  QString string = "Sampler";
  QSqlQuery query(db);

  if(!open())
    return returnList;

  query.exec("SELECT name FROM m_album "
             "WHERE "
             "sampler = 1");

    while(query.next())
    {
      string = string + "|" + query.value(0).toString();
    }

   returnList << string;

   return returnList;
}

void DataBase::onGetTracks(QString artist, QString album)
{
  Log::db(Q_FUNC_INFO);
  QList<Track> returnList;
  QSqlQuery query(db);
  QString db_Artist= artist;
  QString db_Album = album;
  db_Artist.replace("'", "''");
  db_Album.replace("'", "''");

  if(!open())
      return ;

  if(artist == "Sampler")
  {
    query.exec("SELECT m_title.id, m_title.album, m_title.title, m_title.wertung, "
               "m_title.pfad, m_artist.name, m_album.name, m_album.sampler "
               "FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_album.name = '" + db_Album + "'");
  }
  else
  {
    query.exec("SELECT m_title.id, m_title.album, m_title.title, m_title.wertung, "
               "m_title.pfad, m_artist.name, m_album.name, m_album.sampler "
               "FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_artist.name = '" + db_Artist + "' "
               "AND "
               "m_album.name = '" + db_Album + "'");
  }
  while(query.next())
  {
    Track track;
    track.ramoc_ID = query.value(0).toString();
    track.album_ID = query.value(1).toString();
    track.title  = query.value(2).toString();
    track.favorite = query.value(3).toString();
    track.path  = query.value(4).toString();
    track.album = album;
    track.artist = query.value(5).toString();
    track.sampler = query.value(7).toString();

    returnList << track;
  }
 
  //connected with PlayerWindow::onReceiveTracks(QList<Track>)
  sig_SendTracks(returnList);
  return ;
}

Track DataBase::getTrack(QString ramocID)
{
  QSqlQuery query(db);
  Track track;
  if(!open())
    return track;

    query.exec("SELECT m_title.id, m_title.album, m_title.artist, m_title.title, m_title.wertung, "
               "m_title.pfad, m_artist.name, m_album.name, m_album.sampler FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_title.id = " + ramocID);
 
  while(query.next())
  {
    track.ramoc_ID = query.value(0).toString();
    track.album_ID = query.value(1).toString();
    track.artist_ID = query.value(2).toString();
    track.title  = query.value(3).toString();
    track.favorite = query.value(4).toString();
    track.path  = query.value(5).toString();
    track.artist = query.value(6).toString();
    track.album = query.value(7).toString();
    track.sampler = query.value(8).toString();
  }

  Log::info("ramoc_ID : " + track.ramoc_ID);
  Log::info("album_ID : " + track.album_ID);
  Log::info("artist_ID: " + track.artist_ID);
  Log::info("Titel    : " + track.title);
  Log::info("Album    : " + track.album);
  Log::info("Artist   : " + track.artist);

  return track; 
}

QList<Track> DataBase::getTrack_Album(QString albumID)
{
  QList<Track> returnList;
  QSqlQuery query(db);
  if(!open())
    return returnList;

    query.exec("SELECT m_title.id, m_title.album, m_title.title, m_title.wertung, "
               "m_title.pfad, m_artist.name, m_album.name, m_album.sampler FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_title.album = " + albumID);
 
  Log::db(query.lastQuery());

  while(query.next())
  {
    Track track;
    track.ramoc_ID = query.value(0).toString();
    track.album_ID = query.value(1).toString();
    track.title  = query.value(2).toString();
    track.favorite = query.value(3).toString();
    track.path  = query.value(4).toString();
    track.artist = query.value(5).toString();
    track.album = query.value(6).toString();
    track.sampler = query.value(7).toString();
    returnList.append(track);
  }

  return returnList; 
}

QList<Track> DataBase::getTrack_Artist(QString artistID)
{
  QList<Track> returnList;
  QSqlQuery query(db);
  if(!open())
    return returnList;

    query.exec("SELECT m_title.id, m_title.album, m_title.title, m_title.wertung, "
               "m_title.pfad, m_artist.name, m_album.name, m_album.sampler FROM m_title "
               "INNER JOIN m_artist ON m_title.artist = m_artist.id "
               "INNER JOIN m_album ON m_title.album = m_album.id "
               "WHERE "
               "m_title.artist = " + artistID);
 
  while(query.next())
  {
    Track track;
    track.ramoc_ID = query.value(0).toString();
    track.album_ID = query.value(1).toString();
    track.title  = query.value(2).toString();
    track.favorite = query.value(3).toString();
    track.path  = query.value(4).toString();
    track.artist = query.value(5).toString();
    track.album = query.value(6).toString();
    track.sampler = query.value(7).toString();
    returnList.append(track);
  }

  return returnList; 
}
void DataBase::insertMetaPaket(MetaPaket mp)
{
    if(!db.isOpen())
      db.open();

  QString strError;
  QSqlError sqlError;

  int keyArtist = key(mp.artist, "m_artist");
  int keyAlbum = key(mp.album, "m_album");
  int keyGenre = key(mp.genre, "m_genre");
  int keyYear = key(mp.year, "m_year");
  mp.pfad = mp.pfad.toUtf8();
  mp.title = mp.title.toUtf8();

  int id = 0;
  QSqlQuery query(db);
  
  //Sampler setzen
  query.exec("UPDATE m_album SET m_album.sampler = "
             + mp.sampler +
             " WHERE m_album.id = "
             + QString("%1").arg(keyAlbum));

  //In m_album den key von artist reinschreiben
  query.exec("UPDATE m_album SET m_album.artist = "
             + QString("%1").arg(keyArtist) +
             " WHERE m_album.id = "
             + QString("%1").arg(keyAlbum));
  
  //Nach Cover sehen
  query.exec("SELECT m_album.id, m_album.hasImage FROM m_album "
              "WHERE "
              "m_album.id = " + QString("%1").arg(keyAlbum));

  if(query.first())
  {
    if(!query.value(1).toInt())
    {
      QString file = mp.pfad;
      QByteArray fileName = QFile::encodeName( file );
      const char *encodedName = fileName.constData();

      TagLib::MPEG::File mpegFile(encodedName);
      TagLib::ID3v2::Tag* tag = mpegFile.ID3v2Tag();

      QImage image;
      TagLib::ID3v2::FrameList l = tag->frameList("APIC");

      if(!l.isEmpty())
      {
        TagLib::ID3v2::AttachedPictureFrame *f =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());
        image.loadFromData((const uchar *) f->picture().data(), f->picture().size());
        QByteArray pixmapBytes;
        QBuffer pixmapBuffer(&pixmapBytes);
        pixmapBuffer.open(QIODevice::WriteOnly);
        image.save(&pixmapBuffer, "PNG");
        const QString blobimage = pixmapBytes.toBase64();
        query.exec("UPDATE m_album SET m_album.image = '"
                   + blobimage + "' "
                   " WHERE m_album.id = "
                   + QString("%1").arg(keyAlbum));


        query.exec("UPDATE m_album SET m_album.hasImage = 1 "
                   "WHERE m_album.id = "
                   + QString("%1").arg(keyAlbum));
      }
    }
  }

  //Testen ob die Tabelle leer ist;
  query.exec("SELECT id FROM m_title");
  if(query.isActive() && query.isSelect())
  {
    if(!query.first())
      id = 1;
  }

  //es gibt schon Einträge
  if(!id)
  {
    query.exec("SELECT id FROM m_title ORDER BY id");
    if(query.isActive() && query.isSelect())
    {
      QSqlRecord record = query.record();
      if (query.last())
          id = query.value(record.indexOf("id")).toInt() + 1;
    }
  }

  query.prepare("INSERT INTO m_title (id, title, artist, album, genre, year, tracknr, playcounter, "
                "erfasst, gespielt, wertung, pfad) "
                "VALUES (:id, :title, :artist, :album, :genre, "
                ":year, :tracknr, :playcounter, "
                ":erfasst, :gespielt, :wertung, :pfad) ");

    query.bindValue(":id", id);
    query.bindValue(":title", mp.title);
    query.bindValue(":artist", keyArtist);
    query.bindValue(":album", keyAlbum);
    query.bindValue(":genre", keyGenre);
    query.bindValue(":year", keyYear);
    query.bindValue(":tracknr", mp.tracknr);
    query.bindValue(":playcounter", 0);
    query.bindValue(":erfasst", mp.erfasst);
    query.bindValue(":gespielt", mp.gespielt);
    query.bindValue(":wertung", mp.wertung);
    query.bindValue(":pfad", mp.pfad);

    query.exec();
    sqlError = query.lastError();
    if(sqlError.isValid())
    {
      Log::error(sqlError.text());
      Log::error(query.lastQuery());
    }
}

void DataBase::updateAlbum(Track track, QString album)
{
  album = album.replace("'", "''");

  if(!db.isOpen())
      db.open();
  QSqlQuery query(db);
  query.exec("UPDATE m_album SET name = '" + album + "' "
             "WHERE id = " + track.album_ID);

  TagLib::String strAlbum = Qt4StringToString(album);
  QList<Track> trackList = getTrack_Album(track.album_ID);
  foreach(Track tr, trackList)
  {
    TagLib::FileRef f(tr.path.toUtf8());
    if(!f.isNull())
    {
      f.tag()->setAlbum(strAlbum);
      f.save();
    }
  }

}

void DataBase::updateArtist(Track track, QString artist)
{

  if(!db.isOpen())
      db.open();
  QString keyArtist = QString("%1").arg(key(artist, "m_artist"));
  Log::info("Neuer keyArtist = " + keyArtist);

  TagLib::String strArtist = Qt4StringToString(artist);
  QString path;
  QSqlQuery query(db);
  query.exec("SELECT m_title.id, m_title.pfad, m_title.artist FROM m_title "
               "WHERE "
               "m_title.artist = " + track.artist_ID);
 
  while(query.next())
  {
    path = query.value(1).toString();
    TagLib::FileRef f(path.toUtf8());
    if(!f.isNull())
    {
      f.tag()->setArtist(strArtist);
      f.save();
    }
  }

  query.exec("UPDATE m_album SET artist = " + keyArtist + " WHERE artist = " + track.artist_ID);
  query.exec("UPDATE m_title SET artist = " + keyArtist + " WHERE artist = " + track.artist_ID);
  query.exec("DELETE FROM m_artist WHERE id = " + track.artist_ID);
}

void DataBase::updateTitle(Track track, QString title)
{
  title = title.replace("'", "''");

  if(!db.isOpen())
      db.open();
  QSqlQuery query(db);
  query.exec("UPDATE m_title SET title = '" + title + "' "
             "WHERE id = " + track.ramoc_ID);

  TagLib::String string = Qt4StringToString(title);

  TagLib::FileRef f(track.path.toUtf8());
  if(!f.isNull())
  {
    f.tag()->setTitle(string);
    f.save();
  }
}

int DataBase::key(QString string_Content, QString string_Table)
{
  //Log::error(Q_FUNC_INFO);
    if(!db.isOpen())
      db.open();
  string_Content = string_Content.replace("'", "''");

  QSqlQuery query(db);

  query.exec("SELECT id FROM " + string_Table);
  if(query.isActive() && query.isSelect())
  {
    if(!query.first())
    {
      if(string_Table == "t_album")
      {
        query.exec("INSERT INTO " + string_Table + " (id, name, hasImage) "
                    "VALUES (1, '" + string_Content +"', 0)");
        return 1;
      }
      query.exec("INSERT INTO " + string_Table + " (id, name) "
                 "VALUES (1, '" + string_Content + "')");
      return 1;
    }
  }

  //Testen ob der key in der Tabelle ist
  query.exec("SELECT id, name FROM " + string_Table + " WHERE "
              "name ='" + string_Content + "'");
  QSqlRecord record = query.record();
  if (query.next())
    return query.value(record.indexOf("id")).toInt();

  //Key ist nicht in der Tabelle -> Eintrag erstellen
  //erstmal die letzte bzw höchste id suchen
  query.exec("SELECT id FROM " + string_Table + " ORDER BY id");
  if(query.isActive() && query.isSelect())
  {
    record = query.record();
    if (query.last())
    {
      int id = query.value(record.indexOf("id")).toInt() + 1;
      if(string_Table == "t_album")
      {
        query.exec("INSERT INTO " + string_Table + " (id, name, hasImage) "
                   "VALUES (" + QString("%1").arg(id)  + ", '" + string_Content +"', 0)");
        return id;
      }
      query.exec("INSERT INTO " + string_Table + " (id, name) "
                 "VALUES (" + QString("%1").arg(id)  + ", '" + string_Content + "')");
      return id;
    }
  }
  return -1;
}
