#include "devcard.h"

DevCard::DevCard(DEVELOPMENT::ENUM type, const QString & /*inst*/, QObject *parent) :
    QObject(parent)
{
    devCardType = type;
    instructions = "";
}

DEVELOPMENT::ENUM DevCard::GetCardType() const
{
    return devCardType;
}

QString DevCard::GetInstructions() const
{
    return instructions;
}

