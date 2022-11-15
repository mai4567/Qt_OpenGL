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
    //鼠标变量
    bool changeview_ = false;            //改变视角的标志位
    float last_x;               //记录鼠标按下时鼠标的位置用以作视角偏移
    float last_y;
    float yaw = 0.0;            //偏航角
    float pitch = 0.0;          //俯视角
    float fov = 60.0f;          //视野范围
    float sensitivity = 1.5;    //鼠标灵敏度
    QVector3D cameraDirection = QVector3D(0.0f,0.0f,1.5f);  //摄像机方向
    QVector3D cameraUp = QVector3D(0.0f,1.0f,0.0f);         //摄像机上向量
    //鼠标交互事件重写
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    //改变视角变量
    QMatrix4x4 view;  //观察矩阵
    QMatrix4x4 projection ;
    QMatrix4x4 common_mat;  //按照平常的习惯变换视角
};

#endif // ROBOT_SIMULATION_H
