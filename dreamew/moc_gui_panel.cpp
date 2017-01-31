/****************************************************************************
** Meta object code from reading C++ file 'gui_panel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui_panel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gui_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Panel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      36,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,
      24,    6,    6,    6, 0x05,
      41,    6,    6,    6, 0x05,
      69,   63,    6,    6, 0x05,
      89,   63,    6,    6, 0x05,
     139,  109,    6,    6, 0x05,
     197,  175,    6,    6, 0x05,
     224,    6,    6,    6, 0x05,
     249,    6,    6,    6, 0x05,
     276,    6,    6,    6, 0x05,
     300,    6,    6,    6, 0x05,
     325,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
     335,    6,    6,    6, 0x0a,
     351,    6,    6,    6, 0x0a,
     367,    6,    6,    6, 0x0a,
     384,    6,    6,    6, 0x0a,
     400,    6,    6,    6, 0x0a,
     422,    6,    6,    6, 0x0a,
     438,    6,    6,    6, 0x0a,
     454,    6,    6,    6, 0x0a,
     479,  469,    6,    6, 0x0a,
     499,  497,    6,    6, 0x0a,
     525,    6,    6,    6, 0x0a,
     545,  109,    6,    6, 0x0a,
     595,  175,    6,    6, 0x0a,
     638,  635,    6,    6, 0x0a,
     668,  497,    6,    6, 0x0a,
     701,    6,    6,    6, 0x0a,
     726,   63,    6,    6, 0x0a,
     745,    6,    6,    6, 0x0a,
     768,    6,    6,    6, 0x0a,
     795,    6,    6,    6, 0x0a,
     815,    6,    6,    6, 0x0a,
     842,    6,    6,    6, 0x0a,
     869,    6,    6,    6, 0x0a,
     882,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Panel[] = {
    "Panel\0\0pvw_changed(int)\0pgm_changed(int)\0"
    "wipe_mix_changed(int)\0index\0"
    "signal_maj_pgm(int)\0signal_maj_pvw(int)\0"
    "id,mode,seuil,tolerance,color\0"
    "param_luma(int,bool,int,int,QColor)\0"
    "taille,x,y,modeencour\0param_pip(int,int,int,int)\0"
    "signal_alpha_change(int)\0"
    "signal_depart_change(bool)\0"
    "signal_change_wipe(int)\0"
    "signal_iris_changed(int)\0closing()\0"
    "slot_clic_pvw()\0slot_clic_pgm()\0"
    "slot_clic_wipe()\0slot_clic_mix()\0"
    "slot_clic_autotrans()\0slot_clic_cut()\0"
    "slot_clic_pip()\0slot_lecture()\0nvl_value\0"
    "tbar_changed(int)\0p\0slot_config_keyer(QPoint)\0"
    "slot_config_keyer()\0"
    "slot_save_keyer_settings(int,bool,int,int,QColor)\0"
    "slot_save_pip_settings(int,int,int,int)\0"
    "id\0slot_keyer_change_source(int)\0"
    "slot_edit_nom_bouton_pgm(QPoint)\0"
    "slot_change_nom_bouton()\0combo_changed(int)\0"
    "slot_iris_changed(int)\0"
    "slot_change_current_wipe()\0"
    "setValueInvert(int)\0change_pressed_color_pvw()\0"
    "change_pressed_color_pgm()\0reset_iris()\0"
    "uncheck_all()\0"
};

void Panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Panel *_t = static_cast<Panel *>(_o);
        switch (_id) {
        case 0: _t->pvw_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->pgm_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->wipe_mix_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signal_maj_pgm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signal_maj_pvw((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->param_luma((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5]))); break;
        case 6: _t->param_pip((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: _t->signal_alpha_change((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->signal_depart_change((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->signal_change_wipe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->signal_iris_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->closing(); break;
        case 12: _t->slot_clic_pvw(); break;
        case 13: _t->slot_clic_pgm(); break;
        case 14: _t->slot_clic_wipe(); break;
        case 15: _t->slot_clic_mix(); break;
        case 16: _t->slot_clic_autotrans(); break;
        case 17: _t->slot_clic_cut(); break;
        case 18: _t->slot_clic_pip(); break;
        case 19: _t->slot_lecture(); break;
        case 20: _t->tbar_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->slot_config_keyer((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 22: _t->slot_config_keyer(); break;
        case 23: _t->slot_save_keyer_settings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QColor(*)>(_a[5]))); break;
        case 24: _t->slot_save_pip_settings((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 25: _t->slot_keyer_change_source((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->slot_edit_nom_bouton_pgm((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 27: _t->slot_change_nom_bouton(); break;
        case 28: _t->combo_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->slot_iris_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->slot_change_current_wipe(); break;
        case 31: _t->setValueInvert((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->change_pressed_color_pvw(); break;
        case 33: _t->change_pressed_color_pgm(); break;
        case 34: _t->reset_iris(); break;
        case 35: _t->uncheck_all(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Panel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Panel::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Panel,
      qt_meta_data_Panel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Panel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Panel))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 36)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 36;
    }
    return _id;
}

// SIGNAL 0
void Panel::pvw_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Panel::pgm_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Panel::wipe_mix_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Panel::signal_maj_pgm(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Panel::signal_maj_pvw(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Panel::param_luma(int _t1, bool _t2, int _t3, int _t4, QColor _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Panel::param_pip(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Panel::signal_alpha_change(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Panel::signal_depart_change(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Panel::signal_change_wipe(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void Panel::signal_iris_changed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void Panel::closing()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}
QT_END_MOC_NAMESPACE
