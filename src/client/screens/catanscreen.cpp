#include "catanscreen.h"
#include <QDebug>
#include <QKeyEvent>

CatanScreen::CatanScreen(QWidget *parent, ScreenManager *manager, const QPoint &pos) :
    SlidingWidget(parent), manager(manager), screenPos(pos)
{
}

void CatanScreen::SetActive( bool bActive )
{
    if( bActive && !active )
        Activated();
    else if( !bActive && active )
        Deactivated();
    active = bActive;
}

bool CatanScreen::GetActive() const
{
    return active;
}

void CatanScreen::Activated()
{}
void CatanScreen::Deactivated()
{}

void CatanScreen::keyPressEvent(QKeyEvent*)
{}

void CatanScreen::SetPos(QPoint pos)
{
    this->screenPos = pos;
}

QPoint CatanScreen::GetPos() const
{
    return screenPos;
}

int CatanScreen::x() const
{
    return screenPos.x();
}

int CatanScreen::y() const
{
    return screenPos.y();
}
