#include "./robot_simulation.h"

//����ϵ��
static float vertices[] = {//������׼������Ҫ�ṩ��openGL�Ķ�������
    // λ��              // ��ɫ
     0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.1f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f, 0.1f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 0.1f,  0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     100.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f, 100.0f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.0f, 0.0f, 100.0f,  0.0f, 0.0f, 1.0f,
};

ROBOT_SIMULATION::ROBOT_SIMULATION(QWidget *parent):QOpenGLWidget(parent)
{
    this->setGeometry(parent->rect().x(),parent->rect().y(),
                      parent->rect().width(),parent->rect().height());

}

void ROBOT_SIMULATION::initializeGL(){
    initializeOpenGLFunctions();
    program = new QOpenGLShaderProgram;
    program->bind();
    //��Ӷ�����ɫ��
    program->addShaderFromSourceFile(QOpenGLShader::Vertex,"./coordinate.vert");
    //���Ƭ����ɫ��
    program->addShaderFromSourceFile(QOpenGLShader::Fragment,"./coordinate.frag");
    program->link();

    //��������VBO
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));//��VBO��������׼���õ�����(���ļ���ʼ���ֵľ�̬����)

    //�򶥵���ɫ���������ж���Ϊ"aPos"�ı������������
    program->setAttributeBuffer(program->attributeLocation("aPos"),GL_FLOAT, 0, 3,6*sizeof(GLfloat));
    program->enableAttributeArray(program->attributeLocation("aPos"));

    //�򶥵���ɫ���������ж���Ϊ"aColor"�ı������������
    program->setAttributeBuffer(program->attributeLocation("aColor"),GL_FLOAT,3*sizeof(GLfloat),3,6*sizeof(GLfloat));
    program->enableAttributeArray(program->attributeLocation("aColor"));
    program->release();//������

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  //������ɫ
}

void ROBOT_SIMULATION::resizeGL(int w, int h){
    this->glViewport(0,0,w,h);
}

void ROBOT_SIMULATION::paintGL(){
    program->bind();
    glDrawArrays(GL_LINES, 0, 2);//���ƻ�����ϵ
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    program->release();//������
}
