/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *labelDebug;
    QWidget *widget_Music;
    QLabel *label_Title;
    QLabel *label_Artist;
    QLabel *label_ArtistPic;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1055, 625);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 551, 281));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Bilder/banner4.png")));
        labelDebug = new QLabel(centralWidget);
        labelDebug->setObjectName(QStringLiteral("labelDebug"));
        labelDebug->setGeometry(QRect(155, 350, 500, 21));
        labelDebug->setAlignment(Qt::AlignCenter);
        widget_Music = new QWidget(centralWidget);
        widget_Music->setObjectName(QStringLiteral("widget_Music"));
        widget_Music->setGeometry(QRect(50, 30, 960, 540));
        label_Title = new QLabel(widget_Music);
        label_Title->setObjectName(QStringLiteral("label_Title"));
        label_Title->setGeometry(QRect(10, 480, 940, 50));
        label_Title->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(33);
        font.setBold(false);
        font.setWeight(50);
        label_Title->setFont(font);
        label_Title->setAlignment(Qt::AlignCenter);
        label_Artist = new QLabel(widget_Music);
        label_Artist->setObjectName(QStringLiteral("label_Artist"));
        label_Artist->setGeometry(QRect(0, 0, 940, 50));
        label_Artist->setMinimumSize(QSize(0, 50));
        QFont font1;
        font1.setPointSize(22);
        font1.setBold(false);
        font1.setWeight(50);
        label_Artist->setFont(font1);
        label_Artist->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_ArtistPic = new QLabel(widget_Music);
        label_ArtistPic->setObjectName(QStringLiteral("label_ArtistPic"));
        label_ArtistPic->setGeometry(QRect(650, 230, 300, 300));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QString());
        labelDebug->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_Title->setText(QApplication::translate("MainWindow", "Titel", Q_NULLPTR));
        label_Artist->setText(QApplication::translate("MainWindow", "Titel", Q_NULLPTR));
        label_ArtistPic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
