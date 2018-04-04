#-------------------------------------------------
#
# Project created by QtCreator 2018-04-04T11:51:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../entities/graph/src/Graph.cpp \
    ../../entities/graph/src/Node.cpp \
    ../../entities/graph/src/Edge.cpp \
    ../../utils/src/utils.cpp \
    graphhelper.cpp

HEADERS  += mainwindow.h \
    gnode.h \
    ../../entities/animal/include/Animal.h \
    ../../entities/animal/include/NaturalLaw.h \
    ../../entities/graph/include/Graph.h \
    ../../entities/graph/include/Node.h \
    ../../entities/graph/include/Edge.h \
    ../../utils/include/utils.h \
    nodeguiattr.h \
    graphhelper.h

FORMS    += mainwindow.ui

DISTFILES += \
    image.jpg
