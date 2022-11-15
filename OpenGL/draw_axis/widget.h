#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "./robot_simulation.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    ROBOT_SIMULATION *robot;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
