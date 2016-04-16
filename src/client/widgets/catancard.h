/****************************************************************************
** **Settlers of Catan**
** CatanCard
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This makes the visual of the card object on the PlayerReadWidget
**
****************************************************************************/

#ifndef CATANCARD_H
#define CATANCARD_H

#include <QWidget>
#include "shared/enums/resource.h"

class QLabel;
class QPixmap;

class CatanCardWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit CatanCardWidget(const RESOURCE::ENUM&, QWidget *parent = 0);
    ~CatanCardWidget();
private slots:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
private:
    QLabel *cardCount;
    QPixmap *pixMap;
};

#endif // CATANCARD_H
