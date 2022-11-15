#include "./robot_simulation.h"

//坐标系点
static float vertices[] = {//我们所准备的需要提供给openGL的顶点数据
    // 位置              // 颜色
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
    //添加顶点着色器
    program->addShaderFromSourceFile(QOpenGLShader::Vertex,"./coordinate.vert");
    //添加片段着色器
    program->addShaderFromSourceFile(QOpenGLShader::Fragment,"./coordinate.frag");
    program->link();

    //创建并绑定VBO
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));//向VBO传递我们准备好的数据(本文件起始部分的静态数组)

    //向顶点着色器传递其中定义为"aPos"的变量所需的数据
    program->setAttributeBuffer(program->attributeLocation("aPos"),GL_FLOAT, 0, 3,6*sizeof(GLfloat));
    program->enableAttributeArray(program->attributeLocation("aPos"));

    //向顶点着色器传递其中定义为"aColor"的变量所需的数据
    program->setAttributeBuffer(program->attributeLocation("aColor"),GL_FLOAT,3*sizeof(GLfloat),3,6*sizeof(GLfloat));
    program->enableAttributeArray(program->attributeLocation("aColor"));
    program->release();//解绑程序

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  //背景上色
}

void ROBOT_SIMULATION::resizeGL(int w, int h){
    this->glViewport(0,0,w,h);
}

void ROBOT_SIMULATION::paintGL(){
    program->bind();
    glDrawArrays(GL_LINES, 0, 2);//绘制基坐标系
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    program->release();//解绑程序
}
