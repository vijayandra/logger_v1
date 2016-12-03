/****************************************************************************
** Meta object code from reading C++ file 'mem_rw.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mem_rw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mem_rw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MemRw_class[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      29,   12,   12,   12, 0x05,
      46,   40,   12,   12, 0x05,
      90,   12,   12,   12, 0x05,
     110,   12,   12,   12, 0x05,
     123,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     144,  138,  134,   12, 0x0a,
     179,   12,   12,   12, 0x0a,
     197,   12,   12,   12, 0x0a,
     209,   12,   12,   12, 0x0a,
     227,   12,  134,   12, 0x0a,
     262,   12,  134,   12, 0x0a,
     301,   12,  134,   12, 0x0a,
     333,  331,   12,   12, 0x0a,
     352,   12,   12,   12, 0x0a,
     364,   12,   12,   12, 0x0a,
     378,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MemRw_class[] = {
    "MemRw_class\0\0may_load_next()\0finished()\0"
    "b,len\0push_trigger(unsigned char*,unsigned short)\0"
    "kick_start_signal()\0comm_start()\0"
    "comm_end()\0int\0s,pkt\0"
    "route_msg(QString,scoap_packet_t&)\0"
    "kick_start_slot()\0load_next()\0"
    "heartbeat_pulse()\0address_sent_ackd(scoap_packet_t&)\0"
    "process_incomming_pkt(scoap_packet_t&)\0"
    "device_ready(scoap_packet_t&)\0,\0"
    "retrigger(int,int)\0to_device()\0"
    "from_device()\0slot_sendScriptC_Code(char*)\0"
};

void MemRw_class::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MemRw_class *_t = static_cast<MemRw_class *>(_o);
        switch (_id) {
        case 0: _t->may_load_next(); break;
        case 1: _t->finished(); break;
        case 2: _t->push_trigger((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned short(*)>(_a[2]))); break;
        case 3: _t->kick_start_signal(); break;
        case 4: _t->comm_start(); break;
        case 5: _t->comm_end(); break;
        case 6: { int _r = _t->route_msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< scoap_packet_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: _t->kick_start_slot(); break;
        case 8: _t->load_next(); break;
        case 9: _t->heartbeat_pulse(); break;
        case 10: { int _r = _t->address_sent_ackd((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->process_incomming_pkt((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: { int _r = _t->device_ready((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 13: _t->retrigger((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->to_device(); break;
        case 15: _t->from_device(); break;
        case 16: _t->slot_sendScriptC_Code((*reinterpret_cast< char*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MemRw_class::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MemRw_class::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MemRw_class,
      qt_meta_data_MemRw_class, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MemRw_class::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MemRw_class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MemRw_class::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MemRw_class))
        return static_cast<void*>(const_cast< MemRw_class*>(this));
    return QThread::qt_metacast(_clname);
}

int MemRw_class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MemRw_class::may_load_next()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MemRw_class::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MemRw_class::push_trigger(unsigned char * _t1, unsigned short _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MemRw_class::kick_start_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MemRw_class::comm_start()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MemRw_class::comm_end()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
