#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    robot = (new ROBOT_SIMULATION(ui->widget));
}

Widget::~Widget()
{
    delete ui;
}
