/****************************************************************************
** **Settlers of Catan**
** DiceDialog
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** The visuals of the Dice object that are used on the ScreenGameBoard
**
****************************************************************************/
\

#ifndef DICEDIALOG_H
#define DICEDIALOG_H

#include <QDialog>


namespace Ui {
class DiceDialog;
}

class DiceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DiceDialog();
    ~DiceDialog();
private slots:
    void receivedGameRollResult(QDataStream& msg);
    void receivedGamePlayersTurn();
    void roll();
private:
    Ui::DiceDialog *ui;
    QTimer* timer;
};

#endif // DICEDIALOG_H
