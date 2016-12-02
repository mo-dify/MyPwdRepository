#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T16:31:44
#
#-------------------------------------------------

QT       += core gui

RC_ICONS +=mypwd.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPwdRepository
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    sqlite3/sqlite_fun.c \
    sqlite3/sqlite3.c \
    pwd.cpp

HEADERS  += widget.h \
    sqlite3/sqlite_fun.h \
    sqlite3/sqlite3.h \
    pwd.h

FORMS    += widget.ui \
    pwd.ui

DISTFILES += \
    mypwd.ico \
    myapp.rc

