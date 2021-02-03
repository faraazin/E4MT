################################################################################
#   QBuildSystem
#
#   Copyright(c) 2021 by Targoman Intelligent Processing <http://tip.co.ir>
#
#   Redistribution and use in source and binary forms are allowed under the
#   terms of BSD License 2.0.
################################################################################
ProjectName="TargomanCommon"
VERSION=1.1.1

#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-
LIBS += -lz \
        -lTargomanCommon \
        -lTextProcessor \
        -lxml2

#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-
QT+= core network
QT -= gui
QMAKE_CXXFLAGS += -Wno-unknown-pragmas
INCLUDEPATH += 3rdParty

CONFIG += create_prl
CONFIG += link_prl

!defined(QJsonRPC, var)|equals(QJsonRPC, 1) {
    DEFINES += WITH_QJsonRPC
    LIBS += -lQJsonRPC
}else{
    DISABLED_DPES += QJsonRPC
}

#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-
# Qt5.5.1 on OSX needs both c++11 and c++14!! the c++14 is not enough
QMAKE_CXXFLAGS += -std=c++11 -std=c++14
CONFIGS += c++11 c++14

#+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-
#following definitions are used on all Targoman projects
DEFINES += TARGOMAN_DEBUG_PROCESS_LINE=1
DEFINES += TARGOMAN_SHOW_WARNING=1
DEFINES += TARGOMAN_SHOW_INFO=1
DEFINES += TARGOMAN_SHOW_HAPPY=1
DEFINES += TARGOMAN_SHOW_NORMAL=1
