/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Player_t {
    QByteArrayData data[30];
    char stringdata0[408];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Player_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Player_t qt_meta_stringdata_Player = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Player"
QT_MOC_LITERAL(1, 7, 12), // "sig_NewState"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "sig_SendPlaylist"
QT_MOC_LITERAL(4, 38, 13), // "sig_SetPlayed"
QT_MOC_LITERAL(5, 52, 5), // "Track"
QT_MOC_LITERAL(6, 58, 16), // "sig_MusicStopped"
QT_MOC_LITERAL(7, 75, 16), // "sig_PlayingTrack"
QT_MOC_LITERAL(8, 92, 13), // "sig_WriteData"
QT_MOC_LITERAL(9, 106, 16), // "onDeletePlaylist"
QT_MOC_LITERAL(10, 123, 10), // "onBackward"
QT_MOC_LITERAL(11, 134, 13), // "onGetPlaylist"
QT_MOC_LITERAL(12, 148, 13), // "onGetSubtitle"
QT_MOC_LITERAL(13, 162, 10), // "onIncSpeed"
QT_MOC_LITERAL(14, 173, 17), // "onMinutesBackward"
QT_MOC_LITERAL(15, 191, 16), // "onMinutesForward"
QT_MOC_LITERAL(16, 208, 6), // "onMute"
QT_MOC_LITERAL(17, 215, 6), // "onPlay"
QT_MOC_LITERAL(18, 222, 12), // "onPlayStream"
QT_MOC_LITERAL(19, 235, 11), // "onPlayTrack"
QT_MOC_LITERAL(20, 247, 13), // "onPlayYoutube"
QT_MOC_LITERAL(21, 261, 15), // "onReceiveTracks"
QT_MOC_LITERAL(22, 277, 12), // "QList<Track>"
QT_MOC_LITERAL(23, 290, 13), // "onSetSubtitle"
QT_MOC_LITERAL(24, 304, 6), // "onStop"
QT_MOC_LITERAL(25, 311, 16), // "onToggleSubtitle"
QT_MOC_LITERAL(26, 328, 15), // "onTrackFinished"
QT_MOC_LITERAL(27, 344, 20), // "onUpdateID3Tag_Title"
QT_MOC_LITERAL(28, 365, 20), // "onUpdateID3Tag_Album"
QT_MOC_LITERAL(29, 386, 21) // "onUpdateID3Tag_Artist"

    },
    "Player\0sig_NewState\0\0sig_SendPlaylist\0"
    "sig_SetPlayed\0Track\0sig_MusicStopped\0"
    "sig_PlayingTrack\0sig_WriteData\0"
    "onDeletePlaylist\0onBackward\0onGetPlaylist\0"
    "onGetSubtitle\0onIncSpeed\0onMinutesBackward\0"
    "onMinutesForward\0onMute\0onPlay\0"
    "onPlayStream\0onPlayTrack\0onPlayYoutube\0"
    "onReceiveTracks\0QList<Track>\0onSetSubtitle\0"
    "onStop\0onToggleSubtitle\0onTrackFinished\0"
    "onUpdateID3Tag_Title\0onUpdateID3Tag_Album\0"
    "onUpdateID3Tag_Artist"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Player[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  149,    2, 0x06 /* Public */,
       3,    1,  152,    2, 0x06 /* Public */,
       4,    1,  155,    2, 0x06 /* Public */,
       4,    1,  158,    2, 0x06 /* Public */,
       6,    0,  161,    2, 0x06 /* Public */,
       7,    1,  162,    2, 0x06 /* Public */,
       8,    2,  165,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  170,    2, 0x0a /* Public */,
      10,    0,  171,    2, 0x0a /* Public */,
      11,    0,  172,    2, 0x0a /* Public */,
      12,    0,  173,    2, 0x0a /* Public */,
      13,    0,  174,    2, 0x0a /* Public */,
      14,    0,  175,    2, 0x0a /* Public */,
      15,    0,  176,    2, 0x0a /* Public */,
      16,    0,  177,    2, 0x0a /* Public */,
      17,    1,  178,    2, 0x0a /* Public */,
      18,    1,  181,    2, 0x0a /* Public */,
      19,    1,  184,    2, 0x0a /* Public */,
      20,    1,  187,    2, 0x0a /* Public */,
      21,    1,  190,    2, 0x0a /* Public */,
      23,    1,  193,    2, 0x0a /* Public */,
      24,    0,  196,    2, 0x0a /* Public */,
      25,    0,  197,    2, 0x0a /* Public */,
      26,    0,  198,    2, 0x0a /* Public */,
      27,    2,  199,    2, 0x0a /* Public */,
      28,    2,  204,    2, 0x0a /* Public */,
      29,    2,  209,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

       0        // eod
};

void Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Player *_t = static_cast<Player *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->sig_SendPlaylist((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_SetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sig_SetPlayed((*reinterpret_cast< Track(*)>(_a[1]))); break;
        case 4: _t->sig_MusicStopped(); break;
        case 5: _t->sig_PlayingTrack((*reinterpret_cast< Track(*)>(_a[1]))); break;
        case 6: _t->sig_WriteData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->onDeletePlaylist(); break;
        case 8: _t->onBackward(); break;
        case 9: _t->onGetPlaylist(); break;
        case 10: _t->onGetSubtitle(); break;
        case 11: _t->onIncSpeed(); break;
        case 12: _t->onMinutesBackward(); break;
        case 13: _t->onMinutesForward(); break;
        case 14: _t->onMute(); break;
        case 15: _t->onPlay((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->onPlayStream((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onPlayTrack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->onPlayYoutube((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->onReceiveTracks((*reinterpret_cast< QList<Track>(*)>(_a[1]))); break;
        case 20: _t->onSetSubtitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->onStop(); break;
        case 22: _t->onToggleSubtitle(); break;
        case 23: _t->onTrackFinished(); break;
        case 24: _t->onUpdateID3Tag_Title((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 25: _t->onUpdateID3Tag_Album((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 26: _t->onUpdateID3Tag_Artist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Player::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_NewState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Player::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_SendPlaylist)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Player::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_SetPlayed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Player::*_t)(Track );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_SetPlayed)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Player::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_MusicStopped)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Player::*_t)(Track );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_PlayingTrack)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Player::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Player::sig_WriteData)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject Player::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Player.data,
      qt_meta_data_Player,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Player.stringdata0))
        return static_cast<void*>(const_cast< Player*>(this));
    return QObject::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void Player::sig_NewState(quint8 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Player::sig_SendPlaylist(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Player::sig_SetPlayed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Player::sig_SetPlayed(Track _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Player::sig_MusicStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void Player::sig_PlayingTrack(Track _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Player::sig_WriteData(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE