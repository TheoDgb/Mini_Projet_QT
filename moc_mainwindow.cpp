/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "newFile"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "open"
QT_MOC_LITERAL(4, 25, 4), // "quit"
QT_MOC_LITERAL(5, 30, 4), // "save"
QT_MOC_LITERAL(6, 35, 6), // "saveAs"
QT_MOC_LITERAL(7, 42, 6), // "zoomIn"
QT_MOC_LITERAL(8, 49, 7), // "zoomOut"
QT_MOC_LITERAL(9, 57, 7), // "pinceau"
QT_MOC_LITERAL(10, 65, 7), // "checked"
QT_MOC_LITERAL(11, 73, 15), // "rectangleSelect"
QT_MOC_LITERAL(12, 89, 16), // "chooseBrushColor"
QT_MOC_LITERAL(13, 106, 15), // "chooseBrushSize"
QT_MOC_LITERAL(14, 122, 10), // "chooseForm"
QT_MOC_LITERAL(15, 133, 9), // "pixelGrid"
QT_MOC_LITERAL(16, 143, 11), // "resizeImage"
QT_MOC_LITERAL(17, 155, 12), // "resizeCanvas"
QT_MOC_LITERAL(18, 168, 16), // "flipHorizontally"
QT_MOC_LITERAL(19, 185, 14), // "flipVertically"
QT_MOC_LITERAL(20, 200, 11), // "rotateRight"
QT_MOC_LITERAL(21, 212, 10), // "rotateLeft"
QT_MOC_LITERAL(22, 223, 12) // "rotateBehind"

    },
    "MainWindow\0newFile\0\0open\0quit\0save\0"
    "saveAs\0zoomIn\0zoomOut\0pinceau\0checked\0"
    "rectangleSelect\0chooseBrushColor\0"
    "chooseBrushSize\0chooseForm\0pixelGrid\0"
    "resizeImage\0resizeCanvas\0flipHorizontally\0"
    "flipVertically\0rotateRight\0rotateLeft\0"
    "rotateBehind"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x08 /* Private */,
       3,    0,  115,    2, 0x08 /* Private */,
       4,    0,  116,    2, 0x08 /* Private */,
       5,    0,  117,    2, 0x08 /* Private */,
       6,    0,  118,    2, 0x08 /* Private */,
       7,    0,  119,    2, 0x08 /* Private */,
       8,    0,  120,    2, 0x08 /* Private */,
       9,    1,  121,    2, 0x08 /* Private */,
      11,    1,  124,    2, 0x08 /* Private */,
      12,    0,  127,    2, 0x08 /* Private */,
      13,    0,  128,    2, 0x08 /* Private */,
      14,    0,  129,    2, 0x08 /* Private */,
      15,    1,  130,    2, 0x08 /* Private */,
      16,    0,  133,    2, 0x08 /* Private */,
      17,    0,  134,    2, 0x08 /* Private */,
      18,    0,  135,    2, 0x08 /* Private */,
      19,    0,  136,    2, 0x08 /* Private */,
      20,    0,  137,    2, 0x08 /* Private */,
      21,    0,  138,    2, 0x08 /* Private */,
      22,    0,  139,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->open(); break;
        case 2: _t->quit(); break;
        case 3: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->zoomIn(); break;
        case 6: _t->zoomOut(); break;
        case 7: _t->pinceau((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->rectangleSelect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->chooseBrushColor(); break;
        case 10: _t->chooseBrushSize(); break;
        case 11: _t->chooseForm(); break;
        case 12: _t->pixelGrid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->resizeImage(); break;
        case 14: _t->resizeCanvas(); break;
        case 15: _t->flipHorizontally(); break;
        case 16: _t->flipVertically(); break;
        case 17: _t->rotateRight(); break;
        case 18: _t->rotateLeft(); break;
        case 19: _t->rotateBehind(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
