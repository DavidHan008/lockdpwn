/****************************************************************************
** Meta object code from reading C++ file 'GridMapDisplay.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/grid_map/grid_map_rviz_plugin/include/grid_map_rviz_plugin/GridMapDisplay.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GridMapDisplay.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_grid_map_rviz_plugin__GridMapDisplay[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      38,   37,   37,   37, 0x08,
      60,   37,   37,   37, 0x08,
      79,   37,   37,   37, 0x08,
      97,   37,   37,   37, 0x08,
     116,   37,   37,   37, 0x08,
     151,   37,   37,   37, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_grid_map_rviz_plugin__GridMapDisplay[] = {
    "grid_map_rviz_plugin::GridMapDisplay\0"
    "\0updateHistoryLength()\0updateHeightMode()\0"
    "updateColorMode()\0updateUseRainbow()\0"
    "updateAutocomputeIntensityBounds()\0"
    "updateVisualization()\0"
};

void grid_map_rviz_plugin::GridMapDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GridMapDisplay *_t = static_cast<GridMapDisplay *>(_o);
        switch (_id) {
        case 0: _t->updateHistoryLength(); break;
        case 1: _t->updateHeightMode(); break;
        case 2: _t->updateColorMode(); break;
        case 3: _t->updateUseRainbow(); break;
        case 4: _t->updateAutocomputeIntensityBounds(); break;
        case 5: _t->updateVisualization(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData grid_map_rviz_plugin::GridMapDisplay::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject grid_map_rviz_plugin::GridMapDisplay::staticMetaObject = {
    { &MessageFilterDisplayMod<grid_map_msgs::GridMap,grid_map_msgs::GridMapInfo>::staticMetaObject, qt_meta_stringdata_grid_map_rviz_plugin__GridMapDisplay,
      qt_meta_data_grid_map_rviz_plugin__GridMapDisplay, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &grid_map_rviz_plugin::GridMapDisplay::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *grid_map_rviz_plugin::GridMapDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *grid_map_rviz_plugin::GridMapDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_grid_map_rviz_plugin__GridMapDisplay))
        return static_cast<void*>(const_cast< GridMapDisplay*>(this));
    typedef MessageFilterDisplayMod<grid_map_msgs::GridMap,grid_map_msgs::GridMapInfo> QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int grid_map_rviz_plugin::GridMapDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef MessageFilterDisplayMod<grid_map_msgs::GridMap,grid_map_msgs::GridMapInfo> QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
