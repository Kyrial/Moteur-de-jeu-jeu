/****************************************************************************
** Meta object code from reading C++ file 'object.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Source/object.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Object_t {
    QByteArrayData data[20];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Object_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Object_t qt_meta_stringdata_Object = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Object"
QT_MOC_LITERAL(1, 7, 14), // "viewDirChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "vec"
QT_MOC_LITERAL(4, 27, 12), // "emitPosition"
QT_MOC_LITERAL(5, 40, 4), // "objM"
QT_MOC_LITERAL(6, 45, 8), // "emitTree"
QT_MOC_LITERAL(7, 54, 18), // "controleMouvements"
QT_MOC_LITERAL(8, 73, 10), // "QKeyEvent*"
QT_MOC_LITERAL(9, 84, 5), // "event"
QT_MOC_LITERAL(10, 90, 10), // "getDirView"
QT_MOC_LITERAL(11, 101, 7), // "dirView"
QT_MOC_LITERAL(12, 109, 13), // "getProjection"
QT_MOC_LITERAL(13, 123, 4), // "proj"
QT_MOC_LITERAL(14, 128, 16), // "controleRotation"
QT_MOC_LITERAL(15, 145, 21), // "keyPressedChangedMove"
QT_MOC_LITERAL(16, 167, 7), // "QEvent*"
QT_MOC_LITERAL(17, 175, 23), // "keyPressedChangedRotate"
QT_MOC_LITERAL(18, 199, 15), // "mapCoordChanged"
QT_MOC_LITERAL(19, 215, 10) // "updateTree"

    },
    "Object\0viewDirChanged\0\0vec\0emitPosition\0"
    "objM\0emitTree\0controleMouvements\0"
    "QKeyEvent*\0event\0getDirView\0dirView\0"
    "getProjection\0proj\0controleRotation\0"
    "keyPressedChangedMove\0QEvent*\0"
    "keyPressedChangedRotate\0mapCoordChanged\0"
    "updateTree"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Object[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       6,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   80,    2, 0x0a /* Public */,
      10,    1,   83,    2, 0x0a /* Public */,
      12,    1,   86,    2, 0x0a /* Public */,
      14,    1,   89,    2, 0x0a /* Public */,
      15,    1,   92,    2, 0x0a /* Public */,
      17,    1,   95,    2, 0x0a /* Public */,
      18,    2,   98,    2, 0x0a /* Public */,
      19,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVector3D,    3,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QMatrix4x4,    3,    5,
    QMetaType::Void, QMetaType::QVector3D,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QVector3D,   11,
    QMetaType::Void, QMetaType::QMatrix4x4,   13,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 16,    9,
    QMetaType::Void, 0x80000000 | 16,    9,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QMatrix4x4,    3,    5,
    QMetaType::Void, QMetaType::QVector3D,    3,

       0        // eod
};

void Object::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Object *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->viewDirChanged((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 1: _t->emitPosition((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QMatrix4x4(*)>(_a[2]))); break;
        case 2: _t->emitTree((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 3: _t->controleMouvements((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->getDirView((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 5: _t->getProjection((*reinterpret_cast< QMatrix4x4(*)>(_a[1]))); break;
        case 6: _t->controleRotation((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 7: _t->keyPressedChangedMove((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 8: _t->keyPressedChangedRotate((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 9: _t->mapCoordChanged((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QMatrix4x4(*)>(_a[2]))); break;
        case 10: _t->updateTree((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Object::*)(QVector3D );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Object::viewDirChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Object::*)(QVector3D , QMatrix4x4 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Object::emitPosition)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Object::*)(QVector3D );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Object::emitTree)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Object::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Object.data,
    qt_meta_data_Object,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Object::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Object::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Object.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Object::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Object::viewDirChanged(QVector3D _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Object::emitPosition(QVector3D _t1, QMatrix4x4 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Object::emitTree(QVector3D _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
