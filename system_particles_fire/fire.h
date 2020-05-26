#ifndef FIRE_H
#define FIRE_H

#include <QVector>
#include <QVector3D>
#include <QVector4D>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QtMath>

class Fire: QOpenGLFunctions
{
public:
    Fire();
    void drawFire(QOpenGLShaderProgram* m_program,float time);

private:
    QVector<QVector3D> points;
    QVector<QVector3D> veloc;
    QVector<float> w;
    QVector<float> direction;
    GLuint nump;
    float randFloat(float a, float b);
    float randFloat();
};

#endif // FIRE_H
