#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Log::info("Starte RamocServer");
    ui->setupUi(this);
    setStyleSheet("QMainWindow {background: 'black';}");

    label_ChannelIcon = new QLabel(this);

    insertMovies = new InsertMovies(this);
    //vlcProcess   = new VLCProcess(this);
    server       = new Server(this);
    database     = new DataBase(this);
    lastFm       = new M_LastFm(this);
    progressBar = new QProgressBar(this);
    player      = new Player(this);

    connect(database, SIGNAL(sig_PlayedSet()), server, SIGNAL(sig_PlayedSet()));
    connect(database, SIGNAL(sig_SendUnsortedFiles(QString)), 
            server,   SIGNAL(sig_SendUnsortedFiles(QString)));
    connect(database, SIGNAL(sig_SendArtistAlben(QStringList)), 
            server,   SIGNAL(sig_SendArtistAlben(QStringList)));

    connect(database, SIGNAL(sig_SendTracks(QList<Track>)),
            player  , SLOT(onReceiveTracks(QList<Track>)));
    connect(database, SIGNAL(sig_UpdateID3Tag_Title(QString, QString)),
            player,   SLOT(onUpdateID3Tag_Title(QString, QString)));
    connect(database, SIGNAL(sig_UpdateID3Tag_Album(QString, QString)),
            player,   SLOT(onUpdateID3Tag_Album(QString, QString)));
    connect(database, SIGNAL(sig_UpdateID3Tag_Artist(QString, QString)),
            player  , SLOT(onUpdateID3Tag_Artist(QString, QString)));

    connect(insertMovies, SIGNAL(sig_NewInfo(QString)),    
            this,         SLOT(onNewInfo(QString)));
    connect(insertMovies, SIGNAL(sig_ProgressBar_Show()),
            progressBar, SLOT(show()));
    connect(insertMovies, SIGNAL(sig_ProgressBar_Hide()),
            progressBar, SLOT(hide()));
    connect(insertMovies, SIGNAL(sig_ProgressBar_SetRange(int, int)),
            progressBar, SLOT(setRange(int, int)));
    connect(insertMovies, SIGNAL(sig_ProgressBar_SetValue(int)),
            progressBar, SLOT(setValue(int)));

    connect(server, SIGNAL(sig_InsertMovie(QString, QString)), 
            this,   SLOT(onInsertMovie(QString, QString)));
    connect(server, SIGNAL(sig_InsertMovies()),      
            this,   SLOT(onInsertMovies()));

    connect(server,       SIGNAL(sig_ArchiveMovie(QString)),
            database,     SLOT(onArchive(QString)));
    connect(server,       SIGNAL(sig_DeleteMovie(QString)),
            database,     SLOT(onDelete(QString)));
    connect(server,       SIGNAL(sig_GetArtistAlben(QString)),
            database,     SLOT(onArtistAlben(QString)));
    connect(server,       SIGNAL(sig_GetFavorite()),
            database,     SLOT(onGetFavorite()));
    connect(server,       SIGNAL(sig_GetRandom()),
            database,     SLOT(onGetRandom()));
    connect(server,       SIGNAL(sig_GetUnsortedFiles()),
            database,     SLOT(onGetUnsortedFiles()));
    connect(server,       SIGNAL(sig_GetTracks(QString, QString)),
            database,     SLOT(onGetTracks(QString, QString)));
    connect(server,       SIGNAL(sig_RestoreMovie(QString)),
            database,     SLOT(onRestore(QString)));
    connect(server,       SIGNAL(sig_SetFavorite(QString)),
            database,     SLOT(onSetFavorite(QString)));
    connect(server,       SIGNAL(sig_SetID3Tag(QString)),
            database,     SLOT(onSetID3Tag(QString)));

    connect(server,       SIGNAL(sig_DeletePlaylist()),
            player, SLOT(onDeletePlaylist()));
    connect(server,       SIGNAL(sig_Backward()),
            player, SLOT(onBackward()));
    connect(server,       SIGNAL(sig_GetAudio()),
            player, SLOT(onGetAudio()));
    connect(server,       SIGNAL(sig_GetPlaylist()),
            player, SLOT(onGetPlaylist()));
    connect(server,       SIGNAL(sig_GetSubtitle()),
            player, SLOT(onGetSubtitle()));
    connect(server,       SIGNAL(sig_IncSpeed()),
            player, SLOT(onIncSpeed()));
    connect(server,       SIGNAL(sig_MinutesBackward()),
            player, SLOT(onMinutesBackward()));
    connect(server,       SIGNAL(sig_MinutesForward()),
            player, SLOT(onMinutesForward()));
    connect(server,       SIGNAL(sig_Mute()),
            player, SLOT(onMute()));
    connect(server,       SIGNAL(sig_Play(QString)),
            player, SLOT(onPlay(QString)));
    connect(server,       SIGNAL(sig_PlayStream(QString)),
            player, SLOT(onPlayStream(QString)));
    connect(server,       SIGNAL(sig_PlayTrack(int)),
            player, SLOT(onPlayTrack(int)));
    connect(server,       SIGNAL(sig_PlayYoutube(QString)),
            player, SLOT(onPlayYoutube(QString)));
    connect(server,       SIGNAL(sig_Stop()),
            player, SLOT(onStop()));
    connect(server,       SIGNAL(sig_SetAudio(QString)),
            player, SLOT(onSetAudio(QString)));
    connect(server,       SIGNAL(sig_SetSubtitle(QString)),
            player, SLOT(onSetSubtitle(QString)));
    connect(server,       SIGNAL(sig_SetVolume(QString)),
            player, SLOT(onSetVolume(QString)));
    connect(server,       SIGNAL(sig_SetTime(QString)),
            player, SLOT(onSeek(QString)));
    connect(server,       SIGNAL(sig_ToggleSubtitle()),
            player, SLOT(onToggleSubtitle()));

    connect(player, SIGNAL(sig_SendPlaylist(QString)),
            server,       SIGNAL(sig_SendPlaylist(QString)));
    connect(player, SIGNAL(sig_NewState(quint8)),   
            server,       SIGNAL(sig_NewState(quint8)));
    connect(player, SIGNAL(sig_SetPlayed(QString)), 
            database,     SLOT(onSetPlayed(QString)));
    connect(player, SIGNAL(sig_SetPlayed(Track)), 
            database,     SLOT(onSetPlayed(Track)));
    connect(player, SIGNAL(sig_WriteData(QString, bool)),
            server,       SIGNAL(sig_WriteData(QString, bool)));

    connect(player, SIGNAL(sig_PlayingTrack(Track)),
            this,         SLOT(onPlayingTrack(Track)));
    connect(player, SIGNAL(sig_VLCStopped()),
            this,         SLOT(onVLCStopped()));

    connect(player, SIGNAL(sig_SetBlack()),
            this,         SLOT(onSetBlack()));
    connect(lastFm, SIGNAL(new_Artist_Pixmap(QPixmap)), this,
                    SLOT(onNewArtistPixmap(QPixmap)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onVLCStopped()
{
  ui->label->setPixmap(pixmap_Main);
  ui->widget_Music->hide();
}

void MainWindow::onNewArtistPixmap(QPixmap pixmap)
{
    QPixmap pix(310,310);
    pix.fill(QColor(255,0,0,0));
    QPainter p(&pix);
    QPainterPath path;
    path.addEllipse(5,5,300,300);
    p.setClipPath(path);
    p.drawPixmap(5,5,pixmap);
    //pix = pix.scaled(300,300);
    ui->label_ArtistPic->setPixmap(pix);
}

void MainWindow::onNewInfo(QString str)
{
  ui->labelDebug->show();
  ui->labelDebug->setText(str);
}

void MainWindow::onInsertMovie(QString file_path, QString title)
{
  Log::info(Q_FUNC_INFO);
  Log::info(file_path);
  Log::info(title);

  QFileInfo info(file_path);
  QFile file(file_path);
  QDir dir = info.dir();
  QString tmp = dir.absolutePath() + "/" + title + "." + info.suffix();
  file.rename(tmp);
  if(!insertMovies->isRunning())
    insertMovies->start();
}

void MainWindow::onInsertMovies()
{
  if(!insertMovies->isRunning())
    insertMovies->start();
}

void MainWindow::onPlayingTrack(Track track)
{
  Log::info(Q_FUNC_INFO);
  ui->label->setPixmap(pixmap_Music);
  ui->label_Title->setText(track.title);
  ui->label_Artist->setText(track.artist);
  ui->widget_Music->show();

  lastFm->start_Search_Artist_Image(track.artist);
}

void MainWindow::setDesktop(QDesktopWidget *d)
{
    desktop = d;
    QRect rec = desktop->availableGeometry(this);
    setGeometry(0,0,desktop->width(), desktop->height());
    pixmap_Main = QPixmap(":/Bilder/Wallpaper");
    pixmap_Main = pixmap_Main.scaled(rec.width(),rec.height());
    pixmap_Black = QPixmap(":/Bilder/Black");
    pixmap_Black = pixmap_Black.scaled(rec.width(),rec.height());
    ui->label->setPixmap(pixmap_Main);
    ui->label->setGeometry(0,0,rec.width(), rec.height());
    ui->labelDebug->setGeometry(rec.width()/2 - 150,
                                rec.height()*0.66,
                                300,30);
    ui->labelDebug->setText("DEBUG");

    ui->widget_Music->setGeometry(0,0,rec.width(),rec.height());
    pixmap_Music = QPixmap(":/Bilder/wallpaper_Music");
    pixmap_Music = pixmap_Music.scaled(rec.width(),rec.height());

    ui->label_Title->setGeometry(0,
                                 (int)(rec.height() - (rec.height() * 0.09)),
                                 rec.width(),
                                 (int)(rec.height() * 0.09));
    ui->label_Artist->setGeometry(0,
                                 (int)(rec.height() - (rec.height() * 0.09) * 2 - 10 ),
                                 rec.width() - 310,
                                 (int)(rec.height() * 0.09));

    ui->label_ArtistPic->setGeometry(rec.width() - 310,
                                 (int)(rec.height() - (rec.height() * 0.09) - 310 ),
                                 300,
                                 300);


    ui->widget_Music->hide();
   
    //IP suchen und anzeigen
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    QString ipAddress;

    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && 
            ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    //Wenn nichts gefunden wurde dann nimm localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    ui->labelDebug->setText(ipAddress);

    QCursor c = cursor();
    c.setPos(rec.width(), rec.height());
    setCursor(c);
    
    progressBar->setGeometry(0,rec.height()-15, rec.width(), 15);
    
    QTimer::singleShot(30000, ui->labelDebug, SLOT(hide()));
}

void MainWindow::onSetBlack()
{
  ui->label->setPixmap(pixmap_Black);
  ui->widget_Music->hide();
}
