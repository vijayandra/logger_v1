#ifndef __R_ADC_H
#define __R_ADC_H

#include "options.h"
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTime>
#include <QTimer>
#include <QUrl>
#include "textprogressbar.h"

#ifdef ZSERIAL
#include "serial_cs.h"
#else
#include "lrn_io.h"
#endif
#include "shared_struct.h"


class ADC_class: public QThread
{
    Q_OBJECT
public:
    explicit ADC_class(QObject *parent);
    ~ADC_class();
    io_ADC_DAC_Exchng gluData;
signals:

public slots:

    int  route_msg(QString s,scoap_packet_t &pkt);
    int  process_incomming_pkt(scoap_packet_t &);
private:
    unsigned char *m_Ptr;

};

#endif
