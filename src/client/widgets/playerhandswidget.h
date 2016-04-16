/****************************************************************************
** **Settlers of Catan**
** PlayerHandWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This Class is used to display the different kind of cards we use eums
** that implement the cards by lodding in a catancard to load the img.
**
**
****************************************************************************/


#ifndef PLAYERHANDSWIDGET_H
#define PLAYERHANDSWIDGET_H

#include <QDialog>
#include <QMap>
#include "shared/enums/resource.h"

class CatanCardWidget;

class PlayerHandWidget : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlayerHandWidget();
    ~PlayerHandWidget();
public slots:
    void resizeEvent(QResizeEvent *);
private:
    void addCard(const RESOURCE::ENUM&);
    QMap<RESOURCE::ENUM, CatanCardWidget*> cards;
};

#endif // PLAYERHANDSWIDGET_H
