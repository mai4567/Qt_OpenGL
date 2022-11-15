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
    QOpenGLShaderProgram* program;   //��ɫ���������
    //���ؼ���opengl����Ҫ����
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    //������
    bool changeview_ = false;            //�ı��ӽǵı�־λ
    float last_x;               //��¼��갴��ʱ����λ���������ӽ�ƫ��
    float last_y;
    float yaw = 0.0;            //ƫ����
    float pitch = 0.0;          //���ӽ�
    float fov = 60.0f;          //��Ұ��Χ
    float sensitivity = 1.5;    //���������
    QVector3D cameraDirection = QVector3D(0.0f,0.0f,1.5f);  //���������
    QVector3D cameraUp = QVector3D(0.0f,1.0f,0.0f);         //�����������
    //��꽻���¼���д
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    //�ı��ӽǱ���
    QMatrix4x4 view;  //�۲����
    QMatrix4x4 projection ;
    QMatrix4x4 common_mat;  //����ƽ����ϰ�߱任�ӽ�
};

#endif // ROBOT_SIMULATION_H
