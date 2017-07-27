/****************************************************************************
** Meta object code from reading C++ file 'controller_main.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/controller/inc/controller_main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x0a,
      35,   12,   11,   11, 0x0a,
      60,   12,   11,   11, 0x0a,
      81,   11,   77,   11, 0x0a,
      95,   11,   11,   11, 0x0a,
     127,   11,   11,   11, 0x0a,
     158,   11,   11,   11, 0x0a,
     188,   11,   11,   11, 0x0a,
     217,   11,   11,   11, 0x0a,
     244,   11,   11,   11, 0x0a,
     271,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0value\0setLCDValue(int)\0"
    "setLCDValue_tar_vel(int)\0Set_tar_vel(int)\0"
    "int\0getLCDValue()\0on_pushButton_start_2_clicked()\0"
    "on_pushButton_stop_2_clicked()\0"
    "on_pushButton_start_clicked()\0"
    "on_pushButton_stop_clicked()\0"
    "on_pushButton_LF_clicked()\0"
    "on_pushButton_RF_clicked()\0"
    "on_pushButton_Z_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setLCDValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setLCDValue_tar_vel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->Set_tar_vel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: { int _r = _t->getLCDValue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->on_pushButton_start_2_clicked(); break;
        case 5: _t->on_pushButton_stop_2_clicked(); break;
        case 6: _t->on_pushButton_start_clicked(); break;
        case 7: _t->on_pushButton_stop_clicked(); break;
        case 8: _t->on_pushButton_LF_clicked(); break;
        case 9: _t->on_pushButton_RF_clicked(); break;
        case 10: _t->on_pushButton_Z_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
