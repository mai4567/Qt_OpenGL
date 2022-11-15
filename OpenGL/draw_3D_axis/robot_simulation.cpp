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
    QMatrix4x4 mat1 = QMatrix4x4();
    mat1.rotate(-90,0,1,0);
    QMatrix4x4 mat2 = QMatrix4x4();
    mat2.rotate(-90,1,0,0);
    common_mat = mat1*mat2;
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

    view.setToIdentity();
    view.lookAt(cameraDirection, QVector3D(0.0f, 0.0f, 0.0f), cameraUp);
    projection.setToIdentity();
    projection.perspective(fov, (float)width() / (float)height(), 0.01f, 10.0f);
    program->setUniformValue("projection", projection);
    program->setUniformValue("view", view);
    program->setUniformValue("common_view",common_mat);

    glDrawArrays(GL_LINES, 0, 2);//绘制基坐标系
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    program->release();//解绑程序
}


//鼠标交互事件
void ROBOT_SIMULATION::mousePressEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton ){
        changeview_ = true;
    }
}


void ROBOT_SIMULATION::mouseReleaseEvent(QMouseEvent *event){
    changeview_ = false;
}


//控制相机变换位置
void ROBOT_SIMULATION::mouseMoveEvent(QMouseEvent *event){
    if (changeview_ == false)
        return;
    //如果鼠标左键按下且未松开，允许视角发生变化
    float offset_x = event->x() - last_x;
    float offset_y = event->y() - last_y;
    if (offset_x>0){  //鼠标向右走offset_x>0
        yaw += sensitivity*1*3.14/180;
    }
    else if (offset_x<0){
        yaw -= sensitivity*1*3.14/180;
    }
    if (offset_y>0){  //鼠标向上走offest_y<0
        pitch += sensitivity*1*3.14/180;
    }
    else if (offset_y<0){
        pitch -= sensitivity*1*3.14/180;
    }
    if(yaw>6.28 || yaw<-6.28)
        yaw = 0;
    if (pitch>3.14/2){
        pitch = 3.13/2;
    }
    if (pitch < -3.14/2){
        pitch = -3.13/2;
    }

    float x_change = 1.5*sin(yaw)*cos(pitch);
    float y_change = 1.5*sin(pitch);
    float z_change = 1.5*cos(yaw)*cos(pitch);

    cameraDirection.setX(x_change);
    cameraDirection.setY(y_change);
    cameraDirection.setZ(z_change);
    cameraUp = QVector3D(0.0f,1.0f,0.0f);
    this->repaint();
    last_x = event->x();
    last_y = event->y();
}


//控制相机缩放
void ROBOT_SIMULATION::wheelEvent(QWheelEvent *event){
    if (event->delta() > 0)
        fov-=2.0f;
    else
        fov+=2.0f;
    if (fov<1.0f)
        fov = 1.0f;
    if (fov>=90.f)
        fov = 90.0;
    this->repaint();
}
