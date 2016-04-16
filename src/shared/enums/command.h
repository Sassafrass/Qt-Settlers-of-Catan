/****************************************************************************
** **Settlers of Catan**
** Development Card Enumeration
** author: Team Bronies
** date: 4/25/2012
**
** The NETWORK_COMMAND enumeration represents the enumerations for all
** network commands.  They are the CommandID type of a networked message
****************************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

namespace NETWORK_COMMAND {

enum ENUM
{
    /*******************************************************
     *        SHARED COMMANDS
     *******************************************************/
    /**
     * first message to establish connection
     **/
    GREETING,

    /**
     * used for pinging
     **/
    PING,

    /**
     * used for pinging
     **/
    PONG,
    /*******************************************************
     *        CLIENT COMMANDS
     *******************************************************/
    /**
     * client sends the server his/her name
     * @param username:QString
     **/
    CLIENT_NAME,

    /**
     * client wishes to join a room
     * @param lobbyID:quint16
     **/
    CLIENT_JOIN,

    /**
     * client wants a complete list of available game rooms
     **/
    CLIENT_LIST,

    /**
     * client wishes to create a lobby
     * @param room_name:QString
     * @param max_players:quint8
     * @param maritimeTrade:bool
     * @param randomChits:bool
     **/
    CLIENT_CREATE,

    /**
     * client wishes to forfeit the game
     */
    PLAYER_FORFEIT,

    /**
     * client is ready to start the game
     * @param ready:bool
     **/
    PLAYER_READY,

    /**
     * client wishes to leave a room
     **/
    PLAYER_LEAVE,

    /**
     * client wishes to change his/her color
     * @param color_enum:quint8
     **/
    PLAYER_COLOR,

    /**
     * the host wishes to start the game
     **/
    PLAYER_START,

    /**
     * host of room changes a config option
     * @param optionID:quint16
     * @param option:optionDataType
     **/
    PLAYER_CHANGE_CONFIG,

    /*******************************************************
     *        SERVER COMMANDS
     *******************************************************/
    /**
     * server tells client a new lobby has been created
     * @param lobbyID:quint16
     * @param lobbyName:QString
     * @param maxPlayers:quint8
     **/
    SERVER_ROOM_NEW,

    /**
     * server tells clients a lobby no longer exists
     * @param (roomID:quint16)
     **/
    SERVER_ROOM_CLOSE,

    /**
     * server sends a list of all available rooms
     * @param num_rooms:quint16
     *   //for num_rooms
     * - @param roomID:quint16
     * - @param roomName:QString
     * - @param num_players:quint8
     * - @param max_players:quint8
     **/
    SERVER_ROOM_LIST,

    /**
     * room has started the countdown to begin the game
     **/
    SERVER_ROOM_STARTING,

    /**
     * A player has halted the startup process
     * @param playerID:quint8
     **/
    SERVER_ROOM_START_INTERRUPT,

    /**
     * a room has added or removed a player, and the num players has changed
     * @param room_ID:quint16
     * @param num_players:quint8
     **/
    SERVER_ROOM_UPDATE,

    /**
     * server informs client that a user has joined their room
     * @param lobbyID:quint16
     * @param playerID:quint8
     * @param playerName:QString
     **/
    SERVER_ROOM_USER_JOINED,

    /**
     * server informs client that a user has left their room
     * @param playerID:quint8
     **/
    SERVER_ROOM_USER_EXITED,

    /**
     * server informs room clients that the host has changed
     * @param playerID:quint8
     **/
    SERVER_ROOM_NEW_HOST,

    /**
     * server replies to join request, informing the requester that the room was full
     **/
    SERVER_ROOM_FULL,

    /**
     * server replies to join request, informing the request that the room no longer exists
     **/
    SERVER_ROOM_NONEXISTANT,

    /**
     * server informs the client the status of all the players current in the room
     * @param num_players:quint8
     * @param hostID:quint8
     * @param hostName:QString
     * @param hostReady:bool
     *   //for num_players - 1
     * - @param playerID:quint8
     * - @param playerName:QString
     * - @param playerReady:bool
     **/
    SERVER_ROOM_PLAYERS,

    /**
     * server informs player of the game configuration in full
     * @param maxPlayer:quint8
     * @param randomChits:bool
     * @param maritimeTrading:bool
     **/
    SERVER_ROOM_CONFIG_FULL,

    /**
     * server informs players that another player has changed their ready status
     * @param playerID:quint8
     * @param ready:bool
     **/
    SERVER_ROOM_PLAYER_READY,

    /**
     * game informs its players that the game has started
     * @param boardSeed:quint16
     * @param numPlayers:quint8
     *  //for numPlayers
     * - @param playerID:quint8
     * - @param playerColor:quint8 //PLAYER_COLOR::ENUM
     **/
    SERVER_GAME_START,

    /**
     * game informs its players that the game has officially ended
     **/
    SERVER_GAME_END,

    /**
     * game informs its players of a dice roll result
     * @param playerID:quint8
     * @param result:quint8
     **/
    SERVER_GAME_ROLL_RESULT,

    /*******************************************************
     *        NONE COMMAND
     *******************************************************/
    //none command MUST BE LAST ENUMERATION
    NONE
};

} // namespace USER_COMMAND
typedef NETWORK_COMMAND::ENUM NetworkCommand;

#endif // COMMANDS_H
