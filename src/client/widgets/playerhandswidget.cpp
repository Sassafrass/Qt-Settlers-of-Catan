#include "playerhandswidget.h"
#include "client/widgets/catancard.h"

PlayerHandWidget::PlayerHandWidget() :
    QDialog(0,
            Qt::CustomizeWindowHint |
            Qt::FramelessWindowHint)
{
    addCard(RESOURCE::BRICK);
    addCard(RESOURCE::WOOL);
    addCard(RESOURCE::GRAIN);
    addCard(RESOURCE::LUMBER);
    addCard(RESOURCE::ORE);
    setStyleSheet("background-color: transparent;");
}

void PlayerHandWidget::addCard(const RESOURCE::ENUM &res)
{
    cards[res] = new CatanCardWidget(res, this);
}

void PlayerHandWidget::resizeEvent(QResizeEvent *)
{
    int cardWidth = width() / cards.size();
    int cardHeight = cardWidth / 0.68;
    int xOffset = 0;

    foreach( CatanCardWidget *card, cards )
    {
        card->resize( cardWidth, cardHeight );
        card->move( xOffset, 0 );
        xOffset+=cardWidth;
    }
}

PlayerHandWidget::~PlayerHandWidget()
{
}
