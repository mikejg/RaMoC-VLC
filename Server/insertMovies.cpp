#include "insertMovies.h"
#include <QImage>

InsertMovies::InsertMovies(QObject *parent ) : QThread(parent)
{
}

void InsertMovies::run()
{
  networkAccessManager  = new QNetworkAccessManager();
  eventLoop             = new QEventLoop();
  strList_Files         = new QStringList();
  strList_MovieFiles    = new QStringList();
  strList_TVShowFiles    = new QStringList();
  strList_MP3Files    = new QStringList();
 
  database = new DataBase(0, "Thread_Connection");
  connect(database, SIGNAL(sig_NewInfo(QString)), this, SIGNAL(sig_NewInfo(QString)));

  strList_Path.clear();
//  strList_Path.append("/media");
 // strList_Path.append("/mnt/smb/Archive");
   strList_Path.append("/mnt/smb/Movie");
//  strList_Path.append("/mnt/smb/Music");
  //strList_Path.append("/mnt/smb/TVShow");
  QString path;
  strList_DBFiles = database->getFileList();
  Log::info("Start check_HDD");
  while(strList_Path.size() > 0)
  {
    path = strList_Path.takeFirst();
    check_HDD(path, strList_Files);
  }
  Log::info(QString("End check_HDD found %1").arg(strList_Files->size()));
  sig_ProgressBar_Show();
  sig_ProgressBar_SetRange(0, strList_Files->size());
  
  check_NewFiles();
//  insertMovie();
//  insertTVShow();
//  insertMP3Files();
  delete database;
}

/*
 * Liest alle Filenamen aus dem Verzeichnis und
 * speichert sie in stringList_Files
 */
void InsertMovies::check_HDD(QString string_DirPath, QStringList* stringList)
{
  sig_NewInfo("Scanne " + string_DirPath);

      if(string_DirPath.contains("Trailer") || 
          string_DirPath.contains("Export"))
          return;

      QDir dir = QDir(string_DirPath);
      if(!dir.exists())
      {
        Log::error("InsertMovies::check_HDD " 
                   + string_DirPath + " existiert nicht");
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
            //check_HDD(fileInfo.absoluteFilePath(), stringList);
            strList_Path.append(fileInfo.absoluteFilePath());
          }
          else
          {
            stringList->append(fileInfo.absoluteFilePath());
            //if(!strList_DBFiles.contains(fileInfo.absoluteFilePath(),
            //                             Qt::CaseInsensitive))
            //{
            //  stringList->append(fileInfo.absoluteFilePath());
            //}
            //else
            //{
            //  strList_DBFiles.removeAll(fileInfo.absoluteFilePath());
            //}
          }
        }
      }
}

void InsertMovies::check_NewFiles()
{
    QString name;

    QString tmpString;
    int i = 0;
    foreach(tmpString, *strList_Files)
    {
      sig_ProgressBar_SetValue(i);
      if(!strList_DBFiles.contains(tmpString, Qt::CaseInsensitive))
      {
          //Log::info(tmpString);
          mimeType = mimeDatabase.mimeTypeForFile(tmpString);
          name = mimeType.name();
          if(name == "video/x-msvideo" ||
             name == "video/x-matroska" )
          {
            if(tmpString.contains("TVShow"))
            {
              //strList_TVShowFiles->append(tmpString);
              Log::info("TVShow: " + tmpString);
              insertTVShow(tmpString);
            }
            if(tmpString.contains("Movie"))
            {
              //strList_MovieFiles->append(tmpString);
              Log::info("Movie: " + tmpString);
              insertMovie(tmpString);
            }
          }

          if(name == "audio/mpeg" && tmpString.contains("Music"))
          {
            //strList_MP3Files->append(tmpString);
            //Log::info("MP3: " + tmpString);
            insertMP3Files(tmpString);
          }
      }
      else
      {
        strList_DBFiles.removeAll(tmpString);
      }
      i++;
    }
    sig_ProgressBar_Hide();
}

void InsertMovies::insertMovie(QString movieFile)
{
//  foreach(QString movieFile, *strList_MovieFiles)
//  {
    sig_NewInfo(movieFile);
    movie.serie = "0";
    movie.fsk = "0";
    movie.file_Path = movieFile;
    movie.list_Person.clear();
    movie.strList_Genres.clear();
    if(movieFile.contains("Archive"))
    {
      movie.archive = "1";
    }
    else 
    {
      movie.archive = "0";
    }

    fileName = movieFile.left(movieFile.length() - 4);
    fileName = fileName.split("/").last();

    Log::info("InsertMovies: Suche nach " + fileName);

    tmdbUrl = "https://api.themoviedb.org/3/search/movie?query=" + fileName;
    tmdbUrl = tmdbUrl + "&" + tmdbKey + tmdbLanguage;
    tmdbQuery(tmdbUrl, &errorString, &result);
    if(errorString != "NoError")
    {
      Log::error("Insert Movies: " + errorString);
      sig_NewInfo(" ");
      return;
    }

    eval_MovieQuery();
    sig_NewInfo(" ");
//  }
}

void InsertMovies::insertTVShow(QString tvShowFile)
{
  sig_NewInfo(tvShowFile);
  QList<Movie> list_TVShow;
  list_TVShow = database->getAllTVShow();
  QString tvName;

//  foreach(QString tvShowFile, *strList_TVShowFiles)
//  { 
    bool isInDatabase = false;
    movie.serie = "1";
    movie.fsk = "0";
    movie.file_Path = tvShowFile;
    movie.list_Person.clear();
    movie.strList_Genres.clear();

    if(tvShowFile.contains("Archive"))
    {
      movie.archive = "1";
    }
    else 
    {
      movie.archive = "0";
    }
    fileName = tvShowFile.left(tvShowFile.length() - 4);
    QStringList split = fileName.split("/");
    tvName = split.at(split.size() -2);

     Log::info(QString("Size: %1").arg(list_TVShow.size()));
    foreach(Movie _movie, list_TVShow)
    {
      Log::info("_movie: " + _movie.title);
      if(_movie.title == tvName)
      {
        movie.ramoc_ID = _movie.ramoc_ID;
        database->insertEpisode(movie);
        isInDatabase = true;
        break;
      }
    }

    if(isInDatabase)
    {
      //continue;
      sig_NewInfo(" ");
      return;
    }

    tmdbUrl = "https://api.themoviedb.org/3/search/tv?query=" + tvName;
    tmdbUrl = tmdbUrl + "&" + tmdbKey + tmdbLanguage;
    tmdbQuery(tmdbUrl, &errorString, &result);
    if(errorString != "NoError")
    {
      Log::error("Insert Movies: " + errorString);
      sig_NewInfo(" ");
      return;
    }
    //muss sein wegen loadDetails();
    fileName = tvName;
    eval_TVQuery();
    sig_NewInfo(" ");
   // list_TVShow = database->getAllTVShow();
  //}
}

void InsertMovies::insertMP3Files(QString file)
{
//  Log::error(Q_FUNC_INFO);
  sig_NewInfo(file);
  QString comment;
  int erfasst = QDateTime(QDate::currentDate()).toTime_t();

  //while(strList_MP3Files->count() > 0)
  //{
  //  QString file = strList_MP3Files->first();
    Log::error(file);

    TagLib::FileRef f(file.toUtf8());
    if(!f.isNull())
    {
      MetaPaket mp;
      if(file.contains("Sampler"))
      {
        mp.sampler = "1";
      }
      else
      {
        mp.sampler = "0";
      }
      mp.title = TStringToQString(f.tag()->title()).toUtf8();
      mp.artist = TStringToQString(f.tag()->artist()).toUtf8();
      mp.album = TStringToQString(f.tag()->album()).toUtf8();
      mp.genre = TStringToQString(f.tag()->genre()).toUtf8();
      mp.year = QString("%1").arg(f.tag()->year());
      mp.tracknr = f.tag()->track();
      mp.playcounter = 0;
      mp.erfasst = erfasst;
      mp.wertung = 0;
      mp.gespielt = 0;
      comment = TStringToQString(f.tag()->comment()).toUtf8();
      if(comment.startsWith(QString("QMDB")))
      {
        mp.wertung = comment.section('#', 1,1).toInt();
        mp.gespielt = comment.section('#', 2,2).toUInt();
        //alte 5 auf 1 setzen
        if(mp.wertung == 5)
          mp.wertung = 1;
      }
      mp.pfad = file.toUtf8();
      mp.coverPfad = QString("noCover");
      database->insertMetaPaket(mp);
    }
    else
    {
      Log::error("Kein ID3Tag gefunden");
    }
  //}
 sig_NewInfo(" ");
}

void InsertMovies::eval_MovieQuery()
{
  Log::error(Q_FUNC_INFO);
    foreach(QVariant qVariant_Film, result["results"].toList())
    {
      QVariantMap map = qVariant_Film.toMap();
      //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << map["title"].toString();
      if(map["title"].toString() == fileName)
      {
        movie.title = map["title"].toString();
        movie.tmdb_ID = map["id"].toString();
        
        fskQuery(movie.tmdb_ID, &movie.fsk);
        Log::info("FSK: " + movie.fsk + " tmdb: " + movie.tmdb_ID);

        if(load_Details())
        {
          database->insertMovie(movie);
        }
        break;
      }//if(map["title"].toString() == fileName)
    }//foreach(QVariant qVariant_Film, result[results].toList())
}

void InsertMovies::eval_TVQuery()
{
  Log::info(Q_FUNC_INFO);
    foreach(QVariant qVariant_Film, result["results"].toList())
    {
      QVariantMap map = qVariant_Film.toMap();
      Log::info( map["original_name"].toString());

      if(map["original_name"].toString() == fileName)
      {
        movie.title = map["original_name"].toString();
        movie.tmdb_ID = map["id"].toString();
//
        if(load_Details())
          database->insertMovie(movie);
        break;
      }//if(map["title"].toString() == fileName)
    }//foreach(QVariant qVariant_Film, result[results].toList())
}

bool InsertMovies::load_Details()
{
  //Details nachladen
  tmdbUrl = "https://api.themoviedb.org/3/movie/" + movie.tmdb_ID;
  if(movie.serie == "1")
    tmdbUrl = "https://api.themoviedb.org/3/tv/" + movie.tmdb_ID;

  tmdbUrl = tmdbUrl + "?" + tmdbKey + tmdbLanguage;
  tmdbQuery(tmdbUrl, &errorString, &result);
  if(errorString == "Network Error" || errorString == "Parser Error")
  {
      Log::error("Insert Movies: " + errorString);
      Log::error("Insert Movies: " + tmdbUrl);
    return false;
  }

  movie.poster_Path = result["poster_path"].toString();
  movie.backdrop_Path = result["backdrop_path"].toString();
  movie.overview = result["overview"].toString();
  movie.runtime = result["runtime"].toString();
  movie.vote_Average = result["vote_average"].toString();
  movie.vote_Count = result["vote_count"].toString();
  movie.year = result["release_date"].toString();
  movie.year = movie.year.split("-").first();
  if(movie.serie == "1") movie.year = "0";
  if(movie.serie == "1") movie.runtime = "0";
  foreach(QVariant qVariant_Genre, result["genres"].toList())
  {
    QVariantMap map = qVariant_Genre.toMap();
    movie.strList_Genres << map["name"].toString();
  }
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Poster_Path  : " << movie.poster_Path;
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Backdrop_Path: " << movie.backdrop_Path;
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Runtime      : " << movie.runtime;
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "vote_average : " << movie.vote_Average;
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "vote_count   : " << movie.vote_Count;
  
  //Youtube Url
  tmdbUrl = "https://api.themoviedb.org/3/movie/" + movie.tmdb_ID 
            + "/videos?" + tmdbKey
            + tmdbLanguage;
  if(movie.serie == "1")
  {
    tmdbUrl = "https://api.themoviedb.org/3/tv/" + movie.tmdb_ID 
              + "/videos?" + tmdbKey
              + tmdbLanguage;
  }

  tmdbQuery(tmdbUrl, &errorString, &result);
  if(errorString == "NoError")
  {
     foreach(QVariant qVariant_map, result["results"].toList())
     {
       QVariantMap qVariant_Trailer = qVariant_map.toMap();
       if(qVariant_Trailer["site"].toString() == QString("YouTube"))
       {
         movie.trailer = qVariant_Trailer["key"].toString();
         sig_NewTrailer(movie.trailer);
         break;
       }
     }
  }
  
  //Poster & Backdrop laden
  sig_NewInfo("Lade Poster: " + movie.title);
  tmdbUrl = "http://image.tmdb.org/t/p/w342" + movie.poster_Path;
  tmdbQuery(tmdbUrl, &errorString, &result);
  if(errorString == "Network Error")
  {
    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << tmdbUrl;
    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << errorString << "\n";
    return false;
  }
  image.loadFromData(tmdbReply->readAll());
  movie.poster_Hash = QString("%1").arg(QString(QCryptographicHash::hash(movie.title.toUtf8(),QCryptographicHash::Md5).toHex())); 
  image.save(picturePath + "Poster/" + movie.poster_Hash, "PNG" );
 // QByteArray byteArray_Poster;
 // QBuffer buffer_Poster(&byteArray_Poster);
 // image.save(&buffer_Poster, "PNG");
 // movie.base64_Poster = byteArray_Poster.toBase64();

  sig_NewInfo("Lade Backdrop: " + movie.title);
  //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Lade Backdrop";
  tmdbUrl = "http://image.tmdb.org/t/p/w1280" + movie.backdrop_Path;
  tmdbQuery(tmdbUrl, &errorString, &result);
  if(errorString == "Network Error")
  {
      Log::error("Insert Movies: " + errorString);
      Log::error("Insert Movies: " + tmdbUrl);
    return false;
  }

  image.loadFromData(tmdbReply->readAll());
  movie.backdrop_Hash = QString("%1").arg(QString(QCryptographicHash::hash(movie.title.toUtf8(),QCryptographicHash::Md5).toHex())); 
  image.save(picturePath + "Backdrop/" + movie.backdrop_Hash, "PNG" );
 // QByteArray byteArray_Backdrop;
 // QBuffer buffer_Backdrop(&byteArray_Backdrop);
 // image.save(&buffer_Backdrop, "PNG");
 // movie.base64_Backdrop = byteArray_Backdrop.toBase64();

  //Credits
  tmdbUrl = "https://api.themoviedb.org/3/movie/" 
            + movie.tmdb_ID
            + "/credits?"
            + tmdbKey
            + tmdbLanguage;
  
  if(movie.serie == "1")
  {
    tmdbUrl = "https://api.themoviedb.org/3/tv/" 
            + movie.tmdb_ID
            + "/credits?"
            + tmdbKey
            + tmdbLanguage;
  }

  tmdbQuery(tmdbUrl, &errorString, &result);
  if(errorString == "Network Error" || errorString == "Parser Error")
  {
      Log::error("Insert Movies: " + errorString);
      Log::error("Insert Movies: " + tmdbUrl);
    return false;
  }
  
  foreach(QVariant cast, result["cast"].toList())
  {
    QVariantMap map = cast.toMap();
    Person person;
    person.name = map["name"].toString();
    person.character = map["character"].toString();
    person.profile_Path = map["profile_path"].toString();
    person.tmdb_ID = map["id"].toString();
    
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "TMDB_ID     : " << person.tmdb_ID;
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Name        : " << person.name;
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Character   : " << person.character;
    //qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss") << "Profile_Path: " << person.profile_Path;
//
   if(!person.profile_Path.isEmpty())
   {
      tmdbUrl = "http://image.tmdb.org/t/p/w185" + person.profile_Path;
      sig_NewInfo("Lade Profile: " + person.name);
      tmdbQuery(tmdbUrl, &errorString, 0);
      image.loadFromData(tmdbReply->readAll());
      person.profile_Hash = QString("%1").arg(QString(QCryptographicHash::hash(person.name.toUtf8(),QCryptographicHash::Md5).toHex())); 
      image.save(picturePath + "Actor/" + person.profile_Hash, "PNG" );
    //  QByteArray byteArray_Profile;
    //  QBuffer buffer_Profile(&byteArray_Profile);
    //  image.save(&buffer_Profile, "PNG");

    //  person.base64_Profile = byteArray_Profile.toBase64();
   }
    movie.list_Person << person;
  }

  return true;
}

void InsertMovies::tmdbQuery(QString url, QString* str, QVariantMap* res)
{
  //Log::error(Q_FUNC_INFO);
  QVariantMap map;
  *str = "NoError";

  tmdbReply = networkAccessManager->get(QNetworkRequest(QUrl(url)));
  connect(tmdbReply, SIGNAL(finished()), eventLoop, SLOT(quit()));
  eventLoop->exec();

  if(tmdbReply->error() != QNetworkReply::NoError)
  {
    *str = "Network Error " + url;
    return;
  }

  if(url.contains("image.tmdb.org"))
      return;

  QString string = tmdbReply->readAll();
  QJsonParseError* jError = new QJsonParseError();
  QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), jError);
  if(jError->error != 0)
  {
    *str = "Parser Error";
    return;
  }
  QJsonObject jObject = jsonDocument.object();
  *res = jObject.toVariantMap();

  map = *res;

  if(map["results"].toList().isEmpty())
  {
    *str = "Nichts gefunden";
    return;
  }
}

void InsertMovies::fskQuery(QString tmdb, QString* str)
{
  QUrl url("https://altersfreigaben.de/api2/s/" + tmdb + "/de");
  fskReply = networkAccessManager->get(QNetworkRequest(url));

  connect(fskReply, SIGNAL(finished()), eventLoop, SLOT(quit()));
  eventLoop->exec();

  if(fskReply->error() != QNetworkReply::NoError)
  {
    *str = "-1";
    return;
  }
  
  *str = fskReply->readAll();
  return;
}



//void InsertMovies::check_NewMovie()
//{
//    QStringList stringList_databaseFiles = database->getFileList();
//    QString tmpString;
//
//    //Lese alle Dateien aus /Bigpod/Filme und ueberpruefe sie
//    //mit der Datenbank
//    check_HDD("/media/ramoc/Filme", strList_Files);
//
//    foreach(tmpString, *strList_Files)
//    {
//      if(!stringList_databaseFiles.contains(tmpString, Qt::CaseInsensitive))
//          strList_MovieFiles->append(tmpString);
//    }
//}
//void InsertMovies::check_NewTVShow()
//{
//    QStringList stringList_databaseFiles = database->getFileList();
//    QString tmpString;
//    strList_Files->clear();
//    strList_MovieFiles->clear();
//
//    //Lese alle Dateien aus /Bigpod/Serien und ueberpruefe sie
//    //mit der Datenbank
//    check_HDD("/media/ramoc/Serien", strList_Files);
//
//    foreach(tmpString, *strList_Files)
//    {
//      if(!stringList_databaseFiles.contains(tmpString, Qt::CaseInsensitive))
//          strList_MovieFiles->append(tmpString);
//    }
//}
//
//void InsertMovies::check_NewMP3()
//{
//    
//    QStringList stringList_databaseFiles = database->getUrl();
//    strList_Files->clear();
//    strList_MP3Files->clear();
//    QDir dir;
//    dir.setPath("/media/Mike/Musik");
//    findTracks(dir,strList_Files);
//
//    foreach(QString tmpString, *strList_Files)
//    {
//      if(!stringList_databaseFiles.contains(tmpString, Qt::CaseInsensitive))
//      {
//          strList_MP3Files->append(tmpString);
//          Log::error("New MP3: " + tmpString);
//      }
//    }
//}
//
//void InsertMovies::findTracks(QDir dir, QStringList* list)
//{
//  //Sucht rekursiv im Verzeichnis dir nach mp3 Files die dann
//  //in list abgelegt werden
//
//  dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
//
//  QFileInfoList infoList = dir.entryInfoList();
//  foreach(QFileInfo info, infoList)
//  {
//    if(info.isFile())
//    {
//      if(info.suffix() == "mp3")
//      *list << info.absoluteFilePath();
//    }
//    if(info.isDir())
//    {
//      dir.cd(info.absoluteFilePath());
//      findTracks(dir, list);
//    }
//  }
//}
