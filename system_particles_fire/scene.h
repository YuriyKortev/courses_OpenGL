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
#include <QOpenGLTexture>

#include "fire.h"
#include "camera.h"
#include "axes.h"

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


private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* release) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    bool mouse_flag;

    QOpenGLShaderProgram* axes_shader;
    QOpenGLShaderProgram* fire_shader;


    GLuint m_frame;

    Fire* fire;
    Camera* cam;
    Axes* axes;

    GLfloat cam_angle;
    GLfloat cam_y;
    GLfloat cam_r;
    QPointF start;

    QSet<int> keys;

    QOpenGLTexture* initTexture(const char* nof);

    QOpenGLTexture* sprite;
    QOpenGLTexture* colorMap;

    void initTextures();

};


#endif // SCENE_H
