#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T20:46:58
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyReminder_Note
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        about.cpp \
        login.cpp \
        main.cpp \
        mybasewindow.cpp \
        remind.cpp \
        remindbox.cpp \
        setpasdialog.cpp

HEADERS += \
        about.h \
        login.h \
        mybasewindow.h \
        remind.h \
        remindbox.h \
        setpasdialog.h

FORMS += \
        about.ui \
        login.ui \
        mybasewindow.ui \
        remind.ui \
        remindbox.ui \
        setpasdialog.ui
RC_ICONS = mylogo3.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../myresource_file.qrc
