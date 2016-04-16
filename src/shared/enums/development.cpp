#include "shared/enums/development.h"

extern QString DEVELOPMENT::toString(const ENUM &e)
{
    switch(e)
    {
    case KNIGHT:
        return "Knight";
    case YEAR_OF_PLENTY:
        return "Year Of Plenty";
    case MONOPOLY:
        return "Monopoly";
    case ROAD_BUILDING:
        return "Road Building";
    case VICTORY:
        return "Victory";
    default:
        return "Bad Development Card";
    }
}
