QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -L$$PWD -lBruker_WLI
LIBS += -L$$PWD -lWS2_32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    PmacBaseClass/MotorClass.h \
    PmacBaseClass/PmacClass.h \
    PmacBaseClass/inifile.h \
    PmacBaseClass/pch.h \
    PmacBaseClass/pmacserver.h \
    brukerWLI.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# 外部库
win32: LIBS += -L$$PWD/PmacBaseClass/ -lPmacDLL

INCLUDEPATH += $$PWD/PmacBaseClass
DEPENDPATH += $$PWD/PmacBaseClass
