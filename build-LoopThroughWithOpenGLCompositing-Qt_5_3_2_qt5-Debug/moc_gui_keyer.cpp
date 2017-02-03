/****************************************************************************
** Meta object code from reading C++ file 'gui_keyer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dreamew/gui_keyer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_keyer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KeyerSettings_t {
    QByteArrayData data[9];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyerSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyerSettings_t qt_meta_stringdata_KeyerSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "KeyerSettings"
QT_MOC_LITERAL(1, 14, 13), // "keyer_changes"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "keyer_change_source"
QT_MOC_LITERAL(4, 49, 13), // "save_settings"
QT_MOC_LITERAL(5, 63, 16), // "slot_change_mode"
QT_MOC_LITERAL(6, 80, 18), // "slot_index_changed"
QT_MOC_LITERAL(7, 99, 18), // "slot_color_picking"
QT_MOC_LITERAL(8, 118, 26) // "slot_current_color_changed"

    },
    "KeyerSettings\0keyer_changes\0\0"
    "keyer_change_source\0save_settings\0"
    "slot_change_mode\0slot_index_changed\0"
    "slot_color_picking\0slot_current_color_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyerSettings[] = {

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
       1,    5,   49,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   63,    2, 0x0a /* Public */,
       5,    1,   66,    2, 0x0a /* Public */,
       6,    1,   69,    2, 0x0a /* Public */,
       7,    0,   72,    2, 0x0a /* Public */,
       8,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::QColor,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    2,

       0        // eod
};

void KeyerSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyerSettings *_t = static_cast<KeyerSettings *>(_o);
        Q_UNUSED(_t)
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
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeyerSettings::*_t)(int , bool , int , int , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyerSettings::keyer_changes)) {
                *result = 0;
            }
        }
        {
            typedef void (KeyerSettings::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyerSettings::keyer_change_source)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject KeyerSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KeyerSettings.data,
      qt_meta_data_KeyerSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KeyerSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyerSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KeyerSettings.stringdata0))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void KeyerSettings::keyer_changes(int _t1, bool _t2, int _t3, int _t4, QColor _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyerSettings::keyer_change_source(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
