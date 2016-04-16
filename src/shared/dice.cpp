
#include <QTime>
#include "shared/dice.h"

Dice::Dice(QObject *parent) : QObject(parent)
{
    qsrand(QTime::currentTime().msec()); //set the seed value
}

int Dice::GetRoll()
{
    return qrand() % 12 + 2;
}

int Dice::GetOrderRoll()
{
    return qrand() % 6 + 1;
}
