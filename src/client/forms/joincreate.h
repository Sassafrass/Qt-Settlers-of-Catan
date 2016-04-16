#ifndef JOINCREATE_H
#define JOINCREATE_H

#include <QWidget>

namespace Ui {
class JoinCreate;
}

class JoinCreate : public QWidget
{
    Q_OBJECT
    
public:
    explicit JoinCreate(QWidget *parent = 0);
    ~JoinCreate();
    
private:
    Ui::JoinCreate *ui;
};

#endif // JOINCREATE_H
