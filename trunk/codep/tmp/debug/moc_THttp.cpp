/****************************************************************************
** Meta object code from reading C++ file 'THttp.h'
**
** Created: Fri Apr 29 14:01:09 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client/THttp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'THttp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Http[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      36,    5,    5,    5, 0x0a,
      75,    5,    5,    5, 0x0a,
     116,   91,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Http[] = {
    "Http\0\0replyFinished(QNetworkReply*)\0"
    "slotError(QNetworkReply::NetworkError)\0"
    "handleTimeOut()\0bytesReceived,bytesTotal\0"
    "downloadProgress(qint64,qint64)\0"
};

const QMetaObject Http::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Http,
      qt_meta_data_Http, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Http::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Http::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Http::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Http))
        return static_cast<void*>(const_cast< Http*>(this));
    return QObject::qt_metacast(_clname);
}

int Http::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: slotError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 2: handleTimeOut(); break;
        case 3: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
