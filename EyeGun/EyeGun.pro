#-------------------------------------------------
#
# Project created by QtCreator 2015-09-24T23:36:38
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = EyeGun
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    motor.cpp \
    laser.cpp \
    eyegun.cpp \
    eyeguncalibrator.cpp \
    trigger.cpp

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_calib3d -lwiringPi
INCLUDEPATH += /usr/local/include

HEADERS += \
    motor.h \
    laser.h \
    eyegun.h \
    eyeguncalibrator.hpp \
    trigger.h
