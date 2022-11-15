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

    view.setToIdentity();
    view.lookAt(cameraDirection, QVector3D(0.0f, 0.0f, 0.0f), cameraUp);
    projection.setToIdentity();
    projection.perspective(fov, (float)width() / (float)height(), 0.01f, 10.0f);
    program->setUniformValue("projection", projection);
    program->setUniformValue("view", view);
    program->setUniformValue("common_view",common_mat);

    glDrawArrays(GL_LINES, 0, 2);//���ƻ�����ϵ
    glDrawArrays(GL_LINES, 2, 2);
    glDrawArrays(GL_LINES, 4, 2);
    program->release();//������
}


//��꽻���¼�
void ROBOT_SIMULATION::mousePressEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton ){
        changeview_ = true;
    }
}


void ROBOT_SIMULATION::mouseReleaseEvent(QMouseEvent *event){
    changeview_ = false;
}


//��������任λ��
void ROBOT_SIMULATION::mouseMoveEvent(QMouseEvent *event){
    if (changeview_ == false)
        return;
    //���������������δ�ɿ��������ӽǷ����仯
    float offset_x = event->x() - last_x;
    float offset_y = event->y() - last_y;
    if (offset_x>0){  //���������offset_x>0
        yaw += sensitivity*1*3.14/180;
    }
    else if (offset_x<0){
        yaw -= sensitivity*1*3.14/180;
    }
    if (offset_y>0){  //���������offest_y<0
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


//�����������
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
