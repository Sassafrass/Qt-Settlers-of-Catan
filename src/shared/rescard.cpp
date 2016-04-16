#include "rescard.h"

ResCard::ResCard(RESOURCE::ENUM type, QObject *parent) :
    QObject(parent)
{
    resCardType = type;
}

RESOURCE::ENUM ResCard::GetCardType() const
{
    return resCardType;
}
