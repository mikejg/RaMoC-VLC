#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <QLabel>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QFile>
#include <QFileInfo>
#include <QCursor>
#include <QProgressBar>

#include "vlc_process.h"
#include "player.h"

#include "insertMovies.h"
#include "log.h"
#include "server.h"
#include "database.h"
#include "lastfm.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    InsertMovies*   insertMovies; 
    VLCProcess*     vlcProcess;
    QDesktopWidget* desktop;
    QLabel*         label_ChannelIcon;
    QPixmap         pixmap_Main;
    QPixmap         pixmap_Music;
    QPixmap         pixmap_Black;
    QProgressBar*   progressBar;
    Server*         server;
    DataBase*       database;
    M_LastFm*       lastFm;
    Player*         player;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setDesktop(QDesktopWidget *d);

public slots:
    void onInsertMovie(QString, QString);
    void onInsertMovies();
    void onVLCStopped();
    void onNewArtistPixmap(QPixmap);
    void onNewInfo(QString);
    void onPlayingTrack(Track);
    void onSetBlack();
};

#endif // MAINWINDOW_H
