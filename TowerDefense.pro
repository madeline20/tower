#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
    audioplayer.cpp \
    boss.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    g1.cpp \
    mw1.cpp \
    mybutton.cpp \
    mywindow.cpp \
    slowingtower.cpp

HEADERS  += \
    audioplayer.h \
    boss.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    towerposition.h \
    g1.h \
    mw1.h \
    mybutton.h \
    mywindow.h \
    slowingtower.h

FORMS    +=

RESOURCES += \
    resource.qrc
