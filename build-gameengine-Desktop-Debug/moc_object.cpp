/****************************************************************************
** Meta object code from reading C++ file 'object.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Source/object.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'object.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Object_t {
    QByteArrayData data[11];
    char stringdata0[101];
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
QT_MOC_LITERAL(4, 27, 18), // "controleMouvements"
QT_MOC_LITERAL(5, 46, 10), // "QKeyEvent*"
QT_MOC_LITERAL(6, 57, 5), // "event"
QT_MOC_LITERAL(7, 63, 10), // "getDirView"
QT_MOC_LITERAL(8, 74, 7), // "dirView"
QT_MOC_LITERAL(9, 82, 13), // "getProjection"
QT_MOC_LITERAL(10, 96, 4) // "proj"

    },
    "Object\0viewDirChanged\0\0vec\0"
    "controleMouvements\0QKeyEvent*\0event\0"
    "getDirView\0dirView\0getProjection\0proj"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Object[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       7,    1,   40,    2, 0x0a /* Public */,
       9,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVector3D,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::QVector3D,    8,
    QMetaType::Void, QMetaType::QMatrix4x4,   10,

       0        // eod
};

void Object::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Object *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->viewDirChanged((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 1: _t->controleMouvements((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->getDirView((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 3: _t->getProjection((*reinterpret_cast< QMatrix4x4(*)>(_a[1]))); break;
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
    }
}

QT_INIT_METAOBJECT const QMetaObject Object::staticMetaObject = { {
    &QObject::staticMetaObject,
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Object::viewDirChanged(QVector3D _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
