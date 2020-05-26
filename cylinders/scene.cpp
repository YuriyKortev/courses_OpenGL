#include "scene.h"
#include <QtMath>


Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    a=new Axes;
    objs=new Sphere_and_conus;

    type=GL_POLYGON;

    l_rad=10.0f;
    l_angle=0.0f;
    l_y=10.0f;

    l={{l_rad*cosf(l_angle),l_y,l_rad*sinf(l_angle),0.0f},{0.6f,0.6f,0.6f},{0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f}};

    glnc={{1.9f,1.9f,1.9f},{0.9f,0.9f,0.9f},{5.0f,5.0f,6.0f},256.0f};
    mat={{0.7f,0.7f,0.7f},{0.9f,0.9f,0.9f},{0.5f,0.5f,0.5f},6.0f};

    cam=new Camera;

    cyl_par=new Cylinder(type_parab,30,30,1.0f,1.0f,5.0f);
    cyl_sqrt=new Cylinder(type_sqrt,30,30,1.0f,1.0f,8.0f);
    cyl_def=new Cylinder(def,30,30,2.0f,2.0f,9.0f);
    cyl_con=new Cylinder(def,30,30,3.0f,0.0f,10.0f);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    keys.insert(event->key());
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()==false)keys.remove(event->key());
}

void Scene::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.9f,0.9f,0.9f,0.3f);


    def_sh=new QOpenGLShaderProgram;
    def_sh->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader.glsl");
    def_sh->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader.glsl");
    def_sh->link();

    spline_sh=new QOpenGLShaderProgram;
    spline_sh->addShaderFromSourceFile(QOpenGLShader::Vertex,":/vShader_spline.glsl");
    spline_sh->addShaderFromSourceFile(QOpenGLShader::Fragment,":/fShader_spline.glsl");
    spline_sh->link();

    initTextures();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CLIP_DISTANCE0);

    glEnable(GL_MULTISAMPLE);


}

void Scene::resizeGL(int w, int h){
    glViewport(0,0,w,h);

}

void Scene::paintGL(){


    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

    renderScene();


    update();
}

void Scene::wheelEvent(QWheelEvent *event)
{

}




void Scene::mousePressEvent(QMouseEvent *event){

    start=QPointF(event->x(),event->y());
    if(event->button()==Qt::RightButton){
        this->setCursor(Qt::BlankCursor);
        mouse_flag=true;
    }
    if(event->button()==Qt::LeftButton){
        light_flag=true;
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
    if(event->button()==Qt::LeftButton){
        light_flag=false;
    }
}

void Scene::drawPlane(QOpenGLShaderProgram *m_program)
{
    QVector<QVector3D> points={
        {4.0f,-4.0f,1.0f},
        {1.0f,4.0f,-4.0f},
        {-4.0f,4.0f,1.0f},
        {1.0,-4.0f,4.0f}
    };

    m_program->bind();
    m_program->setAttributeArray(0,points.data());
   // m_program->setAttributeValue(1,QVector4D{0.1f,0.8f,0.1f,0.1f});
    m_program->setAttributeValue(2,QVector3D{1.0f,1.0f,1.0f});

    m_program->enableAttributeArray(0);
    // m_program->enableAttributeArray(1);
     // m_program->enableAttributeArray(2);
    glDrawArrays(GL_POLYGON ,0,points.size());

    m_program->disableAttributeArray(0);
   // m_program->disableAttributeArray(1);
   // m_program->disableAttributeArray(2);
    m_program->release();
}

void Scene::initTextures()
{
    sqrt_tex=initTexture(":/vlue_side.bmp");
    par_tex=initTexture(":/parab_side.bmp");
    def_tex=initTexture(":/orange_side.bmp");
    con_tex=initTexture(":/purple_side.bmp");
}

void Scene::renderScene()
{
    QMatrix4x4 model,view=this->cam->getMatrix(), projection;

    if(light_flag)l_angle++;

    l={{l_rad*cosf(l_angle/50),l_y,l_rad*sinf(l_angle/50),0.0f},{0.5f,0.5f,0.5f},{1.0f,1.0f,1.0f},{1.9f,1.9f,1.9f}};

    Material m=mat;
    projection.perspective(70.0f, 2300.0f/1080.0f, 0.1f, 100.0f);


    cam->moveCam(&keys);


    def_sh->bind();
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("model",model);
    def_sh->setUniformValue("clip",false);
    def_sh->setUniformValue("modelview",view*model);
    def_sh->setUniformValue("LightInfo.position",l.light_pos);
    def_sh->setUniformValue("LightInfo.la",l.la);
    def_sh->setUniformValue("LightInfo.ld",l.ld);
    def_sh->setUniformValue("LightInfo.ls",l.ls);
    def_sh->setUniformValue("MaterialInfo.ka",m.ka);
    def_sh->setUniformValue("MaterialInfo.kd",m.kd);
    def_sh->setUniformValue("MaterialInfo.ks",m.ks);
    def_sh->setUniformValue("MaterialInfo.Shininess",m.Shininess);
    def_sh->release();



    def_sh->bind();

    def_sh->setUniformValue("l.position",l.light_pos);
    def_sh->setUniformValue("l.la",l.la);
    def_sh->setUniformValue("l.ld",l.ld);
    def_sh->setUniformValue("l.ls",l.ls);
    def_sh->setUniformValue("material.ka",m.ka);
    def_sh->setUniformValue("material.kd",m.kd);
    def_sh->setUniformValue("material.ks",m.ks);
    def_sh->setUniformValue("material.Shininess",m.Shininess);
    def_sh->release();



    model.setToIdentity();
    model.translate(0.0f,5.0f/2,0.0f);
    def_sh->bind();
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("model",model);
    def_sh->setUniformValue("modelview",view*model);
    par_tex->bind();
    def_sh->setUniformValue("texture",0);
    def_sh->release();
    cyl_par->draw(def_sh);



    model.setToIdentity();              // модельная матрица - единичная
    model.translate(-5.0f,8.0f/2,0.0f); //перенос
    def_sh->bind();                     //привязка шейдерной программы
    def_sh->setUniformValue("matrix",projection*view*model);    //юниформ переменные на вход шейдеру
    def_sh->setUniformValue("model",model);
    def_sh->setUniformValue("modelview",view*model);
    sqrt_tex->bind();                           //связывание текстуры
    def_sh->setUniformValue("texture",0);
    def_sh->release();
    cyl_sqrt->draw(def_sh);     //отрисовка цилиндра в мировых координатах

    model.setToIdentity();
    model.translate(0.0f,10.0f/2,7.0f);
    model.rotate(-90,0,1,0);
    def_sh->bind();
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("model",model);
    def_sh->setUniformValue("modelview",view*model);
    con_tex->bind();
    def_sh->setUniformValue("texture",0);
    def_sh->release();



    glEnable(GL_STENCIL_TEST);      //включаю тест трафарета
    glStencilFunc(GL_ALWAYS, 1, 1); //тест проходят все пиксели
    glStencilOp(GL_INCR, GL_INCR, GL_INCR); //при прохождении теста значение буфера увеличивается на 1
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);    // включаю отрисовку только  задних граней

    cyl_con->draw(def_sh,true);     //рисую цилиндр
    glStencilOp(GL_DECR, GL_DECR, GL_DECR);//при прохождении теста значение буфера уменьшается на 1
    glCullFace(GL_FRONT);   // включаю отрисовку только  передних граней
    cyl_con->draw(def_sh,true); //рисую цилиндр
    glDisable(GL_CULL_FACE);    //отсключаю cull_face
    glStencilFunc(GL_EQUAL, 1, 1);  //тест проходят только пиксели, значения которых в буфере = 1
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //если не прошли то отбрасываются
    drawPlane(def_sh);              //рисую плоскость
    glDisable(GL_STENCIL_TEST); //выключаю тест трафарета


    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    glEnable(GL_CULL_FACE);


    model.setToIdentity();
    model.translate(5.0f,9.0f/2,5.0f);
    model.rotate(-180,0,1,0);
    def_sh->bind();
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("model",model);
    def_sh->setUniformValue("modelview",view*model);
    def_tex->bind();
    def_sh->setUniformValue("texture",0);
    def_sh->release();

    glCullFace(GL_BACK);
    cyl_def->draw(def_sh,true);
    glStencilOp(GL_DECR, GL_DECR, GL_DECR);
    glCullFace(GL_FRONT);
    cyl_def->draw(def_sh,true);
    glDisable(GL_CULL_FACE);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    drawPlane(def_sh);
    glDisable(GL_STENCIL_TEST);



    ++m_frame;
}

QOpenGLTexture *Scene::initTexture(const char *nof)
{
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


void Scene::mouseMoveEvent(QMouseEvent *event){
    start.setX(event->x()-start.x());
    start.setY(start.y()-event->y());

    if(mouse_flag){
        this->cam->changeYawAndPitch(start.x(),start.y());
    }


    start=event->pos();
    update();
}

