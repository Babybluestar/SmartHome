#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T14:58:06
#
#-------------------------------------------------


QT       += core gui
QT       += network
QT       += core gui network multimedia  multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    registerwindow.cpp \
    tcpsocket.cpp \
    serveraddressdialog.cpp \
    userinformation.cpp \
    smartprotocol.cpp \
    majorwindow.cpp \
    roomwindow.cpp \
    findpassword.cpp \
    widget.cpp \
    smtp.cpp \
    ball.cpp \
    enemy.cpp \
    game.cpp \
    menubutton.cpp \
    player.cpp \
    gamechoose.cpp \
    food.cpp \
    gamecontroller.cpp \
    snake.cpp \
    wall.cpp \
    mainwindow.cpp

HEADERS  += loginwindow.h \
    registerwindow.h \
    tcpsocket.h \
    serveraddressdialog.h \
    userinformation.h \
    smartprotocol.h \
    majorwindow.h \
    roomwindow.h \
    findpassword.h \
    widget.h \
    smtp.h \
    ball.h \
    enemy.h \
    game.h \
    menubutton.h \
    player.h \
    gamechoose.h \
    food.h \
    gamecontroller.h \
    snake.h \
    wall.h \
    mainwindow.h \
    constants.h

FORMS    += loginwindow.ui \
    registerwindow.ui \
    serveraddressdialog.ui \
    majorwindow.ui \
    roomwindow.ui \
    findpassword.ui \
    widget.ui \
    gamechoose.ui

RESOURCES += \
    resources.qrc
