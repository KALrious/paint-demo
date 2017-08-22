#-------------------------------------------------
#
# Project created by QtCreator 2015-09-25T23:48:24
#
#-------------------------------------------------

QT       += core gui
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mylittlepaint
TEMPLATE = app


SOURCES += main.cpp\
        mylittlepaint.cpp \
    canvas.cpp

HEADERS  += mylittlepaint.h \
    canvas.h

FORMS    += mylittlepaint.ui

RESOURCES += \
    ressources.qrc
