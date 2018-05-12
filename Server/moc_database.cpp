/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataBase_t {
    QByteArrayData data[27];
    char stringdata0[351];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataBase_t qt_meta_stringdata_DataBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataBase"
QT_MOC_LITERAL(1, 9, 11), // "sig_NewInfo"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "sig_PlayedSet"
QT_MOC_LITERAL(4, 36, 19), // "sig_SendArtistAlben"
QT_MOC_LITERAL(5, 56, 14), // "sig_SendTracks"
QT_MOC_LITERAL(6, 71, 12), // "QList<Track>"
QT_MOC_LITERAL(7, 84, 21), // "sig_SendUnsortedFiles"
QT_MOC_LITERAL(8, 106, 22), // "sig_UpdateID3Tag_Title"
QT_MOC_LITERAL(9, 129, 22), // "sig_UpdateID3Tag_Album"
QT_MOC_LITERAL(10, 152, 23), // "sig_UpdateID3Tag_Artist"
QT_MOC_LITERAL(11, 176, 9), // "onArchive"
QT_MOC_LITERAL(12, 186, 13), // "onArtistAlben"
QT_MOC_LITERAL(13, 200, 8), // "onDelete"
QT_MOC_LITERAL(14, 209, 13), // "onGetFavorite"
QT_MOC_LITERAL(15, 223, 11), // "onGetRandom"
QT_MOC_LITERAL(16, 235, 11), // "onGetTracks"
QT_MOC_LITERAL(17, 247, 18), // "onGetUnsortedFiles"
QT_MOC_LITERAL(18, 266, 9), // "onRestore"
QT_MOC_LITERAL(19, 276, 13), // "onSetFavorite"
QT_MOC_LITERAL(20, 290, 8), // "ramoc_ID"
QT_MOC_LITERAL(21, 299, 11), // "onSetID3Tag"
QT_MOC_LITERAL(22, 311, 3), // "str"
QT_MOC_LITERAL(23, 315, 11), // "onSetPlayed"
QT_MOC_LITERAL(24, 327, 11), // "string_File"
QT_MOC_LITERAL(25, 339, 5), // "Track"
QT_MOC_LITERAL(26, 345, 5) // "track"

    },
    "DataBase\0sig_NewInfo\0\0sig_PlayedSet\0"
    "sig_SendArtistAlben\0sig_SendTracks\0"
    "QList<Track>\0sig_SendUnsortedFiles\0"
    "sig_UpdateID3Tag_Title\0sig_UpdateID3Tag_Album\0"
    "sig_UpdateID3Tag_Artist\0onArchive\0"
    "onArtistAlben\0onDelete\0onGetFavorite\0"
    "onGetRandom\0onGetTracks\0onGetUnsortedFiles\0"
    "onRestore\0onSetFavorite\0ramoc_ID\0"
    "onSetID3Tag\0str\0onSetPlayed\0string_File\0"
    "Track\0track"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x06 /* Public */,
       3,    0,  117,    2, 0x06 /* Public */,
       4,    1,  118,    2, 0x06 /* Public */,
       5,    1,  121,    2, 0x06 /* Public */,
       7,    1,  124,    2, 0x06 /* Public */,
       8,    2,  127,    2, 0x06 /* Public */,
       9,    2,  132,    2, 0x06 /* Public */,
      10,    2,  137,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  142,    2, 0x0a /* Public */,
      12,    1,  145,    2, 0x0a /* Public */,
      13,    1,  148,    2, 0x0a /* Public */,
      14,    0,  151,    2, 0x0a /* Public */,
      15,    0,  152,    2, 0x0a /* Public */,
      16,    2,  153,    2, 0x0a /* Public */,
      17,    0,  158,    2, 0x0a /* Public */,
      18,    1,  159,    2, 0x0a /* Public */,
      19,    1,  162,    2, 0x0a /* Public */,
      21,    1,  165,    2, 0x0a /* Public */,
      23,    1,  168,    2, 0x0a /* Public */,
      23,    1,  171,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

void DataBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sig_PlayedSet(); break;
        case 2: _t->sig_SendArtistAlben((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->sig_SendTracks((*reinterpret_cast< QList<Track>(*)>(_a[1]))); break;
        case 4: _t->sig_SendUnsortedFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->sig_UpdateID3Tag_Title((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->sig_UpdateID3Tag_Album((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->sig_UpdateID3Tag_Artist((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onArchive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onArtistAlben((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->onDelete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->onGetFavorite(); break;
        case 12: _t->onGetRandom(); break;
        case 13: _t->onGetTracks((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 14: _t->onGetUnsortedFiles(); break;
        case 15: _t->onRestore((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->onSetFavorite((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onSetID3Tag((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->onSetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 19: _t->onSetPlayed((*reinterpret_cast< Track(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataBase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_NewInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_PlayedSet)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_SendArtistAlben)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QList<Track> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_SendTracks)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_SendUnsortedFiles)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_UpdateID3Tag_Title)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_UpdateID3Tag_Album)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (DataBase::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::sig_UpdateID3Tag_Artist)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject DataBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataBase.data,
      qt_meta_data_DataBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataBase.stringdata0))
        return static_cast<void*>(const_cast< DataBase*>(this));
    return QObject::qt_metacast(_clname);
}

int DataBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void DataBase::sig_NewInfo(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataBase::sig_PlayedSet()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DataBase::sig_SendArtistAlben(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DataBase::sig_SendTracks(QList<Track> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DataBase::sig_SendUnsortedFiles(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DataBase::sig_UpdateID3Tag_Title(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DataBase::sig_UpdateID3Tag_Album(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DataBase::sig_UpdateID3Tag_Artist(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
