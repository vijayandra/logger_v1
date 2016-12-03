FORMS         = extern_inf.ui

HEADERS       = coap_pdu.h
HEADERS      += heartbeat.h
HEADERS      += tftpc.h

SOURCES      += main.cpp
SOURCES      += coap_pdu.cpp
SOURCES      += heartbeat.cpp
SOURCES      += tftpc.cpp

HEADERS += textprogressbar.h
SOURCES += textprogressbar.cpp

SOURCES += enc_coap.c
SOURCES      += lrn_io.cpp
HEADERS      += lrn_io.h

SOURCES +=  disc.cpp
HEADERS +=  disc.h

SOURCES +=  adc.cpp
HEADERS +=  adc.h

SOURCES += zcprotocol.cpp
HEADERS += zcprotocol.h

SOURCES += mem_rw.cpp
HEADERS += mem_rw.h

SOURCES += file_rw.cpp
HEADERS += file_rw.h

SOURCES += rtc_pp.cpp
HEADERS += rtc_pp.h

SOURCES += sensor_pp.cpp
HEADERS += sensor_pp.h

SOURCES += scratch_pp.cpp
HEADERS += scratch_pp.h

SOURCES += global_var.c
HEADERS += global_var.h

#SOURCES += io_uart.c
#HEADERS += io_uart.h

SOURCES += codeeditor.cpp
HEADERS += codeeditor.h

SOURCES += scratch_pad.cpp
HEADERS += scratch_pad.h

SOURCES += highlighter.cpp
HEADERS += highlighter.h

SOURCES += iwextern.cpp
HEADERS += iwextern.h

#RP= ../../../scratch1
RP= ..

INCLUDEPATH += $${RP}/ext_common
INCLUDEPATH += $${RP}/light_coap/protocol
INCLUDEPATH += $${RP}/light_coap/endpoints

SOURCES += $${RP}/light_coap/protocol/coap13.c
SOURCES += $${RP}/light_coap/protocol/coapbuilder.c
SOURCES += $${RP}/light_coap/protocol/llist.c
SOURCES += $${RP}/light_coap/protocol/str.c
SOURCES += $${RP}/light_coap/protocol/uri.c
SOURCES += $${RP}/light_coap/protocol/srv_coap.c
SOURCES += $${RP}/light_coap/endpoints/endpoints.c
SOURCES += $${RP}/light_coap/endpoints/ep_device.c


RC_FILE       = iwscope.rc
RESOURCES     = communicator.qrc
#SOURCES += images

DESTDIR      = bin
MOC_DIR      = obj
RCC_DIR      = obj
OBJECTS_DIR  = obj



QT       += core gui widgets network

# install
target.path = $$[QT_INSTALL_EXAMPLES]/dialogs/standarddialogs
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/dialogs/standarddialogs
INSTALLS += target sources

CONFIG       += wwwidgets

unix {
    DEFINES += LINUX_WAY
    #DEFINES += FORCE_STATIC_LIB
    QWT_LOCATION = /usr/local/qwt-6.0.2
    INCLUDEPATH += $${QWT_LOCATION}/include
    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/include/qt4/wwWidgets
    LIBS += -L$${QWT_LOCATION}/lib -lqwt
    LIBS += -L$${QWT_LOCATION}/lib -lqwt
    LIBS += -lgsl
    LIBS += -lgslcblas
}

win32 {
DEFINES += WINDOWS_WAY
QWT_LOCATION = C:/Qt/2010.05/qwt-6.0.2
INCLUDEPATH += $${QWT_LOCATION}/src
LIBS += -L$${QWT_LOCATION}/lib -lqwt
}


INCLUDEPATH  += ../ext_common


LIBS         += -lm
LIBS         += -L../fixed_lib/bin -lfixed_lib

win {
unix {
SOURCES += qt_tftp/inetaddr.cpp
SOURCES += qt_tftp/inetsockaddr.cpp
SOURCES += qt_tftp/listener.cpp
SOURCES += qt_tftp/senderworker.cpp
SOURCES += qt_tftp/sockaddr.cpp
SOURCES += qt_tftp/socket.cpp
SOURCES += qt_tftp/socketmonitor.cpp
SOURCES += qt_tftp/socketudp.cpp
SOURCES += qt_tftp/tftpapp.cpp
SOURCES += qt_tftp/tftpclient.cpp
SOURCES += qt_tftp/tftpcommon.cpp
SOURCES += qt_tftp/tftpserver.cpp
SOURCES += qt_tftp/writerworker.cpp

HEADERS += qt_tftp/inetaddr.h
HEADERS += qt_tftp/inetsockaddr.h
HEADERS += qt_tftp/listener.h
HEADERS += qt_tftp/senderworker.h
HEADERS += qt_tftp/sockaddr.h
HEADERS += qt_tftp/socket.h
HEADERS += qt_tftp/socketmonitor.h
HEADERS += qt_tftp/socketudp.h
HEADERS += qt_tftp/tftpapp.h
HEADERS += qt_tftp/tftpclient.h
HEADERS += qt_tftp/tftpcommon.h
HEADERS += qt_tftp/tftpserver.h
HEADERS += qt_tftp/writerworker.h
}
}

TARGET   = heartbeat

CONFIG       += wwwidgets

unix {
QWT_LOCATION = /usr/local/qwt-6.0.2
DEFINES      += LINUX_WAY
INCLUDEPATH  += $${QWT_LOCATION}/include
LIBS += -L$${QWT_LOCATION}/lib -lqwt
}

win32 {
DEFINES += WINDOWS_WAY
QWT_LOCATION = C:/Qt/2010.05/qwt-6.0.2
INCLUDEPATH += $${QWT_LOCATION}/src
LIBS += -L$${QWT_LOCATION}/lib -lqwt
}


