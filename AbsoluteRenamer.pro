#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T20:58:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AbsoluteRenamer
TEMPLATE = app
RC_FILE = icon.rc


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    icon.rc \
    .gitattributes \
    .gitignore \
    LICENSE \
    README.md

RESOURCES += \
    resources.qrc
