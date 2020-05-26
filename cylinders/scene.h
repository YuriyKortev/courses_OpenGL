#ifndef SCENE_H
#define SCENE_H

#include <QtGui/QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <vector>
#include <QMatrix4x4>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QKeyEvent>
#include <QCursor>
#include <QOpenGLTexture>
#include <QImage>
#include <QSet>

#include "camera.h"
#include "axes.h"
#include "sphere_and_conus.h"
#include "cylinder.h"

struct Light{
    QVector4D light_pos;
    QVector3D la;
    QVector3D ld;
    QVector3D ls;
};

struct Material{
    QVector3D ka;
    QVector3D kd;
    QVector3D ks;
    float Shininess;
};

class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
    Scene(QWidget* parent=0);
    Sphere_and_conus* objs;
protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void drawPlane(QOpenGLShaderProgram* m_program);
    void initTextures();

    void renderScene();

    QOpenGLTexture* initTexture(const char* nof);

    bool mouse_flag;
    bool light_flag;



    QOpenGLShaderProgram* def_sh;
    QOpenGLShaderProgram* spline_sh;

    GLuint m_frame;
    Camera* cam;
    Axes* a;
    QPointF start;
    GLenum type;

    Light l;
    float l_y;
    float l_rad;
    float l_angle;

    Material glnc,mat;

    QSet<int> keys;

    Cylinder* cyl_par;
    Cylinder* cyl_sqrt;
    Cylinder* cyl_def;
    Cylinder* cyl_con;

    QOpenGLTexture* par_tex;
    QOpenGLTexture* sqrt_tex;
    QOpenGLTexture* def_tex;
    QOpenGLTexture* con_tex;

};


#endif // SCENE_H
