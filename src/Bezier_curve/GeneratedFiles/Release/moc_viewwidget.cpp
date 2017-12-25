/****************************************************************************
** Meta object code from reading C++ file 'viewwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../viewwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewWidget_t {
    QByteArrayData data[16];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewWidget_t qt_meta_stringdata_ViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ViewWidget"
QT_MOC_LITERAL(1, 11, 8), // "OpenFile"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "SaveFile"
QT_MOC_LITERAL(4, 30, 9), // "newFigure"
QT_MOC_LITERAL(5, 40, 12), // "deleteFigure"
QT_MOC_LITERAL(6, 53, 8), // "Evaluate"
QT_MOC_LITERAL(7, 62, 9), // "Subdivide"
QT_MOC_LITERAL(8, 72, 13), // "DegreeElevate"
QT_MOC_LITERAL(9, 86, 12), // "SetParameter"
QT_MOC_LITERAL(10, 99, 1), // "n"
QT_MOC_LITERAL(11, 101, 11), // "CheckBezier"
QT_MOC_LITERAL(12, 113, 2), // "bv"
QT_MOC_LITERAL(13, 116, 14), // "CheckFourPoint"
QT_MOC_LITERAL(14, 131, 14), // "CheckDrawFrame"
QT_MOC_LITERAL(15, 146, 14) // "CheckDrawCurve"

    },
    "ViewWidget\0OpenFile\0\0SaveFile\0newFigure\0"
    "deleteFigure\0Evaluate\0Subdivide\0"
    "DegreeElevate\0SetParameter\0n\0CheckBezier\0"
    "bv\0CheckFourPoint\0CheckDrawFrame\0"
    "CheckDrawCurve"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    1,   81,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      13,    1,   87,    2, 0x0a /* Public */,
      14,    1,   90,    2, 0x0a /* Public */,
      15,    1,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void ViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewWidget *_t = static_cast<ViewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenFile(); break;
        case 1: _t->SaveFile(); break;
        case 2: _t->newFigure(); break;
        case 3: _t->deleteFigure(); break;
        case 4: _t->Evaluate(); break;
        case 5: _t->Subdivide(); break;
        case 6: _t->DegreeElevate(); break;
        case 7: _t->SetParameter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->CheckBezier((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->CheckFourPoint((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->CheckDrawFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->CheckDrawCurve((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ViewWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ViewWidget.data,
      qt_meta_data_ViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewWidget.stringdata0))
        return static_cast<void*>(const_cast< ViewWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
