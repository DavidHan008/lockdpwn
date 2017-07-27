/****************************************************************************
** Meta object code from reading C++ file 'rndf_manager_main.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/rndf_manager/inc/rndf_manager_main.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rndf_manager_main.h' doesn't include <QObject>."
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
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      41,   11,   11,   11, 0x0a,
      69,   11,   11,   11, 0x0a,
      97,   11,   11,   11, 0x0a,
     124,   11,   11,   11, 0x0a,
     148,   11,   11,   11, 0x0a,
     171,   11,   11,   11, 0x0a,
     197,   11,   11,   11, 0x0a,
     226,   11,   11,   11, 0x0a,
     257,   11,   11,   11, 0x0a,
     288,   11,   11,   11, 0x0a,
     319,   11,   11,   11, 0x0a,
     350,   11,   11,   11, 0x0a,
     381,   11,   11,   11, 0x0a,
     410,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_RNDFFileFindBtn_clicked()\0"
    "on_MDFFileFindBtn_clicked()\0"
    "on_StartPubMsgBtn_clicked()\0"
    "on_StopPubMsgBtn_clicked()\0"
    "on_BuildGraph_clicked()\0on_SearchBtn_clicked()\0"
    "on_PubSegMsgBtn_clicked()\0"
    "on_PubAllSegMsgBtn_clicked()\0"
    "on_pushButton_check1_clicked()\0"
    "on_pushButton_check2_clicked()\0"
    "on_pushButton_check3_clicked()\0"
    "on_pushButton_check4_clicked()\0"
    "on_pushButton_check5_clicked()\0"
    "OnCheckBoxTarNode1_clicked()\0"
    "OnCheckBoxTarNode2_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_RNDFFileFindBtn_clicked(); break;
        case 1: _t->on_MDFFileFindBtn_clicked(); break;
        case 2: _t->on_StartPubMsgBtn_clicked(); break;
        case 3: _t->on_StopPubMsgBtn_clicked(); break;
        case 4: _t->on_BuildGraph_clicked(); break;
        case 5: _t->on_SearchBtn_clicked(); break;
        case 6: _t->on_PubSegMsgBtn_clicked(); break;
        case 7: _t->on_PubAllSegMsgBtn_clicked(); break;
        case 8: _t->on_pushButton_check1_clicked(); break;
        case 9: _t->on_pushButton_check2_clicked(); break;
        case 10: _t->on_pushButton_check3_clicked(); break;
        case 11: _t->on_pushButton_check4_clicked(); break;
        case 12: _t->on_pushButton_check5_clicked(); break;
        case 13: _t->OnCheckBoxTarNode1_clicked(); break;
        case 14: _t->OnCheckBoxTarNode2_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
