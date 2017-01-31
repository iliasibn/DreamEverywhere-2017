/****************************************************************************
** Meta object code from reading C++ file 'gui_keyer.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui_keyer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_keyer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KeyerSettings[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      59,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      84,   14,   14,   14, 0x0a,
     103,   14,   14,   14, 0x0a,
     125,   14,   14,   14, 0x0a,
     149,   14,   14,   14, 0x0a,
     170,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KeyerSettings[] = {
    "KeyerSettings\0\0,,,,\0"
    "keyer_changes(int,bool,int,int,QColor)\0"
    "keyer_change_source(int)\0save_settings(int)\0"
    "slot_change_mode(int)\0slot_index_changed(int)\0"
    "slot_color_picking()\0"
    "slot_current_color_changed(QColor)\0"
};

void KeyerSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KeyerSettings *_t = static_cast<KeyerSettings *>(_o);
        switch (_id) {
        case 0: _t->keyer_changes((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5]))); break;
        case 1: _t->keyer_change_source((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->save_settings((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slot_change_mode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slot_index_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_color_picking(); break;
        case 6: _t->slot_current_color_changed((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData KeyerSettings::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject KeyerSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KeyerSettings,
      qt_meta_data_KeyerSettings, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KeyerSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KeyerSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KeyerSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KeyerSettings))
        return static_cast<void*>(const_cast< KeyerSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int KeyerSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void KeyerSettings::keyer_changes(int _t1, bool _t2, int _t3, int _t4, QColor _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyerSettings::keyer_change_source(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
