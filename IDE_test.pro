#-------------------------------------------------
#
# Project created by QtCreator 2022-08-19T18:28:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IDE_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    findwindow.cpp \
    highlight.cpp \
    dialog_new.cpp \
    file_textedit.cpp \
    newbuildfile.cpp \
    newbuildfolder.cpp \
    treemenu.cpp \
    changestyle.cpp \
    textedit.cpp

HEADERS += \
        mainwindow.h \
    findwindow.h \
    highlight.h \
    dialog_new.h \
    file_textedit.h \
    newbuildfile.h \
    newbuildfolder.h \
    treemenu.h \
    changestyle.h \
    textedit.h

FORMS += \
        mainwindow.ui \
    findwindow.ui \
    dialog_new.ui

RESOURCES += \
    icon.qrc \
    customcompleter.qrc

# 添加图标
RC_FILE += logo.rc
