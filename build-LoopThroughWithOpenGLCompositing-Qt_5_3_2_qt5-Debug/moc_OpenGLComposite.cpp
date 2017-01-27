/****************************************************************************
** Meta object code from reading C++ file 'OpenGLComposite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dreamew/OpenGLComposite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OpenGLComposite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OpenGLComposite_t {
    QByteArrayData data[16];
    char stringdata[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGLComposite_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGLComposite_t qt_meta_stringdata_OpenGLComposite = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 12),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 6),
QT_MOC_LITERAL(4, 37, 11),
QT_MOC_LITERAL(5, 49, 14),
QT_MOC_LITERAL(6, 64, 13),
QT_MOC_LITERAL(7, 78, 11),
QT_MOC_LITERAL(8, 90, 13),
QT_MOC_LITERAL(9, 104, 13),
QT_MOC_LITERAL(10, 118, 13),
QT_MOC_LITERAL(11, 132, 5),
QT_MOC_LITERAL(12, 138, 11),
QT_MOC_LITERAL(13, 150, 8),
QT_MOC_LITERAL(14, 159, 10),
QT_MOC_LITERAL(15, 170, 6)
    },
    "OpenGLComposite\0alphaChanged\0\0_alpha\0"
    "LumaChanged\0set_luma_param\0set_pip_param\0"
    "modeChanged\0set_pvw_value\0set_pgm_value\0"
    "slot_set_wipe\0_wipe\0irisChanged\0"
    "_nv_iris\0GLC_bindto\0void**"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLComposite[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       5,    5,   70,    2, 0x08 /* Private */,
       6,    4,   81,    2, 0x08 /* Private */,
       7,    1,   90,    2, 0x08 /* Private */,
       8,    1,   93,    2, 0x08 /* Private */,
       9,    1,   96,    2, 0x08 /* Private */,
      10,    1,   99,    2, 0x08 /* Private */,
      12,    1,  102,    2, 0x08 /* Private */,
      14,    2,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::QColor,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,    2,    2,

       0        // eod
};

void OpenGLComposite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OpenGLComposite *_t = static_cast<OpenGLComposite *>(_o);
        switch (_id) {
        case 0: _t->alphaChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->LumaChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->set_luma_param((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5]))); break;
        case 3: _t->set_pip_param((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->modeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->set_pvw_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->set_pgm_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->slot_set_wipe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->irisChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->GLC_bindto((*reinterpret_cast< void**(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject OpenGLComposite::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_OpenGLComposite.data,
      qt_meta_data_OpenGLComposite,  qt_static_metacall, 0, 0}
};


const QMetaObject *OpenGLComposite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLComposite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLComposite.stringdata))
        return static_cast<void*>(const_cast< OpenGLComposite*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int OpenGLComposite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
