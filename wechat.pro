QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bubble.cpp \
    configwidget.cpp \
    functiontool.cpp \
    iconbutton.cpp \
    main.cpp \
    mainwindow.cpp \
    messagewidget.cpp \
    showthread.cpp \
    systemtips.cpp \
    trianglewidget.cpp

HEADERS += \
    bubble.h \
    config.h \
    configwidget.h \
    functiontool.h \
    iconbutton.h \
    mainwindow.h \
    messagewidget.h \
    showthread.h \
    systemtips.h \
    trianglewidget.h

FORMS += \
    bubble.ui \
    configwidget.ui \
    functiontool.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
