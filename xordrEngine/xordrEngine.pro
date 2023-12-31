QT       += core gui multimedia multimediawidgets concurrent

RC_ICONS = icon.ico

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
    bgmplayer.cpp \
    chapter.cpp \
    choicepushbutton.cpp \
    configplayer.cpp \
    data.cpp \
    figure.cpp \
    frameinfo.cpp \
    galleryplayer.cpp \
    loadplayer.cpp \
    main.cpp \
    mainwindow.cpp \
    newpushbutton.cpp \
    performplayer.cpp \
    saveconfig.cpp \
    savedata.cpp \
    saveplayer.cpp \
    sceneplayer.cpp \
    switchbutton.cpp \
    textlabel.cpp


HEADERS += \
    bgmplayer.h \
    chapter.h \
    choicepushbutton.h \
    configplayer.h \
    data.h \
    figure.h \
    frameinfo.h \
    galleryplayer.h \
    loadplayer.h \
    mainwindow.h \
    newpushbutton.h \
    performplayer.h \
    saveconfig.h \
    savedata.h \
    saveplayer.h \
    sceneplayer.h \
    switchbutton.h \
    textlabel.h


FORMS += \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES +=

#QMAKE_LFLAGS += "/STACK:6553600,409600"
