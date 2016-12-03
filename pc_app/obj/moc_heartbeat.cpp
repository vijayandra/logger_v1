/****************************************************************************
** Meta object code from reading C++ file 'heartbeat.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../heartbeat.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'heartbeat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HeartBeat[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      26,   10,   10,   10, 0x05,
      38,   10,   10,   10, 0x05,
      50,   10,   10,   10, 0x05,
      63,   10,   10,   10, 0x05,
      74,   10,   10,   10, 0x05,
     109,   10,   10,   10, 0x05,
     144,   10,   10,   10, 0x05,
     179,   10,   10,   10, 0x05,
     211,   10,   10,   10, 0x05,
     243,   10,   10,   10, 0x05,
     275,   10,   10,   10, 0x05,
     314,  308,   10,   10, 0x05,
     365,  358,   10,   10, 0x05,
     387,  358,   10,   10, 0x05,
     409,   10,   10,   10, 0x05,
     435,   10,   10,   10, 0x05,
     452,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     462,   10,   10,   10, 0x08,
     495,   10,   10,   10, 0x08,
     510,   10,   10,   10, 0x08,
     538,   10,   10,   10, 0x08,
     554,   10,   10,   10, 0x08,
     572,   10,   10,   10, 0x08,
     593,   10,   10,   10, 0x08,
     623,   10,   10,   10, 0x08,
     656,   10,   10,   10, 0x08,
     689,  681,   10,   10, 0x08,
     732,  730,   10,   10, 0x08,
     760,  730,   10,   10, 0x08,
     793,  730,   10,   10, 0x08,
     827,   10,   10,   10, 0x08,
     854,   10,   10,   10, 0x08,
     872,   10,   10,   10, 0x08,
     892,   10,   10,   10, 0x08,
     906,   10,   10,   10, 0x0a,
     935,  933,   10,   10, 0x0a,
     966,   10,   10,   10, 0x0a,
     984,   10,   10,   10, 0x0a,
     994,   10,   10,   10, 0x0a,
    1015,   10,   10,   10, 0x0a,
    1028,   10,   10,   10, 0x0a,
    1039,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HeartBeat[] = {
    "HeartBeat\0\0responseRcvd()\0uart1_Get()\0"
    "uart1_Put()\0msg_Pumped()\0finished()\0"
    "SIG_SCRATCH1(ioTxtGrpthExchStrct&)\0"
    "SIG_SCRATCH2(ioTxtGrpthExchStrct&)\0"
    "SIG_SCRATCH3(ioTxtGrpthExchStrct&)\0"
    "SIG_RS485(ioTxtGrpthExchStrct&)\0"
    "SIG_UART2(ioTxtGrpthExchStrct&)\0"
    "SIG_UART3(ioTxtGrpthExchStrct&)\0"
    "SIG_UART23(ioTxtGrpthExchStrct&)\0b,len\0"
    "push_trigger(unsigned char*,unsigned short)\0"
    "string\0sig_pullFile(QString)\0"
    "sig_pushFile(QString)\0sig_script_load_and_run()\0"
    "sig_script_run()\0do_plot()\0"
    "GUI_UPDATE(ioTxtGrpthExchStrct&)\0"
    "timerExpired()\0delayRAMCodeTimerrExpired()\0"
    "newScriptSlot()\0PushRTCTimeSlot()\0"
    "autoExecScriptSlot()\0slotEditAutoExecScriptC(bool)\0"
    "FoundDataLoggerHWString(QString)\0"
    "HeartBeatTimerSyncSlot()\0cbf,len\0"
    "post_coap(unsigned char*,unsigned short)\0"
    "x\0slot_Edit_OR_PUSH_INI(bool)\0"
    "slot_Edit_OR_PUSH_C_Script(bool)\0"
    "slot_Run_Script_In_Hardware(bool)\0"
    "slot_script_load_and_run()\0slot_script_run()\0"
    "slot_FormatSDCard()\0slot_Reboot()\0"
    "route_pkt(scoap_packet_t&)\0,\0"
    "update_progress(qint64,qint64)\0"
    "browse_and_send()\0getFile()\0"
    "update_code_buffer()\0comm_start()\0"
    "comm_end()\0msg_PumpedRcvd()\0"
};

void HeartBeat::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HeartBeat *_t = static_cast<HeartBeat *>(_o);
        switch (_id) {
        case 0: _t->responseRcvd(); break;
        case 1: _t->uart1_Get(); break;
        case 2: _t->uart1_Put(); break;
        case 3: _t->msg_Pumped(); break;
        case 4: _t->finished(); break;
        case 5: _t->SIG_SCRATCH1((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 6: _t->SIG_SCRATCH2((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 7: _t->SIG_SCRATCH3((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 8: _t->SIG_RS485((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 9: _t->SIG_UART2((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 10: _t->SIG_UART3((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 11: _t->SIG_UART23((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 12: _t->push_trigger((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned short(*)>(_a[2]))); break;
        case 13: _t->sig_pullFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->sig_pushFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: _t->sig_script_load_and_run(); break;
        case 16: _t->sig_script_run(); break;
        case 17: _t->do_plot(); break;
        case 18: _t->GUI_UPDATE((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        case 19: _t->timerExpired(); break;
        case 20: _t->delayRAMCodeTimerrExpired(); break;
        case 21: _t->newScriptSlot(); break;
        case 22: _t->PushRTCTimeSlot(); break;
        case 23: _t->autoExecScriptSlot(); break;
        case 24: _t->slotEditAutoExecScriptC((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->FoundDataLoggerHWString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 26: _t->HeartBeatTimerSyncSlot(); break;
        case 27: _t->post_coap((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< unsigned short(*)>(_a[2]))); break;
        case 28: _t->slot_Edit_OR_PUSH_INI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->slot_Edit_OR_PUSH_C_Script((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->slot_Run_Script_In_Hardware((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->slot_script_load_and_run(); break;
        case 32: _t->slot_script_run(); break;
        case 33: _t->slot_FormatSDCard(); break;
        case 34: _t->slot_Reboot(); break;
        case 35: _t->route_pkt((*reinterpret_cast< scoap_packet_t(*)>(_a[1]))); break;
        case 36: _t->update_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 37: _t->browse_and_send(); break;
        case 38: _t->getFile(); break;
        case 39: _t->update_code_buffer(); break;
        case 40: _t->comm_start(); break;
        case 41: _t->comm_end(); break;
        case 42: _t->msg_PumpedRcvd(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HeartBeat::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HeartBeat::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_HeartBeat,
      qt_meta_data_HeartBeat, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HeartBeat::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HeartBeat::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HeartBeat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeartBeat))
        return static_cast<void*>(const_cast< HeartBeat*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int HeartBeat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void HeartBeat::responseRcvd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void HeartBeat::uart1_Get()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HeartBeat::uart1_Put()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HeartBeat::msg_Pumped()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HeartBeat::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HeartBeat::SIG_SCRATCH1(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void HeartBeat::SIG_SCRATCH2(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void HeartBeat::SIG_SCRATCH3(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void HeartBeat::SIG_RS485(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void HeartBeat::SIG_UART2(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void HeartBeat::SIG_UART3(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void HeartBeat::SIG_UART23(ioTxtGrpthExchStrct & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void HeartBeat::push_trigger(unsigned char * _t1, unsigned short _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void HeartBeat::sig_pullFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void HeartBeat::sig_pushFile(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void HeartBeat::sig_script_load_and_run()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void HeartBeat::sig_script_run()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}

// SIGNAL 17
void HeartBeat::do_plot()
{
    QMetaObject::activate(this, &staticMetaObject, 17, 0);
}
QT_END_MOC_NAMESPACE
