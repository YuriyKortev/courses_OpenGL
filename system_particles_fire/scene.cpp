#include "scene.h"
#include <QtMath>

Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    fire=new Fire;
    cam=new Camera;
    axes=new Axes;

    cam_y=0.0f;
    cam_angle=90.0f;
    cam_r=1.0f;
}


void Scene::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.1f,0.1f,0.1f,1.0f);

    glEnable(GL_POINT_SPRITE);
    glEnable(GL_PROGRAM_POINT_SIZE);


    axes_shader=new QOpenGLShaderProgram;
    axes_shader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader.glsl");
    axes_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader.glsl");
    axes_shader->link();

    fire_shader=new QOpenGLShaderProgram;
    fire_shader->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader_fire.glsl");
    fire_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader_fire.glsl");
    fire_shader->link();

    initTextures();
}

void Scene::resizeGL(int w, int h){
    glViewport(0,0,w,h);

}

void Scene::paintGL(){

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT);


    QMatrix4x4 model, view, projection;
    cam->moveCam(&keys);
    view=cam->getMatrix();


    projection.perspective(70.0f, 2300.0f/1080.0f, 0.1f, 100.0f);

    axes_shader->bind();
    axes_shader->setUniformValue("matrix",projection*view*model);
    axes_shader->release();
    axes->drawAxis(axes_shader);

    float fovy = 60; // degrees
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    float heightOfNearPlane = (float)abs(viewport[3]-viewport[1]) /
        (2*tan(0.5*fovy*M_PI/180.0));


    fire_shader->bind();
    fire_shader->setUniformValue("modelview",model*view);
    fire_shader->setUniformValue("matrix",projection*model*view);
    fire_shader->setUniformValue("heightOfNearPlane",heightOfNearPlane);
    sprite->bind(0);
    colorMap->bind(1);
    fire_shader->setUniformValue("sprite",0);
    fire_shader->setUniformValue("colorMap",1);
    fire_shader->release();

    fire->drawFire(fire_shader, m_frame);




    ++m_frame;
    update();

}

void Scene::mousePressEvent(QMouseEvent *event){
    start=QPointF(event->x(),event->y());
    if(event->button()==Qt::RightButton){
        this->setCursor(Qt::BlankCursor);
        mouse_flag=true;
    }


}

void Scene::mouseReleaseEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton){
        QCursor a;
        a.setPos(QWidget::mapToGlobal({width()/2,height()/2}));
        setCursor(a);
        mouse_flag=false;
        this->unsetCursor();
    }

}

void Scene::mouseMoveEvent(QMouseEvent *event){
    start.setX(event->x()-start.x());
    start.setY(start.y()-event->y());

    if(mouse_flag){
        this->cam->changeYawAndPitch(start.x(),start.y());
    }


    start=event->pos();
    update();
}

QOpenGLTexture* Scene::initTexture(const char *nof){
    QOpenGLTexture * texture = new QOpenGLTexture(QImage(nof).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);

    return texture;
}

void Scene::initTextures()
{
    sprite=initTexture(":/fire.png");
    colorMap=initTexture(":/Flame.tga");
}


void Scene::keyPressEvent(QKeyEvent *event){
    keys.insert(event->key());

}

void Scene::keyReleaseEvent(QKeyEvent *event){
    if(!event->isAutoRepeat())keys.remove(event->key());
}

