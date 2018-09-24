#ifndef M_LASTFM_H
#define M_LASTFM_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QDebug>
#include <QPixmap>

class M_LastFm : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* networkAccessManager;
    QNetworkReply* networkReplay;
    QNetworkReply* networkReplay_Bild;

    QString string_API_Key;
    QString string_Artist;
    QString string_Album;
    bool isRunning;

public:
    explicit M_LastFm(QObject *parent = 0);
    void start_Search_Artist_Image(QString artist);
    void start_Search_Album_Image(QString artist, QString album);

signals:
    void new_Artist_Pixmap(QPixmap);
    void new_Album_Pixmap(QPixmap);

public slots:
    void slot_parse_Album_Image_Url();
    void slot_parse_Artist_Image_Url();
    void slot_load_Album_Image();
    void slot_load_Artist_Image();

    void slotError(QNetworkReply::NetworkError);
};

#endif // M_LASTFM_H
