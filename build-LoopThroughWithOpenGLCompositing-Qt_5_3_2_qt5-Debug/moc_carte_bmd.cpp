/****************************************************************************
** Meta object code from reading C++ file 'carte_bmd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dreamew/carte_bmd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carte_bmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_carte_bmd_t {
    QByteArrayData data[11];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_carte_bmd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_carte_bmd_t qt_meta_stringdata_carte_bmd = {
    {
QT_MOC_LITERAL(0, 0, 9), // "carte_bmd"
QT_MOC_LITERAL(1, 10, 14), // "emitVideoFrame"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "void**"
QT_MOC_LITERAL(4, 33, 17), // "VideoFrameArrived"
QT_MOC_LITERAL(5, 51, 25), // "IDeckLinkVideoInputFrame*"
QT_MOC_LITERAL(6, 77, 11), // "_inputFrame"
QT_MOC_LITERAL(7, 89, 17), // "_hasNoInputSource"
QT_MOC_LITERAL(8, 107, 24), // "AudioPacketStreamArrived"
QT_MOC_LITERAL(9, 132, 26), // "IDeckLinkAudioInputPacket*"
QT_MOC_LITERAL(10, 159, 12) // "_audioPacket"

    },
    "carte_bmd\0emitVideoFrame\0\0void**\0"
    "VideoFrameArrived\0IDeckLinkVideoInputFrame*\0"
    "_inputFrame\0_hasNoInputSource\0"
    "AudioPacketStreamArrived\0"
    "IDeckLinkAudioInputPacket*\0_audioPacket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_carte_bmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   34,    2, 0x08 /* Private */,
       8,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void carte_bmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        carte_bmd *_t = static_cast<carte_bmd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitVideoFrame((*reinterpret_cast< void**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->VideoFrameArrived((*reinterpret_cast< IDeckLinkVideoInputFrame*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->AudioPacketStreamArrived((*reinterpret_cast< IDeckLinkAudioInputPacket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (carte_bmd::*_t)(void * * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&carte_bmd::emitVideoFrame)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject carte_bmd::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_carte_bmd.data,
      qt_meta_data_carte_bmd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *carte_bmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *carte_bmd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_carte_bmd.stringdata0))
        return static_cast<void*>(const_cast< carte_bmd*>(this));
    return QObject::qt_metacast(_clname);
}

int carte_bmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void carte_bmd::emitVideoFrame(void * * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CaptureDelegate_t {
    QByteArrayData data[9];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CaptureDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CaptureDelegate_t qt_meta_stringdata_CaptureDelegate = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CaptureDelegate"
QT_MOC_LITERAL(1, 16, 19), // "captureFrameArrived"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 25), // "IDeckLinkVideoInputFrame*"
QT_MOC_LITERAL(4, 63, 10), // "videoFrame"
QT_MOC_LITERAL(5, 74, 16), // "hasNoInputSource"
QT_MOC_LITERAL(6, 91, 25), // "captureAudioPacketArrived"
QT_MOC_LITERAL(7, 117, 26), // "IDeckLinkAudioInputPacket*"
QT_MOC_LITERAL(8, 144, 11) // "audioPacket"

    },
    "CaptureDelegate\0captureFrameArrived\0"
    "\0IDeckLinkVideoInputFrame*\0videoFrame\0"
    "hasNoInputSource\0captureAudioPacketArrived\0"
    "IDeckLinkAudioInputPacket*\0audioPacket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CaptureDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       6,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void CaptureDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CaptureDelegate *_t = static_cast<CaptureDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->captureFrameArrived((*reinterpret_cast< IDeckLinkVideoInputFrame*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->captureAudioPacketArrived((*reinterpret_cast< IDeckLinkAudioInputPacket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CaptureDelegate::*_t)(IDeckLinkVideoInputFrame * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureDelegate::captureFrameArrived)) {
                *result = 0;
            }
        }
        {
            typedef void (CaptureDelegate::*_t)(IDeckLinkAudioInputPacket * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CaptureDelegate::captureAudioPacketArrived)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CaptureDelegate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CaptureDelegate.data,
      qt_meta_data_CaptureDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CaptureDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CaptureDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureDelegate.stringdata0))
        return static_cast<void*>(const_cast< CaptureDelegate*>(this));
    if (!strcmp(_clname, "IDeckLinkInputCallback"))
        return static_cast< IDeckLinkInputCallback*>(const_cast< CaptureDelegate*>(this));
    return QObject::qt_metacast(_clname);
}

int CaptureDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CaptureDelegate::captureFrameArrived(IDeckLinkVideoInputFrame * _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CaptureDelegate::captureAudioPacketArrived(IDeckLinkAudioInputPacket * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
