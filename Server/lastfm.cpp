#include "lastfm.h"

M_LastFm::M_LastFm(QObject *parent) :
    QObject(parent),
    string_API_Key("8311f747b2eb886f15f6710d83c0438d")
{
    networkAccessManager = new QNetworkAccessManager(this);
    isRunning = false;
}

void M_LastFm::slot_parse_Album_Image_Url()
{
    qDebug() << Q_FUNC_INFO;
    QXmlStreamReader xmlReader(networkReplay);
    QString string_Size;
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named person, we'll dig the information from there.*/
            if(xmlReader.name() == "image")
            {
                 QXmlStreamAttributes attributes = xmlReader.attributes();
                 if(attributes.hasAttribute("size"))
                 {
                    string_Size = attributes.value("size").toString();
                    if(string_Size == "mega")
                    {
                        xmlReader.readNext();
                       // if(xmlReader.text().contains(string_Album, Qt::CaseInsensitive))
                        //{
                            qDebug() << xmlReader.text().toString();
                            networkReplay_Bild = networkAccessManager->get(QNetworkRequest(QUrl(xmlReader.text().toString())));
                            connect(networkReplay_Bild, SIGNAL(finished()), this, SLOT(slot_load_Album_Image()));
                            break;
                        //}
                    }
                 }
            }
        }
    }
    qDebug() << Q_FUNC_INFO;
    networkReplay->deleteLater();
}

void M_LastFm::slot_parse_Artist_Image_Url()
{
    qDebug() << Q_FUNC_INFO;
    QXmlStreamReader xmlReader(networkReplay);
    QString string_Size;
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement)
        {
            /* If it's named person, we'll dig the information from there.*/
            if(xmlReader.name() == "image")
            {
                 QXmlStreamAttributes attributes = xmlReader.attributes();
                 if(attributes.hasAttribute("size"))
                 {
                    string_Size = attributes.value("size").toString();
                    if(string_Size == "mega")
                    {
                    xmlReader.readNext();
                       // if(xmlReader.text().contains(string_Artist, Qt::CaseInsensitive))
                        //{
                            //qDebug() << xmlReader.text().toString();
                            networkReplay_Bild = networkAccessManager->get(QNetworkRequest(QUrl(xmlReader.text().toString())));
                            connect(networkReplay_Bild, SIGNAL(finished()), this, SLOT(slot_load_Artist_Image()));
                            break;
                        //}
                    }
                 }
            }
        }
    }
    networkReplay->deleteLater();
    isRunning = false;
}

void M_LastFm::slot_load_Album_Image()
{
    qDebug() << Q_FUNC_INFO;
    QPixmap pix;
    pix.loadFromData(networkReplay_Bild->readAll());
    new_Album_Pixmap(pix);
}

void M_LastFm::slot_load_Artist_Image()
{
    QPixmap pix;
    pix.loadFromData(networkReplay_Bild->readAll());
    new_Artist_Pixmap(pix);
}

void M_LastFm::start_Search_Album_Image(QString artist, QString album)
{
    string_Artist = artist.replace(" ", "+");
    string_Album = album.replace(" ", "+");

    networkReplay = networkAccessManager->get(QNetworkRequest(QUrl(QString("http://ws.audioscrobbler.com/2.0/?method=album.getinfo&artist="
                                                           + string_Artist
                                                           + "&album="
                                                           + string_Album
                                                           +"&api_key="
                                                           + string_API_Key))));

    connect(networkReplay, SIGNAL(finished()), this, SLOT(slot_parse_Album_Image_Url()));
    connect(networkReplay, SIGNAL(error(QNetworkReply::NetworkError)),
             this, SLOT(slotError(QNetworkReply::NetworkError)));

}

void M_LastFm::start_Search_Artist_Image(QString artist)
{
  if(!isRunning)
  {
    isRunning = true;
    string_Artist = artist.replace(" ", "+");

    networkReplay = networkAccessManager->get(QNetworkRequest(QUrl(QString("http://ws.audioscrobbler.com/2.0/?method=artist.getinfo&artist="
                                                           + string_Artist
                                                           +"&api_key="
                                                           + string_API_Key))));

    connect(networkReplay, SIGNAL(finished()), this,
                           SLOT(slot_parse_Artist_Image_Url()));
    connect(networkReplay, SIGNAL(error(QNetworkReply::NetworkError)),this,
                           SLOT(slotError(QNetworkReply::NetworkError)));
  }
}

void M_LastFm::slotError(QNetworkReply::NetworkError)
{
    qDebug() << Q_FUNC_INFO;
}
