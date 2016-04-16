#include "devdeck.h"

Deck::Deck(QObject *parent) :
    QObject(parent)
{
    //set up the development deck; first cards to be added are the KNIGHT cards
    for(int i = 0; i < 14; i++)
    {
        DevCard* card = new DevCard(DEVELOPMENT::KNIGHT, "Move the robber. Steal 1 resource card from the owner of an adjacent settlement or city.");
        deck.push_back(card);
    }
    //next add 5 VICTORY cards
    for(int i = 0; i < 5; i++)
    {
        DevCard* card = new DevCard(DEVELOPMENT::VICTORY, "1 Victory Point!");
        deck.push_back(card);
    }
    //next add 2 YEAR_OF_PLENTY cards
    DevCard* card1 = new DevCard(DEVELOPMENT::YEAR_OF_PLENTY, "Take any 2 resources from the bank. Add them to your hand. They can be 2 of the same resource or 2 different resources.");
    DevCard* card2 = new DevCard(DEVELOPMENT::YEAR_OF_PLENTY, "Take any 2 resources from the bank. Add them to your hand. They can be 2 of the same resource or 2 different resources.");
    deck.push_back(card1);
    deck.push_back(card2);
    //next add 2 MONOPOLY cards
    DevCard* card3 = new DevCard(DEVELOPMENT::MONOPOLY, "When you Play this card, announce 1 type of resource. All other players must give you all their resource cards of that type");
    DevCard* card4 = new DevCard(DEVELOPMENT::MONOPOLY, "When you Play this card, announce 1 type of resource. All other players must give you all their resource cards of that type");
    deck.push_back(card3);
    deck.push_back(card4);
    //next add 2 ROAD_BUILDIN cards
    DevCard* card5 = new DevCard(DEVELOPMENT::ROAD_BUILDING, "Place 2 new roads as if you had just built them.");
    DevCard* card6 = new DevCard(DEVELOPMENT::ROAD_BUILDING, "Place 2 new roads as if you had just built them.");
    deck.push_back(card5);
    deck.push_back(card6);

    //shuffle this deck so that they are in a random order
    ShuffleDeck();
}

void Deck::ShuffleDeck()
{
    //shuffle the deck
    std::random_shuffle(deck.begin(), deck.end());
}

DevCard* Deck::DrawCard()
{
    DevCard *card = 0;
    //check if the deck is empty
    if(!deck.isEmpty())
        card = deck.takeFirst(); //if it is not empty then we remove the card off the top of the deck
    return card;
}

