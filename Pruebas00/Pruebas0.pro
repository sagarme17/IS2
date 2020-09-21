QT += testlib
QT += core gui sql

CONFIG += qt console warn_on depend_includepath testcase


TEMPLATE = app

SOURCES +=  tst_pruebas0.cpp \
    basededatos.cpp

HEADERS += \
    basededatos.h
