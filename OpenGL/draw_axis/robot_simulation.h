#ifndef ROBOT_SIMULATION_H
#define ROBOT_SIMULATION_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>
#include <gl/GLU.h>
#include <iostream>


class ROBOT_SIMULATION : public QOpenGLWidget,protected QOpenGLFunctions{
    Q_OBJECT
public:
    ROBOT_SIMULATION(QWidget *parent);
protected:
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram* program;   //着色器程序对象
    //重载几个opengl的重要函数
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // ROBOT_SIMULATION_H
