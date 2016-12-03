/****************************************************************************
** Meta object code from reading C++ file 'iwextern.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../iwextern.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iwextern.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IWExtern[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,    9,    9,    9, 0x0a,
      39,    9,    9,    9, 0x0a,
      55,    9,    9,    9, 0x0a,
      71,    9,    9,    9, 0x0a,
      82,    9,    9,    9, 0x0a,
      94,    9,    9,    9, 0x0a,
     115,  113,    9,    9, 0x0a,
     135,    9,    9,    9, 0x0a,
     151,    9,    9,    9, 0x0a,
     160,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IWExtern[] = {
    "IWExtern\0\0banner_msg()\0Ex1_Procedure()\0"
    "Ex2_Procedure()\0Ex3_Procedure()\0"
    "BootMode()\0SoftReset()\0Banner_Action(int)\0"
    ",\0LED_Action(int,int)\0Winlog_Action()\0"
    "UserIn()\0banner_msg_rcvd()\0"
};

void IWExtern::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IWExtern *_t = static_cast<IWExtern *>(_o);
        switch (_id) {
        case 0: _t->banner_msg(); break;
        case 1: _t->Ex1_Procedure(); break;
        case 2: _t->Ex2_Procedure(); break;
        case 3: _t->Ex3_Procedure(); break;
        case 4: _t->BootMode(); break;
        case 5: _t->SoftReset(); break;
        case 6: _t->Banner_Action((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->LED_Action((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->Winlog_Action(); break;
        case 9: _t->UserIn(); break;
        case 10: _t->banner_msg_rcvd(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IWExtern::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IWExtern::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_IWExtern,
      qt_meta_data_IWExtern, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IWExtern::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IWExtern::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IWExtern::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IWExtern))
        return static_cast<void*>(const_cast< IWExtern*>(this));
    return QWidget::qt_metacast(_clname);
}

int IWExtern::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void IWExtern::banner_msg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
