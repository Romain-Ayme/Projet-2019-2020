TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Nos_fichiers/SpaceInvader_AC.cpp \


QMAKE_MAC_SDK = macosx10.11

HEADERS += \
    Nos_fichiers/SpaceInvader_AC.h \
    Nos_fichiers/MyConst_AC.h \
    Nos_fichiers/MyType_AC.h \


DISTFILES += \
    Nos_fichiers/config.yaml \
    Nos_fichiers/lost.txt \
    Nos_fichiers/win.txt
