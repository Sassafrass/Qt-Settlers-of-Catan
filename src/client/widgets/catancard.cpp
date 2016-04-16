
#include <QLabel>
#include <QFont>
#include <QStyle>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include "catancard.h"

CatanCardWidget::CatanCardWidget(const RESOURCE::ENUM &res, QWidget *parent) :
    QWidget(parent)
{
    cardCount = new QLabel("0", this);
    cardCount->setFont(QFont("Courier", 14, QFont::Bold));
    cardCount->setAlignment(Qt::AlignCenter);

    QString cardImage = "Brick";
    if( res == RESOURCE::GRAIN )
        cardImage = "Grain";
    else if( res == RESOURCE::LUMBER )
        cardImage = "Lumber";
    else if( res == RESOURCE::WOOL )
        cardImage = "Wool";
    else if( res == RESOURCE::ORE )
        cardImage = "Ore";

    pixMap = new QPixmap(":/images/cards/"+cardImage);
}

void CatanCardWidget::paintEvent(QPaintEvent *)
{
    QPainter* pPainter = new QPainter(this);
    pPainter->drawPixmap(rect(), *pixMap);
    delete pPainter;
}

void CatanCardWidget::resizeEvent(QResizeEvent *)
{
    QFont font = cardCount->font();
    font.setPixelSize( height() * 0.15 );
    cardCount->resize( width(), font.pixelSize() );
    cardCount->setFont(font);
    cardCount->move( width() * 0.52 - cardCount->width() * 0.5,
                     height() * 0.175 - cardCount->height()*0.5);
}

CatanCardWidget::~CatanCardWidget()
{
}
