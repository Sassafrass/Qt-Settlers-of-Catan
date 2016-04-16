ifndef YOURHANDWIDGET_H
#define YOURHANDWIDGET_H

#include <QWidget>

namespace Ui {
class YourHandWidget;
}

class YourHandWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit YourHandWidget(QWidget *parent = 0);
    ~YourHandWidget();
    
private:
    Ui::YourHandWidget *ui;
};

#endif // YOURHANDWIDGET_H
