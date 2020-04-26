QT       += core gui

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

win32 {
        RC_FILE += lge.rc
        OTHER_FILES += lge.rc
}

SOURCES += \
    formtreegenerate.cpp \
    fromtreemanipulation.cpp \
    main.cpp \
    mainwidget.cpp \
    menu.cpp \
    node.cpp \
    settings.cpp \
    state.cpp \
    tree.cpp

HEADERS += \
    formtreegenerate.h \
    fromtreemanipulation.h \
    mainwidget.h \
    menu.h \
    node.h \
    settings.h \
    state.h \
    tree.h

FORMS += \
    formtreegenerate.ui \
    fromtreemanipulation.ui \
    mainwidget.ui \
    menu.ui \
    settings.ui

TRANSLATIONS += TreeApp_ru.ts
TRANSLATIONS += TreeApp_en.ts
TRANSLATIONS += TreeApp_de.ts

CODECFORSRC     = UTF-8

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += qdarkstyle/style.qrc

DISTFILES += \
    state.ini
