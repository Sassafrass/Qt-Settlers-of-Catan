
#include "shared/hand.h"
#include "shared/base_player.h"

PlayerHand::PlayerHand(CatanPlayerBase *owner) : QObject(owner), owner(owner)
{
    //initialize all the resource counts to zero
    resourceCounts.insert(RESOURCE::BRICK, 0);
    resourceCounts.insert(RESOURCE::WOOL, 0);
    resourceCounts.insert(RESOURCE::LUMBER, 0);
    resourceCounts.insert(RESOURCE::ORE, 0);
    resourceCounts.insert(RESOURCE::GRAIN, 0);

    //initialize all the development counts to zero
    developmentCounts.insert(DEVELOPMENT::KNIGHT, 0);
    developmentCounts.insert(DEVELOPMENT::YEAR_OF_PLENTY, 0);
    developmentCounts.insert(DEVELOPMENT::MONOPOLY, 0);
    developmentCounts.insert(DEVELOPMENT::VICTORY, 0);
    developmentCounts.insert(DEVELOPMENT::ROAD_BUILDING, 0);
}

bool PlayerHand::UseResources(QMap<RESOURCE::ENUM, int> resources)
{
    //first check if we have enough of that resource to remove; if any of them return false, then we
    //terminate early and do not do the transaction
    foreach(RESOURCE::ENUM type, resources.keys())
    {
        if(resources[type] > resourceCounts[type])
            return false;
    }

    //if we reach this point then that means we have a good command and can proceed with the removal
    foreach(RESOURCE::ENUM resType, resources.keys())
        UseResource(resType, resources[resType]);

    //if we have reach this point then we have successfully removed everything
    return true;
}

bool PlayerHand::UseResource(RESOURCE::ENUM resource, int count)
{
    if( resourceCounts[ resource ] >= count )
    {
        resourceCounts[ resource ] -= count;
        return true;
    }

    return false;
}

bool PlayerHand::PlayDevelopment(DEVELOPMENT::ENUM type)
{
    //whether or not we successfully removed this development card
    bool successfullyRemoved = false;

    for(int i = 0; i < devHand.length(); i++)
    {
        if(devHand[i]->GetCardType() == type)
        {
            successfullyRemoved = true;

            devHand.removeAt(i);

            //decrement the counts accordingly
            developmentCounts[type]--;

            //once we remove something we terminate early to prevent removing multiple instances of that card
            return successfullyRemoved;
        }
    }

    //if the removal failed then something went wrong
    return successfullyRemoved;
}

void PlayerHand::AddResource(QList<RESOURCE::ENUM> cards)
{
}

void PlayerHand::AddResource(RESOURCE::ENUM res, int count)
{
    resourceCounts[ res ] += count;
}

void PlayerHand::AddDevCardToHand(DevCard *card)
{
    //add the card to the dev deck
    devHand.push_back(card);

    //update the counts accordingly
    developmentCounts[card->GetCardType()]++;
}

int PlayerHand::GetResCount(RESOURCE::ENUM type)
{
    //check which count should be returned
    return resourceCounts[type];
}

int PlayerHand::GetDevCount(DEVELOPMENT::ENUM type)
{
    //check which one should be returned
    return developmentCounts[type];
}
