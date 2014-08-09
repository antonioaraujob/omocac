#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T08:19:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = omocac
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    individual.cpp \
    normativephenotypicpart.cpp \
    normativegrid.cpp \
    externalfile.cpp \
    simulation.cpp \
    gridsubinterval.cpp

HEADERS  += mainwindow.h \
    individual.h \
    normativephenotypicpart.h \
    normativegrid.h \
    externalfile.h \
    simulation.h \
    gridsubinterval.h

FORMS    += mainwindow.ui
