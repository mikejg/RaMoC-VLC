/****************************************************************************
** Meta object code from reading C++ file 'vlc_process.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vlc_process.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vlc_process.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VLCProcess_t {
    QByteArrayData data[19];
    char stringdata0[247];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VLCProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VLCProcess_t qt_meta_stringdata_VLCProcess = {
    {
QT_MOC_LITERAL(0, 0, 10), // "VLCProcess"
QT_MOC_LITERAL(1, 11, 12), // "sig_NewState"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "s"
QT_MOC_LITERAL(4, 27, 13), // "sig_SetPlayed"
QT_MOC_LITERAL(5, 41, 13), // "sig_WriteData"
QT_MOC_LITERAL(6, 55, 13), // "onVLCFinished"
QT_MOC_LITERAL(7, 69, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 90, 14), // "onVLCReadError"
QT_MOC_LITERAL(9, 105, 15), // "onVLCReadStdOut"
QT_MOC_LITERAL(10, 121, 12), // "onVLCRestart"
QT_MOC_LITERAL(11, 134, 12), // "onVLCStarted"
QT_MOC_LITERAL(12, 147, 11), // "onVLCStatus"
QT_MOC_LITERAL(13, 159, 13), // "onVLCSubtitle"
QT_MOC_LITERAL(14, 173, 15), // "onVLCSocketRead"
QT_MOC_LITERAL(15, 189, 17), // "onYouTubeFinished"
QT_MOC_LITERAL(16, 207, 8), // "exitCode"
QT_MOC_LITERAL(17, 216, 10), // "exitStatus"
QT_MOC_LITERAL(18, 227, 19) // "onYouTubeReadStdOut"

    },
    "VLCProcess\0sig_NewState\0\0s\0sig_SetPlayed\0"
    "sig_WriteData\0onVLCFinished\0"
    "QProcess::ExitStatus\0onVLCReadError\0"
    "onVLCReadStdOut\0onVLCRestart\0onVLCStarted\0"
    "onVLCStatus\0onVLCSubtitle\0onVLCSocketRead\0"
    "onYouTubeFinished\0exitCode\0exitStatus\0"
    "onYouTubeReadStdOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VLCProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    2,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   90,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    2,  102,    2, 0x0a /* Public */,
      18,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   16,   17,
    QMetaType::Void,

       0        // eod
};

void VLCProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VLCProcess *_t = static_cast<VLCProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->sig_SetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_WriteData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->onVLCFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->onVLCReadError(); break;
        case 5: _t->onVLCReadStdOut(); break;
        case 6: _t->onVLCRestart(); break;
        case 7: _t->onVLCStarted(); break;
        case 8: _t->onVLCStatus(); break;
        case 9: _t->onVLCSubtitle(); break;
        case 10: _t->onVLCSocketRead(); break;
        case 11: _t->onYouTubeFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 12: _t->onYouTubeReadStdOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VLCProcess::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VLCProcess::sig_NewState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VLCProcess::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VLCProcess::sig_SetPlayed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VLCProcess::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VLCProcess::sig_WriteData)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject VLCProcess::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VLCProcess.data,
      qt_meta_data_VLCProcess,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VLCProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VLCProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VLCProcess.stringdata0))
        return static_cast<void*>(const_cast< VLCProcess*>(this));
    return QObject::qt_metacast(_clname);
}

int VLCProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void VLCProcess::sig_NewState(quint8 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VLCProcess::sig_SetPlayed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VLCProcess::sig_WriteData(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
