QT -= app
QT += serialbus core
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        ecu.cpp \
        ecucan/canbus.cpp \
        ecucan/ecubase.cpp \
        ecumodel.cpp \
        main.cpp \
        shared_memory.cpp

HEADERS += \
    ecu.h \
    ecucan/canbus.h \
    ecucan/ecubase.h \
    ecumodel.h \
    shared_memory.h
