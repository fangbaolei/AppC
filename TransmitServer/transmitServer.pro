TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    threadpool.c \
    linklist.c \
    fwserver.c

HEADERS += \
    threadpool.h \
    linklist.h \
    fwserver.h

LIBS += -lpthread



