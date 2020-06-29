QT       += core gui

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    boss.cpp \
    bossball.cpp \
    bossballnew.cpp \
    bulletrain.cpp \
    circle.cpp \
    collision.cpp \
    enemy.cpp \
    enemyball.cpp \
    equipment.cpp \
    fan.cpp \
    gameover.cpp \
    help.cpp \
    laser.cpp \
    lifeadd.cpp \
    logindlg.cpp \
    main.cpp \
    gamecontrol.cpp \
    myplane.cpp \
    myplanebullet.cpp \
    rank.cpp \
    view.cpp \
    wingman.cpp \
    wingmanbullet.cpp

HEADERS += \
    background.h \
    boss.h \
    bossball.h \
    bossballnew.h \
    bulletrain.h \
    circle.h \
    collision.h \
    config.h \
    enemy.h \
    enemyball.h \
    equipment.h \
    fan.h \
    gamecontrol.h \
    gameover.h \
    help.h \
    laser.h \
    lifeadd.h \
    logindlg.h \
    myplane.h \
    myplanebullet.h \
    rank.h \
    view.h \
    wingman.h \
    wingmanbullet.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

CONFIG += resources_big

RC_FILE += myIcon.rc

FORMS += \
    GameOver.ui \
    help.ui \
    logindlg.ui
