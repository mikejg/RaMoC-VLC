#ifndef INSERTMOVIES_H
#define INSERTMOVIES_H

#include <QThread>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <QEventLoop>
#include <QDir>
#include <QImage>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMimeDatabase>
#include <QMimeType>
#include "database.h"
#include <id3v2tag.h>
#include <log.h>

class InsertMovies : public QThread
{
  Q_OBJECT

  private:
    QStringList*            strList_MovieFiles;
    QStringList*            strList_TVShowFiles;
    QStringList*            strList_MP3Files;
    QStringList*            strList_Files;
    QStringList             strList_Path;
    QStringList             strList_DBFiles;
    QNetworkReply*          fskReply;
    QNetworkReply*          tmdbReply;
    QNetworkAccessManager*  networkAccessManager;
    QEventLoop*             eventLoop;
    QMimeDatabase           mimeDatabase;
    QMimeType               mimeType;

    QVariantMap   result;
    QString       errorString;
    QString       tmdbUrl;
    QImage        image ;
    QString       fileName;
    QString       tmdbKey = "api_key=9ce3b6ead4014e1e2c976df65a530a11";
    QString       tmdbLanguage = "&language=de";
    QString       picturePath="/var/www/html/Pictures/";
    Movie movie;
    DataBase* database;

    void tmdbQuery(QString url, QString* str, QVariantMap* res);
    void fskQuery(QString tmdb, QString* str);
    void check_HDD(QString string_DirPath, QStringList* stringList);
//    void check_NewMovie();
//    void check_NewTVShow();
//    void check_NewMP3();
    void check_NewFiles();
//    void findTracks(QDir dir, QStringList* list);

  public:
    InsertMovies(QObject *parent = 0);
    void insertMovie(QString);
    void insertTVShow(QString);
    void insertMP3Files(QString);
    void eval_MovieQuery();
    void eval_TVQuery();
    bool load_Details();
  protected:
    virtual void run();

   signals:
    void sig_NewInfo(QString);
    void sig_NewTrailer(QString);
    void sig_ProgressBar_Show();
    void sig_ProgressBar_Hide();
    void sig_ProgressBar_SetRange(int, int);
    void sig_ProgressBar_SetValue(int);
};
#endif
