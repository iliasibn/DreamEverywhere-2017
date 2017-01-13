/****************************************************************************
** Meta object code from reading C++ file 'carte_bmd.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "carte_bmd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'carte_bmd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_carte_bmd[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   11,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      70,   40,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_carte_bmd[] = {
    "carte_bmd\0\0,\0emitVideoFrame(void**,int)\0"
    "_inputFrame,_hasNoInputSource\0"
    "VideoFrameArrived(IDeckLinkVideoInputFrame*,bool)\0"
};

void carte_bmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        carte_bmd *_t = static_cast<carte_bmd *>(_o);
        switch (_id) {
        case 0: _t->emitVideoFrame((*reinterpret_cast< void**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->VideoFrameArrived((*reinterpret_cast< IDeckLinkVideoInputFrame*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData carte_bmd::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject carte_bmd::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_carte_bmd,
      qt_meta_data_carte_bmd, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &carte_bmd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *carte_bmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *carte_bmd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_carte_bmd))
        return static_cast<void*>(const_cast< carte_bmd*>(this));
    return QObject::qt_metacast(_clname);
}

int carte_bmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void carte_bmd::emitVideoFrame(void * * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_CaptureDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      45,   17,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CaptureDelegate[] = {
    "CaptureDelegate\0\0videoFrame,hasNoInputSource\0"
    "captureFrameArrived(IDeckLinkVideoInputFrame*,bool)\0"
};

void CaptureDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CaptureDelegate *_t = static_cast<CaptureDelegate *>(_o);
        switch (_id) {
        case 0: _t->captureFrameArrived((*reinterpret_cast< IDeckLinkVideoInputFrame*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CaptureDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CaptureDelegate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CaptureDelegate,
      qt_meta_data_CaptureDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CaptureDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CaptureDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CaptureDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CaptureDelegate))
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
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CaptureDelegate::captureFrameArrived(IDeckLinkVideoInputFrame * _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_PlayoutDelegate[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PlayoutDelegate[] = {
    "PlayoutDelegate\0\0result\0"
    "playoutFrameCompleted(BMDOutputFrameCompletionResult)\0"
};

void PlayoutDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayoutDelegate *_t = static_cast<PlayoutDelegate *>(_o);
        switch (_id) {
        case 0: _t->playoutFrameCompleted((*reinterpret_cast< BMDOutputFrameCompletionResult(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayoutDelegate::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayoutDelegate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlayoutDelegate,
      qt_meta_data_PlayoutDelegate, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayoutDelegate::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayoutDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayoutDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayoutDelegate))
        return static_cast<void*>(const_cast< PlayoutDelegate*>(this));
    if (!strcmp(_clname, "IDeckLinkVideoOutputCallback"))
        return static_cast< IDeckLinkVideoOutputCallback*>(const_cast< PlayoutDelegate*>(this));
    return QObject::qt_metacast(_clname);
}

int PlayoutDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PlayoutDelegate::playoutFrameCompleted(BMDOutputFrameCompletionResult _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
