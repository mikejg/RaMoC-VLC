/****************************************************************************
** Meta object code from reading C++ file 'omx_process.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "omx_process.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'omx_process.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OMXProcess_t {
    QByteArrayData data[11];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OMXProcess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OMXProcess_t qt_meta_stringdata_OMXProcess = {
    {
QT_MOC_LITERAL(0, 0, 10), // "OMXProcess"
QT_MOC_LITERAL(1, 11, 12), // "sig_NewState"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "s"
QT_MOC_LITERAL(4, 27, 13), // "sig_SetPlayed"
QT_MOC_LITERAL(5, 41, 21), // "playerFinishedHandler"
QT_MOC_LITERAL(6, 63, 8), // "exitCode"
QT_MOC_LITERAL(7, 72, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(8, 93, 10), // "exitStatus"
QT_MOC_LITERAL(9, 104, 20), // "playerStartedHandler"
QT_MOC_LITERAL(10, 125, 9) // "setPlayed"

    },
    "OMXProcess\0sig_NewState\0\0s\0sig_SetPlayed\0"
    "playerFinishedHandler\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus\0"
    "playerStartedHandler\0setPlayed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OMXProcess[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   45,    2, 0x0a /* Public */,
       9,    0,   50,    2, 0x0a /* Public */,
      10,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OMXProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OMXProcess *_t = static_cast<OMXProcess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_NewState((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->sig_SetPlayed((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->playerFinishedHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 3: _t->playerStartedHandler(); break;
        case 4: _t->setPlayed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OMXProcess::*_t)(quint8 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OMXProcess::sig_NewState)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (OMXProcess::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OMXProcess::sig_SetPlayed)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject OMXProcess::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OMXProcess.data,
      qt_meta_data_OMXProcess,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OMXProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OMXProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OMXProcess.stringdata0))
        return static_cast<void*>(const_cast< OMXProcess*>(this));
    return QObject::qt_metacast(_clname);
}

int OMXProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void OMXProcess::sig_NewState(quint8 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OMXProcess::sig_SetPlayed(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
