/****************************************************************************
** **Settlers of Catan**
** PlayreStatusDialog
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is used on the game board to keep track of the player in game.
** It currently needs to implment ways to change the lables and has no functionality
**
**
****************************************************************************/


#ifndef PLAYERSTATUSDIALOG_H
#define PLAYERSTATUSDIALOG_H

#include <QDialog>
#include "client/entities/player.h"

namespace Ui {
class PlayerStatusDialog;
}

class PlayerStatusDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlayerStatusDialog(CatanPlayer *player);
    ~PlayerStatusDialog();
    
private:
    Ui::PlayerStatusDialog *ui;
    CatanPlayer *player;
};

#endif // PLAYERSTATUSDIALOG_H
