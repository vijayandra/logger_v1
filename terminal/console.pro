TEMPLATE = app
QT      += network opengl
CONFIG  += console

QMAKE_CXXFLAGS += -std=gnu++0x
QMAKE_CXXFLAGS += -U__STRICT_ANSI__
QMAKE_CFLAGS += -std=c99 -g -Wall -pedantic -Dlinux

DESTDIR      = bin
MOC_DIR      = obj
RCC_DIR      = obj
OBJECTS_DIR  = obj


DEFINES      += COMMAND_LINE_USE
FILE_PATH     = ../heartbeat


unix {
DEFINES      += LINUX_WAY
#INCLUDEPATH  += ../common
}
INCLUDEPATH  += .

win32 {
DEFINES += WINDOWS_WAY
INCLUDEPATH += c:/sw/opencv/include
INCLUDEPATH += c:/sw/opencv/include/opencv
INCLUDEPATH += c:/sw/opencv/include/opencv2
#INCLUDEPATH  += ../common
}


unix {
    DEFINES += LINUX_WAY
    #DEFINES += FORCE_STATIC_LIB
    INCLUDEPATH += /usr/include
    INCLUDEPATH += /usr/include/qt4/wwWidgets
    INCLUDEPATH += /usr/include/opencv
    INCLUDEPATH += /usr/include/opencv2
    LIBS += -lgsl
    LIBS += -lgslcblas
}

win32 {
    DEFINES += WINDOWS_WAY
}

TEMPLATE      = app
CONFIG       += wwwidgets
CONFIG       += release
QMAKE_CXXFLAGS_RELEASE -= -O2


win32 {
LIBS += -L../fixed_lib/bin -lfixed_lib
#LIBS         += iw_rtv001.dll
#LIBS         += iw_par.dll
#LIBS += -L../wlib/bin -lwlib
}

unix {
LIBS += -L../fixed_lib/bin -lfixed_lib -lrt
#LIBS += -lgsl
#LIBS += -lgslcblas
unix: !macx: LIBS += -lusb-1.0
}

DEFINES += DEBUG
TARGET   = epc

INCLUDEPATH += libc
INCLUDEPATH += ../../common
INCLUDEPATH += ../fixed_lib
INCLUDEPATH += ../../ext_common
INCLUDEPATH += ../fixed_lib/smtp
INCLUDEPATH += $${FILE_PATH}


PRE_TARGETDEPS       = ../fixed_lib/bin/lib_fixed.so
Fixed_Lib.target     = ../fixed_lib/bin/lib_fixed.so
Fixed_Lib.commands   = cd ../fixed_lib && Qmake
Fixed_Lib.depends    = ../fixed_lib/lib_fixed.pro
QMAKE_EXTRA_TARGETS += Fixed_Lib

unix {
LIBS += -L/usr/local/lib -lgsl -lgslcblas
}

SOURCES += main.cpp
SOURCES += console.cpp
HEADERS += console.h

SOURCES += $${FILE_PATH}/enc_coap.c

SOURCES += $${FILE_PATH}/lrn_io.cpp
HEADERS += $${FILE_PATH}/lrn_io.h

#SOURCES += $${FILE_PATH}/serial_cs.cpp
#HEADERS += $${FILE_PATH}/serial_cs.h

SOURCES += $${FILE_PATH}/global_var.c
HEADERS += $${FILE_PATH}/global_var.h

#SOURCES += testbeat.cpp
#HEADERS += testbeat.h

HEADERS += $${FILE_PATH}/textprogressbar.h
SOURCES += $${FILE_PATH}/textprogressbar.cpp

SOURCES += $${FILE_PATH}/zcprotocol.cpp
HEADERS += $${FILE_PATH}/zcprotocol.h

SOURCES += $${FILE_PATH}/mem_rw.cpp
HEADERS += $${FILE_PATH}/mem_rw.h

SOURCES += file_nw.cpp
HEADERS += file_nw.h

SOURCES += $${FILE_PATH}/rtc_pp.cpp
HEADERS += $${FILE_PATH}/rtc_pp.h

SOURCES += $${FILE_PATH}/sensor_pp.cpp
HEADERS += $${FILE_PATH}/sensor_pp.h

SOURCES += $${FILE_PATH}/disc.cpp
HEADERS += $${FILE_PATH}/disc.h

INCLUDEPATH += ../../light_coap/protocol
INCLUDEPATH += ../../light_coap/endpoints

SOURCES += ../../light_coap/protocol/coap13.c
SOURCES += ../../light_coap/protocol/coapbuilder.c
SOURCES += ../../light_coap/protocol/llist.c
SOURCES += ../../light_coap/protocol/str.c
SOURCES += ../../light_coap/protocol/uri.c
SOURCES += ../../light_coap/protocol/srv_coap.c
SOURCES += ../../light_coap/endpoints/endpoints.c
SOURCES += ../../light_coap/endpoints/ep_device.c

