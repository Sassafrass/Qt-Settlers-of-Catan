/****************************************************************************
** **Settlers of Catan**
** SCREEN_NAME
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is the state for which screen we are currently on
** The state is also used on the screen manager which uses it switch screens
**
****************************************************************************/

#ifndef SCREEN_H
#define SCREEN_H

namespace SCREEN_NAME {
enum ENUM
{
    LOGIN,
    MAIN_MENU,
    LOBBY,
    CREATE_ROOM,
    READY_ROOM,
    GAMEBOARD
};
}
#endif // SCREEN_H
