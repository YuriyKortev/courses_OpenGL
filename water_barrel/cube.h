#ifndef CUBE_H
#define CUBE_H

#include <QVector>
#include <QVector3D>
#include <QOpenGLFunctions>
#include <QVector2D>
#include <QOpenGLShaderProgram>

class Cube : private QOpenGLFunctions
{
public:
    Cube();
    void draw(QOpenGLShaderProgram* m_program);

private:
    QVector<QVector3D> points;
    QVector<QVector2D> tex_coords;
    QVector<GLushort> indices;
    QVector<QVector3D> normals;
};

#endif // CUBE_H
