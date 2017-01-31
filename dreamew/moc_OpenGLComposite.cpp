/****************************************************************************
** Meta object code from reading C++ file 'OpenGLComposite.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "OpenGLComposite.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OpenGLComposite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OpenGLComposite[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x08,
      42,   16,   16,   16, 0x08,
      65,   60,   16,   16, 0x08,
     109,  105,   16,   16, 0x08,
     140,   16,   16,   16, 0x08,
     157,   16,   16,   16, 0x08,
     176,   16,   16,   16, 0x08,
     201,  195,   16,   16, 0x08,
     229,  220,   16,   16, 0x08,
     248,  246,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OpenGLComposite[] = {
    "OpenGLComposite\0\0_alpha\0alphaChanged(int)\0"
    "LumaChanged(bool)\0,,,,\0"
    "set_luma_param(int,bool,int,int,QColor)\0"
    ",,,\0set_pip_param(int,int,int,int)\0"
    "modeChanged(int)\0set_pvw_value(int)\0"
    "set_pgm_value(int)\0_wipe\0slot_set_wipe(int)\0"
    "_nv_iris\0irisChanged(int)\0,\0"
    "GLC_bindto(void**,int)\0"
};

void OpenGLComposite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData OpenGLComposite::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OpenGLComposite::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_OpenGLComposite,
      qt_meta_data_OpenGLComposite, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OpenGLComposite::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OpenGLComposite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OpenGLComposite::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLComposite))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
