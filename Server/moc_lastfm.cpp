/****************************************************************************
** Meta object code from reading C++ file 'lastfm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lastfm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lastfm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_M_LastFm_t {
    QByteArrayData data[10];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_M_LastFm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_M_LastFm_t qt_meta_stringdata_M_LastFm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "M_LastFm"
QT_MOC_LITERAL(1, 9, 17), // "new_Artist_Pixmap"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "new_Album_Pixmap"
QT_MOC_LITERAL(4, 45, 26), // "slot_parse_Album_Image_Url"
QT_MOC_LITERAL(5, 72, 27), // "slot_parse_Artist_Image_Url"
QT_MOC_LITERAL(6, 100, 21), // "slot_load_Album_Image"
QT_MOC_LITERAL(7, 122, 22), // "slot_load_Artist_Image"
QT_MOC_LITERAL(8, 145, 9), // "slotError"
QT_MOC_LITERAL(9, 155, 27) // "QNetworkReply::NetworkError"

    },
    "M_LastFm\0new_Artist_Pixmap\0\0"
    "new_Album_Pixmap\0slot_parse_Album_Image_Url\0"
    "slot_parse_Artist_Image_Url\0"
    "slot_load_Album_Image\0slot_load_Artist_Image\0"
    "slotError\0QNetworkReply::NetworkError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_M_LastFm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   55,    2, 0x0a /* Public */,
       5,    0,   56,    2, 0x0a /* Public */,
       6,    0,   57,    2, 0x0a /* Public */,
       7,    0,   58,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void M_LastFm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        M_LastFm *_t = static_cast<M_LastFm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_Artist_Pixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 1: _t->new_Album_Pixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->slot_parse_Album_Image_Url(); break;
        case 3: _t->slot_parse_Artist_Image_Url(); break;
        case 4: _t->slot_load_Album_Image(); break;
        case 5: _t->slot_load_Artist_Image(); break;
        case 6: _t->slotError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (M_LastFm::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_LastFm::new_Artist_Pixmap)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (M_LastFm::*_t)(QPixmap );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&M_LastFm::new_Album_Pixmap)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject M_LastFm::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_M_LastFm.data,
      qt_meta_data_M_LastFm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *M_LastFm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *M_LastFm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_M_LastFm.stringdata0))
        return static_cast<void*>(const_cast< M_LastFm*>(this));
    return QObject::qt_metacast(_clname);
}

int M_LastFm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void M_LastFm::new_Artist_Pixmap(QPixmap _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void M_LastFm::new_Album_Pixmap(QPixmap _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
