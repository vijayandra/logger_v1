/****************************************************************************
** Meta object code from reading C++ file 'scratch_pad.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scratch_pad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scratch_pad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ScratchPad[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   11,   11,   11, 0x0a,
      50,   48,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ScratchPad[] = {
    "ScratchPad\0\0code_edit_text_changed()\0"
    "saveFile()\0s\0process_slot(ioTxtGrpthExchStrct&)\0"
};

void ScratchPad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScratchPad *_t = static_cast<ScratchPad *>(_o);
        switch (_id) {
        case 0: _t->code_edit_text_changed(); break;
        case 1: _t->saveFile(); break;
        case 2: _t->process_slot((*reinterpret_cast< ioTxtGrpthExchStrct(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ScratchPad::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ScratchPad::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_ScratchPad,
      qt_meta_data_ScratchPad, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ScratchPad::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ScratchPad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ScratchPad::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ScratchPad))
        return static_cast<void*>(const_cast< ScratchPad*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int ScratchPad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ScratchPad::code_edit_text_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
