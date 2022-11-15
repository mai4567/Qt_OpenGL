#include "./robot_simulation.h"

ROBOT_SIMULATION::ROBOT_SIMULATION(QWidget *parent):QOpenGLWidget(parent)
{
    this->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

}

void ROBOT_SIMULATION::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  //±³¾°ÉÏÉ«
}

void ROBOT_SIMULATION::resizeGL(int w, int h){

}

void ROBOT_SIMULATION::paintGL(){

}
