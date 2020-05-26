#include "scene.h"
#include <QtMath>

Scene::Scene(QWidget* parent)
    :QOpenGLWidget(parent)
{
    a=new Axes;
    objs=new Sphere_and_conus;
    hand=new Cylinder(def,30,30,0.08,0.01,5.9);

    type=GL_POLYGON;

    cam=new Camera;

    l_angle=0.0f;
    l_pos={10*cosf(l_angle/50),6,10*sinf(l_angle/50),0.0f};
    l={l_pos,{0.2f,0.2f,0.2f},{1.0f,1.0f,1.0f},{1.9f,1.9f,1.9f}};
    glnc={{1.9f,1.9f,1.9f},{0.9f,0.9f,0.9f},{5.0f,5.0f,6.0f},256.0f};
    mat={{1.1f,1.1f,1.1f},{0.5f,0.5f,0.5f},{0.3f,0.3f,0.3f},8.0f};
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

    glEnable(GL_CLIP_DISTANCE0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

}

void Scene::resizeGL(int w, int h){
    glViewport(0,0,w,h);

}

void Scene::paintGL(){

    l_pos={10*cosf(l_angle/50),6,10*sinf(l_angle/50),0.0f};
    l={l_pos,{0.2f,0.2f,0.2f},{1.0f,1.0f,1.0f},{1.9f,1.9f,1.9f}};


    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    glClear(GL_COLOR_BUFFER_BIT);

    cam->moveCam(&keys);

    QMatrix4x4 model, view=cam->getMatrix(), projection;
    Material m=glnc;

    projection.perspective(70.0f, 2300.0f/1080.0f, 0.1f, 100.0f);

    //matrix.rotate(100.0f * m_frame / 300, 0, 1, 0);

    def_sh->bind();
    def_sh->setUniformValue("clip",false);
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("normal_m",model.normalMatrix());
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

 //   a->drawAxis(def_sh);

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

    model.setToIdentity();  //сбрасываю модельную матрицу
    model.rotate(90.0f,{1.0f,0.0f,0.0f}); //поворачиваю торус
    model.scale({1.0f,1.5f,1.0f});  //вытягиваю, чтобы придать форму ручки
    model.translate({-0.6f,0.0f,0.0f}); //переношу на свое место
    model.rotate(-45.0f,{1.0f,0.0f,0.0f}); //поворачиваю каждую деталь, что зонтик лежал диагонально
    def_sh->bind();                         //бинд шейдерной программы
    def_sh->setUniformValue("matrix",projection*view*model);   //передаю матрицы преобразования шейдеру
    def_sh->setUniformValue("modelview",view*model);
    def_sh->setUniformValue("normal_m",model.normalMatrix());
    handler_tex->bind();        //бинд текстуры
    def_sh->setUniformValue("texture",0); //передаю текстуру как юниформ переменную
    def_sh->release();

    drawTorus(def_sh);  //рисую торус

    model.setToIdentity();
    model.rotate(-45.0f,{1.0f,0.0f,0.0f});
    model.scale({7.0f,7.0f,5.0f});


    def_sh->bind();
    def_sh->setUniformValue("clip",false);
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("modelview",view*model);
    def_sh->setUniformValue("normal_m",model.normalMatrix());
    sphere_tex->bind();
    def_sh->setUniformValue("texture",0);
    def_sh->release();

    objs->drawObj(def_sh, GL_FILL);


    model.setToIdentity();
    model.translate({0.0f,2.2f,2.2f});
    model.rotate(90.0f,{1.0f,0.0f,0.0f});

    model.rotate(-45.0f,{1.0f,0.0f,0.0f});

    def_sh->bind();
    def_sh->setUniformValue("clip",false);
    def_sh->setUniformValue("matrix",projection*view*model);
    def_sh->setUniformValue("modelview",view*model);
    def_sh->setUniformValue("normal_m",model.normalMatrix());
    cyl_tex->bind();
    def_sh->setUniformValue("texture",0);
    def_sh->release();
    hand->draw(def_sh);

    if(light_flag)l_angle++;
    ++m_frame;
    update();
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

void Scene::drawTorus(QOpenGLShaderProgram* m_program, double r, double c, int rSeg, int cSeg)
{
    QVector<QVector3D> points;
    QVector<QVector2D> tex_coords;
    QVector<QVector3D> normals;



      for (int i = 0; i < rSeg; i++) {
        for (int j = 0; j <= cSeg; j++) {
          for (int k = 0; k <= 1; k++) {
            double s = (i + k) % rSeg + 0.5;
            double t = j % (cSeg + 1);

            float x = (c + r * cos(s * M_PI*2 / rSeg)) * cosf(t * M_PI*2 / cSeg);
            float y = (c + r * cos(s * M_PI*2 / rSeg)) * sinf(t * M_PI*2 / cSeg);
            float z = r * sin(s * M_PI*2 / rSeg);

            float u = (i + k) / (float) rSeg;
            float v = t / (float) cSeg;

            points.append({2 * x, 2 * y, 2 * z});
            tex_coords.append({u,v});
            normals.append({2 * x, 2 * y, 2 * z});
          }
        }
      }

      m_program->bind();

      m_program->setUniformValue("clip",true);
      m_program->setAttributeArray(0, points.data());
      m_program->setAttributeArray(2,normals.data());
      m_program->setAttributeArray(3,tex_coords.data());

      m_program->setAttributeValue(1,QVector3D{0.1f,0.8f,0.1f});

      m_program->enableAttributeArray(0);
      m_program->enableAttributeArray(2);
      m_program->enableAttributeArray(3);

      glFrontFace(GL_CW);
      glDrawArrays(GL_TRIANGLE_STRIP,0,points.size());
      m_program->disableAttributeArray( 0);
      m_program->disableAttributeArray(2);
      m_program->release();


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

void Scene::keyPressEvent(QKeyEvent *event){
    keys.insert(event->key());

}

void Scene::keyReleaseEvent(QKeyEvent *event){
    if(event->isAutoRepeat()==false)keys.remove(event->key());

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

void Scene::initTextures(){
    sphere_tex=initTexture(":/sphere.bmp");
    handler_tex=initTexture(":/handler.bmp");
    cyl_tex=initTexture(":/cylinder.bmp");
}
