/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BuildOnMe-master/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[15];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "showImageSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "play"
QT_MOC_LITERAL(4, 33, 5), // "pause"
QT_MOC_LITERAL(5, 39, 11), // "onShowFrame"
QT_MOC_LITERAL(6, 51, 5), // "frame"
QT_MOC_LITERAL(7, 57, 8), // "position"
QT_MOC_LITERAL(8, 66, 12), // "onLineReturn"
QT_MOC_LITERAL(9, 79, 8), // "timecode"
QT_MOC_LITERAL(10, 88, 13), // "onSliderMoved"
QT_MOC_LITERAL(11, 102, 12), // "slotcombobox"
QT_MOC_LITERAL(12, 115, 5), // "index"
QT_MOC_LITERAL(13, 121, 20), // "quitter_windowreseau"
QT_MOC_LITERAL(14, 142, 15) // "valider_adresse"

    },
    "MainWindow\0showImageSignal\0\0play\0pause\0"
    "onShowFrame\0frame\0position\0onLineReturn\0"
    "timecode\0onSliderMoved\0slotcombobox\0"
    "index\0quitter_windowreseau\0valider_adresse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   62,    2, 0x0a /* Public */,
       4,    0,   63,    2, 0x0a /* Public */,
       5,    2,   64,    2, 0x0a /* Public */,
       8,    1,   69,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      11,    1,   75,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x0a /* Public */,
      14,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::VoidStar, QMetaType::UInt,    6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showImageSignal((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->play(); break;
        case 2: _t->pause(); break;
        case 3: _t->onShowFrame((*reinterpret_cast< void*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 4: _t->onLineReturn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->slotcombobox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->quitter_windowreseau(); break;
        case 8: _t->valider_adresse(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QImage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::showImageSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::showImageSignal(QImage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
