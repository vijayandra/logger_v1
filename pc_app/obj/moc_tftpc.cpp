/****************************************************************************
** Meta object code from reading C++ file 'tftpc.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tftpc.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tftpc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTFTPWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x0a,
      53,   48,   12,   12, 0x0a,
      73,   13,   12,   12, 0x0a,
     101,   48,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QTFTPWidget[] = {
    "QTFTPWidget\0\0address\0onSetLocalAddress(QString)\0"
    "port\0onSetLocalPort(int)\0"
    "onSetRemoteAddress(QString)\0"
    "onSetRemotePort(int)\0"
};

void QTFTPWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QTFTPWidget *_t = static_cast<QTFTPWidget *>(_o);
        switch (_id) {
        case 0: _t->onSetLocalAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onSetLocalPort((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onSetRemoteAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onSetRemotePort((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QTFTPWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QTFTPWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QTFTPWidget,
      qt_meta_data_QTFTPWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTFTPWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTFTPWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTFTPWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTFTPWidget))
        return static_cast<void*>(const_cast< QTFTPWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int QTFTPWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
