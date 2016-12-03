/****************************************************************************
** Meta object code from reading C++ file 'scratch_pp.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scratch_pp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scratch_pp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SCRATCH_pp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      47,   11,   11,   11, 0x05,
      82,   11,   11,   11, 0x05,
     117,   11,   11,   11, 0x05,
     149,   11,   11,   11, 0x05,
     181,   11,   11,   11, 0x05,
     213,   11,   11,   11, 0x05,
     246,   11,   11,   11, 0x05,
     272,  266,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     316,   11,   11,   11, 0x0a,
     341,  338,  334,   11, 0x0a,
     376,   11,  334,   11, 0x0a,
     415,   11,  334,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SCRATCH_pp[] = {
    "SCRATCH_pp\0\0SIG_SCRATCH1(ioTxtGrpthExchStrct&)\0"
    "SIG_SCRATCH2(ioTxtGrpthExchStrct&)\0"
    "SIG_SCRATCH3(ioTxtGrpthExchStrct&)\0"
    "SIG_RS485(ioTxtGrpthExchStrct&)\0"
    "SIG_UART2(ioTxtGrpthExchStrct&)\0"
    "SIG_UART3(ioTxtGrpthExchStrct&)\0"
    "SIG_UART23(ioTxtGrpthExchStrct&)\0"
    "kick_start_signal()\0b,len\0"
    "push_trigger(unsigned char*,unsigned short)\0"
    "heartbeat_pulse()\0int\0s,\0"
    "route_msg(QString,scoap_packet_t&)\0"
    "process_incomming_pkt(scoap_packet_t&)\0"
    "device_ready(scoap_packet_t&)\0"
};

void SCRATCH_pp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SCRATCH_pp *_t = static_cast<SCRATCH_pp *>(_o);
        switch (_id) {
        case 0: _t->SIG_SCRATCH1((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 1: _t->SIG_SCRATCH2((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 2: _t->SIG_SCRATCH3((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 3: _t->SIG_RS485((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 4: _t->SIG_UART2((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 5: _t->SIG_UART3((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 6: _t->SIG_UART23((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 7: _t->kick_start_signal(); break;
        case 8: _t->push_trigger((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned short(*)>(_a[2]))); break;
        case 9: _t->heartbeat_pulse(); break;
        case 10: { int _r = _t->route_msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< scoap_packet_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->process_incomming_pkt((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->device_ready((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SCRATCH_pp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SCRATCH_pp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SCRATCH_pp,
      qt_meta_data_SCRATCH_pp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SCRATCH_pp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SCRATCH_pp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SCRATCH_pp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SCRATCH_pp))
        return static_cast<void*>(const_cast< SCRATCH_pp*>(this));
    return QObject::qt_metacast(_clname);
}

int SCRATCH_pp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SCRATCH_pp::SIG_SCRATCH1(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SCRATCH_pp::SIG_SCRATCH2(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SCRATCH_pp::SIG_SCRATCH3(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SCRATCH_pp::SIG_RS485(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SCRATCH_pp::SIG_UART2(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SCRATCH_pp::SIG_UART3(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SCRATCH_pp::SIG_UART23(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SCRATCH_pp::kick_start_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void SCRATCH_pp::push_trigger(unsigned char * _t1, unsigned short _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
