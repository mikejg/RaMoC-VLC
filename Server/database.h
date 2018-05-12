#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QIcon>
#include <QList>
#include <QPixmap>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QDateTime>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QMap>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <id3v2tag.h>
#include <attachedpictureframe.h>
#include <mpegfile.h>
#include <tag.h>
#include <fileref.h>
#include <log.h>
struct Person
{
  QString name;
  QString character;
  QString profile_Path;
  QString tmdb_ID;
  QString profile_Hash;
};

struct Movie
{
  QString ramoc_ID;
  QString title;
  QString file_Path;
  QString tmdb_ID;
  QString year;
  QString poster_Path;
  QString backdrop_Path;
  QString overview;
  QString vote_Average;
  QString vote_Count;
  //QByteArray base64_Poster;
  //QByteArray base64_Backdrop;
  QString poster_Hash;
  QString backdrop_Hash;
  QString trailer;
  QString runtime;
  QString serie;
  QString fsk;
  QString archive;

  QStringList strList_Genres;
  QList<Person> list_Person;
};

struct Track
{
  QString ramoc_ID;
  QString album_ID;
  QString artist_ID;
  QString title;
  QString album;
  QString artist;
  QString path;
  QString playlistPos;
  QString favorite;
  QString sampler;
};

struct MetaPaket
{
  int id;
  QString title;
  QString artist;
  QString album;
  QString genre;
  QString year;
  uint tracknr;
  int playcounter;
  uint erfasst;
  uint gespielt;
  int wertung;
  QString pfad;
  QString coverPfad;
  QString coverData;
  QString sampler;
};

class DataBase : public QObject
{
      Q_OBJECT

  private:

    QString WARNING;
    QString INFO;
    QString ERROR;

    QSqlDatabase db;
    QString connectionName;
    QStringList strList_Path;

    QNetworkAccessManager* networkAccessManager;
    void check_HDD(QString string_DirPath, QStringList* stringList);
    void trimmFilePath(QString& file_path, QString c);

  public:
    DataBase(QObject *parent = 0, QString connectionName = QString("Main_Connection"));
    ~DataBase();
    QString       getAlbumCover(QString albumID);
    QList<Movie>  getAllTVShow();
    QStringList   getFileList();
    QString       getID(QString table, QString column, QString value);
    //QList<Track>  getRandom();
    QList<Movie>  getTVShow();
    //QString       getUnsortetFiles();
    void          insertEpisode(Movie episode);
    void          insertMovie(Movie movie);
    bool          open();
    //void          deleteMovie(QString movieID);
    QStringList   getFiles(QString movie_ID);
    //QStringList   getArtistAlben(QString str);
    Track         getTrack(QString ramocID);
    QList<Track>  getTrack_Album(QString album);
    QList<Track>  getTrack_Artist(QString artist);
    //QList<Track>  getTracks_Artist_Album(QString artist, QString album);
    QStringList   getUrl();
    void          insertMetaPaket(MetaPaket mp);
    int           key(QString , QString );
    QStringList   getSampler();
    void          setSampler (QString ramoc_ID);
    void          setPlayed(Track track);
    void          updateTitle(Track track, QString title);
    void          updateAlbum(Track track, QString album);
    void          updateArtist(Track track, QString artist);

    TagLib::String Qt4StringToString(QString s) 
    {return TagLib::String(s.toLatin1().data(),TagLib::String::Latin1);}

  signals:
    void sig_NewInfo(QString);
    void sig_PlayedSet();
    void sig_SendArtistAlben(QStringList);
    void sig_SendTracks(QList<Track>);
    void sig_SendUnsortedFiles(QString);
    void sig_UpdateID3Tag_Title(QString, QString);
    void sig_UpdateID3Tag_Album(QString, QString);
    void sig_UpdateID3Tag_Artist(QString, QString);

  public slots:
    void onArchive(QString);
    void onArtistAlben(QString);
    void onDelete(QString);
    void onGetFavorite();
    void onGetRandom();
    void onGetTracks(QString, QString);
    void onGetUnsortedFiles();
    void onRestore(QString);
    void onSetFavorite (QString ramoc_ID);
    void onSetID3Tag(QString str);
    void onSetPlayed(QString string_File);
    void onSetPlayed(Track track);
};

#endif // DATABASE_H
