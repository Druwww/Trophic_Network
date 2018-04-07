#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T23:10:21
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../entities/graph/src/Edge.cpp \
    ../../entities/graph/src/Graph.cpp \
    ../../entities/graph/src/Node.cpp \
    ../../utils/src/utils.cpp \
    editnodedialog.cpp \
    editedgedialog.cpp \
    ../../algorithm/src/algorithm.cpp \
    ../../simulation/src/Simulation.cpp

HEADERS  += mainwindow.h \
    gnode.h \
    nodeguiattr.h \
    ../../entities/data/include/EdgeAttr.h \
    ../../entities/data/include/NodeAttr.h \
    ../../entities/graph/include/Edge.h \
    ../../entities/graph/include/Graph.h \
    ../../entities/graph/include/Node.h \
    ../../utils/include/utils.h \
    editnodedialog.h \
    editedgedialog.h \
    ../../algorithm/include/algorithm.h \
    ../../simulation/include/Simulation.h

FORMS    += mainwindow.ui

DISTFILES += \
    App.pro.user
