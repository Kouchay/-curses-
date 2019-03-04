TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L/usr/local/lib/ -lcurl \
        -L/lib32 -lncursesw

SOURCES += main.c \
    cJSON.c \
    drawui.c \
    asciiarttable.c \
    curlapi.c

HEADERS += \
    cJSON.h \
    asciiarttable.h \
    drawui.h \
    curlapi.h
