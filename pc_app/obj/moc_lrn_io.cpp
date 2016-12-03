/****************************************************************************
** Meta object code from reading C++ file 'lrn_io.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../lrn_io.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lrn_io.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ParTask[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ParTask[] = {
    "ParTask\0\0workFinished()\0"
};

void ParTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ParTask *_t = static_cast<ParTask *>(_o);
        switch (_id) {
        case 0: _t->workFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ParTask::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ParTask::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ParTask,
      qt_meta_data_ParTask, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ParTask::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ParTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ParTask::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ParTask))
        return static_cast<void*>(const_cast< ParTask*>(this));
    return QObject::qt_metacast(_clname);
}

int ParTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ParTask::workFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_LRN_io[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      23,    7,    7,    7, 0x05,
      53,   51,    7,    7, 0x05,
      67,    7,    7,    7, 0x05,
      99,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     136,    7,    7,    7, 0x0a,
     151,    7,    7,    7, 0x0a,
     172,    7,    7,    7, 0x0a,
     198,    7,    7,    7, 0x0a,
     212,   51,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LRN_io[] = {
    "LRN_io\0\0hwPokeSignal()\0"
    "hwPokeSignalWithIP(QString)\0,\0"
    "zack(int,int)\0got_valid_coap(scoap_packet_t&)\0"
    "SIG_GUI_UPDATE(ioTxtGrpthExchStrct&)\0"
    "hwPokeAction()\0ClintWriteResponse()\0"
    "ServerHandlingIncomming()\0ztimer_slot()\0"
    "zack_ack_slot(int,int)\0"
};

void LRN_io::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LRN_io *_t = static_cast<LRN_io *>(_o);
        switch (_id) {
        case 0: _t->hwPokeSignal(); break;
        case 1: _t->hwPokeSignalWithIP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->zack((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->got_valid_coap((*reinterpret_cast< scoap_packet_t(*)>(_a[1]))); break;
        case 4: _t->SIG_GUI_UPDATE((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 5: _t->hwPokeAction(); break;
        case 6: _t->ClintWriteResponse(); break;
        case 7: _t->ServerHandlingIncomming(); break;
        case 8: _t->ztimer_slot(); break;
        case 9: _t->zack_ack_slot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LRN_io::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LRN_io::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_LRN_io,
      qt_meta_data_LRN_io, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LRN_io::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LRN_io::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LRN_io::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LRN_io))
        return static_cast<void*>(const_cast< LRN_io*>(this));
    return QThread::qt_metacast(_clname);
}

int LRN_io::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void LRN_io::hwPokeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LRN_io::hwPokeSignalWithIP(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LRN_io::zack(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LRN_io::got_valid_coap(scoap_packet_t & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LRN_io::SIG_GUI_UPDATE(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
