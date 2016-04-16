/****************************************************************************
** **Settlers of Catan**
** LogoWidget
** author:John Hanks / Dore Weber / Frank Sasto / Sarah Hong
** date: 4/18/2012
**
** This is a lable that is moved around by screen manager and it is just a manager
** This is just a img that is loaded the class.
**
**
****************************************************************************/


#ifndef LOGOWIDGET_H
#define LOGOWIDGET_H

#include <QWidget>
#include "client/widgets/slidingwidget.h"

namespace Ui {
class LogoWidget;
}

class LogoWidget : public SlidingWidget
{
    Q_OBJECT
    
public:
    explicit LogoWidget(QWidget *parent = 0);
    ~LogoWidget();
    
private:
    Ui::LogoWidget *ui;
};

#endif // LOGOWIDGET_H
