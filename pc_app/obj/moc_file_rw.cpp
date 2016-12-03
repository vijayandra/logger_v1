/****************************************************************************
** Meta object code from reading C++ file 'file_rw.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../file_rw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'file_rw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FileRw_class[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      30,   13,   13,   13, 0x05,
      47,   41,   13,   13, 0x05,
      91,   13,   13,   13, 0x05,
     111,   13,   13,   13, 0x05,
     134,   13,   13,   13, 0x05,
     149,   13,   13,   13, 0x05,
     164,   13,   13,   13, 0x05,
     182,  180,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     204,   13,   13,   13, 0x0a,
     228,  180,   13,   13, 0x0a,
     251,   13,   13,   13, 0x0a,
     267,   13,   13,   13, 0x0a,
     283,   13,   13,   13, 0x0a,
     301,   13,   13,   13, 0x0a,
     313,   13,   13,   13, 0x0a,
     338,  335,  331,   13, 0x0a,
     373,   13,  331,   13, 0x0a,
     408,   13,  331,   13, 0x0a,
     447,   13,  331,   13, 0x0a,
     477,  180,   13,   13, 0x0a,
     505,  496,   13,   13, 0x0a,
     523,  496,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FileRw_class[] = {
    "FileRw_class\0\0may_load_next()\0finished()\0"
    "b,len\0push_trigger(unsigned char*,unsigned short)\0"
    "kick_start_signal()\0signal_curr_state(int)\0"
    "file_open_ok()\0file_read_ok()\0"
    "file_write_ok()\0,\0state_update(int,int)\0"
    "process_curr_state(int)\0analyze_state(int,int)\0"
    "next_pkt_send()\0next_pkt_save()\0"
    "kick_start_slot()\0load_next()\0"
    "heartbeat_pulse()\0int\0s,\0"
    "route_msg(QString,scoap_packet_t&)\0"
    "address_sent_ackd(scoap_packet_t&)\0"
    "process_incomming_pkt(scoap_packet_t&)\0"
    "device_ready(scoap_packet_t&)\0"
    "retrigger(int,int)\0fileName\0"
    "pullFile(QString)\0pushFile(QString)\0"
};

void FileRw_class::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileRw_class *_t = static_cast<FileRw_class *>(_o);
        switch (_id) {
        case 0: _t->may_load_next(); break;
        case 1: _t->finished(); break;
        case 2: _t->push_trigger((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned short(*)>(_a[2]))); break;
        case 3: _t->kick_start_signal(); break;
        case 4: _t->signal_curr_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->file_open_ok(); break;
        case 6: _t->file_read_ok(); break;
        case 7: _t->file_write_ok(); break;
        case 8: _t->state_update((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->process_curr_state((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->analyze_state((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->next_pkt_send(); break;
        case 12: _t->next_pkt_save(); break;
        case 13: _t->kick_start_slot(); break;
        case 14: _t->load_next(); break;
        case 15: _t->heartbeat_pulse(); break;
        case 16: { int _r = _t->route_msg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< scoap_packet_t(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->address_sent_ackd((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { int _r = _t->process_incomming_pkt((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 19: { int _r = _t->device_ready((*reinterpret_cast< scoap_packet_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: _t->retrigger((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 21: _t->pullFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 22: _t->pushFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FileRw_class::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FileRw_class::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_FileRw_class,
      qt_meta_data_FileRw_class, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FileRw_class::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FileRw_class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FileRw_class::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FileRw_class))
        return static_cast<void*>(const_cast< FileRw_class*>(this));
    return QThread::qt_metacast(_clname);
}

int FileRw_class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void FileRw_class::may_load_next()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void FileRw_class::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void FileRw_class::push_trigger(unsigned char * _t1, unsigned short _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FileRw_class::kick_start_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void FileRw_class::signal_curr_state(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FileRw_class::file_open_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void FileRw_class::file_read_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void FileRw_class::file_write_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void FileRw_class::state_update(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
