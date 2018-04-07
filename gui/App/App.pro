#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T23:10:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    graphhelper.cpp \
    ../../entities/graph/src/Edge.cpp \
    ../../entities/graph/src/Graph.cpp \
    ../../entities/graph/src/Node.cpp \
    ../../utils/src/utils.cpp \
    editnodedialog.cpp \
    editedgedialog.cpp

HEADERS  += mainwindow.h \
    gnode.h \
    graphhelper.h \
    nodeguiattr.h \
    ../../entities/data/include/EdgeAttr.h \
    ../../entities/data/include/NodeAttr.h \
    ../../entities/graph/include/Edge.h \
    ../../entities/graph/include/Graph.h \
    ../../entities/graph/include/Node.h \
    ../../utils/include/utils.h \
    editnodedialog.h \
    editedgedialog.h

FORMS    += mainwindow.ui

DISTFILES += \
    App.pro.user
