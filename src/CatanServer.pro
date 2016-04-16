#-------------------------------------------------
#
# Project created by QtCreator 2012-03-31T11:45:13
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = CatanServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    server/user.cpp \
    server/server.cpp \
    server/main.cpp \
    server/lobby.cpp \
    server/managers/networkmanager.cpp \
    server/managers/lobbymanager.cpp \
    shared/enums/token.cpp \
    shared/enums/terrain.cpp \
    shared/enums/resource.cpp \
    shared/enums/playercolor.cpp \
    shared/qout.cpp \
    shared/connection.cpp \
    server/client.cpp \
    shared/managers/sh_networkmanager.cpp \
    shared/enums/development.cpp \
    shared/dice.cpp \
    shared/base_player.cpp \
    server/entities/player.cpp \
    server/managers/gamemanager.cpp \
    server/game.cpp \
    server/managers/turnmanager.cpp \
    shared/entities/tile.cpp \
    shared/entities/chit.cpp \
    shared/entities/board.cpp \
    shared/entities/base.cpp \
    shared/gameconfig.cpp \
    shared/hand.cpp \
    shared/devdeck.cpp \
    shared/devcard.cpp \
    shared/rescard.cpp \
    shared/entities/vertex.cpp \
    shared/entities/piece.cpp \
    shared/entities/settlement.cpp \
    shared/entities/city.cpp \
    shared/entities/socket.cpp \
    shared/entities/edge.cpp \
    shared/entities/road.cpp

HEADERS += \
    server/user.h \
    server/server.h \
    server/lobby.h \
    server/managers/networkmanager.h \
    server/managers/lobbymanager.h \
    shared/enums/token.h \
    shared/enums/terrain.h \
    shared/enums/resource.h \
    shared/enums/playercolor.h \
    shared/enums/direction.h \
    shared/enums/command.h \
    shared/qout.h \
    shared/connection.h \
    server/client.h \
    shared/managers/sh_networkmanager.h \
    server/enums/userstate.h \
    shared/enums/development.h \
    shared/dice.h \
    server/entities/player.h \
    shared/enums/playerstate.h \
    shared/base_player.h \
    shared/defines.h \
    shared/enums/gameconfig.h \
    server/entities/player.h \
    server/entities/tile.h \
    server/entities/chit.h \
    server/entities/board.h \
    server/entities/base.h \
    shared/unitconvert.h \
    server/managers/gamemanager.h \
    server/game.h \
    server/managers/turnmanager.h \
    shared/entities/tile.h \
    shared/entities/chit.h \
    shared/entities/board.h \
    shared/entities/base.h \
    shared/gameconfig.h \
    shared/hand.h \
    shared/devdeck.h \
    shared/devcard.h \
    shared/rescard.h \
    shared/enums/gamestate.h \
    shared/enums/turnphase.h \
    shared/sh_util.h \
    shared/entities/vertex.h \
    shared/entities/piece.h \
    shared/entities/settlement.h \
    shared/entities/city.h \
    shared/entities/socket.h \
    shared/entities/edge.h \
    shared/entities/road.h
