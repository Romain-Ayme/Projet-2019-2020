TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Nos_fichiers/SpaceInvader_AC.cpp \
    Nos_fichiers/nsutil.cpp

HEADERS += \
    Nos_fichiers/SpaceInvader_AC.h \
    Nos_fichiers/MyConst_AC.h \
    Nos_fichiers/MyType_AC.h \
    Nos_fichiers/nsutil.h


DISTFILES += \
    Nos_fichiers/Invader.txt \
    Nos_fichiers/SpaceInvadertext.txt \
    Nos_fichiers/config.yaml \
    Nos_fichiers/lost.txt \
    Nos_fichiers/win.txt
