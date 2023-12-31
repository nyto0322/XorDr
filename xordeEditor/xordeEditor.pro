QT       += core gui

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
    buttoneditor.cpp \
    chapter.cpp \
    chaptereditor.cpp \
    choicelist.cpp \
    choicepushbutton.cpp \
    configeditor.cpp \
    data.cpp \
    figure.cpp \
    frameinfo.cpp \
    main.cpp \
    mainbacklist.cpp \
    mainwindow.cpp \
    newfile.cpp \
    newpushbutton.cpp \
    performlist.cpp \
    singlesectioneditor.cpp \
    soundlist.cpp \
    speciallist.cpp \
    styleeditor.cpp \
    switchbutton.cpp

HEADERS += \
    buttoneditor.h \
    chapter.h \
    chaptereditor.h \
    choicelist.h \
    choicepushbutton.h \
    configeditor.h \
    data.h \
    figure.h \
    frameinfo.h \
    mainbacklist.h \
    mainwindow.h \
    newfile.h \
    newpushbutton.h \
    performlist.h \
    singlesectioneditor.h \
    soundlist.h \
    speciallist.h \
    styleeditor.h \
    switchbutton.h

FORMS += \
    buttoneditor.ui \
    chaptereditor.ui \
    choicelist.ui \
    configeditor.ui \
    mainbacklist.ui \
    mainwindow.ui \
    newfile.ui \
    performlist.ui \
    singlesectioneditor.ui \
    soundlist.ui \
    speciallist.ui \
    styleeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
