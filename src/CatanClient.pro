#-------------------------------------------------
#
# Project created by QtCreator 2012-03-31T12:29:44
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += network
QT       += opengl
QT       += 3d


TARGET = CatanClient
TEMPLATE = app
CONFIG += qt debug

SOURCES += \
    shared/enums/token.cpp \
    shared/enums/terrain.cpp \
    shared/enums/resource.cpp \
    shared/enums/playercolor.cpp \
    shared/managers/sh_networkmanager.cpp \
    shared/qout.cpp \
    shared/connection.cpp \
    shared/base_player.cpp \
    shared/hand.cpp \
    shared/devdeck.cpp \
    shared/devcard.cpp \
    shared/rescard.cpp \
    shared/entities/tile.cpp \
    shared/entities/chit.cpp \
    shared/entities/board.cpp \
    shared/entities/base.cpp \
    shared/entities/vertex.cpp \
    shared/entities/socket.cpp \
    shared/entities/settlement.cpp \
    shared/entities/road.cpp \
    shared/entities/piece.cpp \
    shared/entities/edge.cpp \
    shared/entities/city.cpp \
    client/main.cpp \
    client/client.cpp \
    client/texture.cpp \
    client/forms/mainwindow.cpp \
    client/enums/c_playercolor.cpp \
    client/managers/networkmanager.cpp \
    client/managers/screenmanager.cpp \
    client/managers/c_catangame.cpp \
    client/screens/catanscreen.cpp \
    client/screens/screenlogin.cpp \
    client/screens/screenmainmenu.cpp \
    client/screens/screenjoin.cpp \
    client/screens/screencreate.cpp \
    client/screens/screengamelobby.cpp \
    client/screens/screengameboard.cpp \
    client/widgets/slidingwidget.cpp \
    client/widgets/login.cpp \
    client/widgets/logowidget.cpp \
    client/widgets/playerreadywidget.cpp \
    client/widgets/roomlabel.cpp \
    client/widgets/roomlistwidget.cpp \
    client/widgets/playerhandswidget.cpp \
    client/widgets/catancard.cpp \
    client/widgets/boardscene.cpp \
    client/widgets/graphicswidget.cpp \
    client/widgets/playerstatusdialog.cpp \
    client/widgets/dicedialog.cpp \
    client/entities/player.cpp \
    client/renderables/renderable.cpp \
    client/renderables/geometry/geometry.cpp \
    client/renderables/texrenderable.cpp \
    client/renderables/r_tile.cpp \
    client/renderables/r_chit.cpp \
    client/unitconvert.cpp \
    client/renderables/r_road.cpp \
    client/renderables/r_piece.cpp

HEADERS  += \
    client/forms/mainwindow.h \
    shared/enums/token.h \
    shared/enums/terrain.h \
    shared/enums/resource.h \
    shared/enums/playercolor.h \
    shared/enums/direction.h \
    shared/enums/command.h \
    client/enums/c_playercolor.h \
    client/managers/networkmanager.h \
    shared/qout.h \
    shared/connection.h \
    shared/managers/sh_networkmanager.h \
    client/client.h \
    client/managers/screenmanager.h \
    client/enums/screen.h \
    client/screens/catanscreen.h \
    client/widgets/slidingwidget.h \
    client/widgets/login.h \
    client/screens/screenlogin.h \
    client/screens/screenmainmenu.h \
    client/widgets/logowidget.h \
    client/screens/screenjoin.h \
    client/screens/screencreate.h \
    client/screens/screengamelobby.h \
    client/widgets/playerreadywidget.h \
    client/widgets/roomlabel.h \
    client/widgets/roomlistwidget.h \
    client/screens/screengameboard.h \
    client/widgets/playerhandswidget.h \
    shared/base_player.h \
    shared/enums/playerstate.h \
    client/entities/player.h \
    shared/defines.h \
    client/widgets/catancard.h \
    shared/entities/tile.h \
    shared/entities/chit.h \
    shared/entities/board.h \
    shared/entities/base.h \
    client/managers/c_catangame.h \
    shared/hand.h \
    shared/devdeck.h \
    shared/devcard.h \
    shared/rescard.h \
    client/texture.h \
    client/renderables/renderable.h \
    shared/sh_util.h \
    client/util.h \
    client/renderables/geometry/geometry.h \
    client/renderables/texrenderable.h \
    client/renderables/r_tile.h \
    client/renderables/r_chit.h \
    client/unitconvert.h \
    client/widgets/boardscene.h \
    client/widgets/graphicswidget.h \
    client/widgets/playerstatusdialog.h \
    client/widgets/dicedialog.h \
    shared/entities/vertex.h \
    shared/entities/socket.h \
    shared/entities/settlement.h \
    shared/entities/road.h \
    shared/entities/piece.h \
    shared/entities/edge.h \
    shared/entities/city.h \
    client/renderables/r_road.h \
    client/renderables/r_piece.h

FORMS    += \
    client/forms/mainwindow.ui \
    client/widgets/login.ui \
    client/screens/screenlogin.ui \
    client/screens/screenmainmenu.ui \
    client/widgets/logowidget.ui \
    client/screens/screenjoin.ui \
    client/screens/screencreate.ui \
    client/screens/screengamelobby.ui \
    client/widgets/playerreadywidget.ui \
    client/widgets/playerstatusdialog.ui \
    client/widgets/dicedialog.ui

RESOURCES += \
    clientresources.qrc
