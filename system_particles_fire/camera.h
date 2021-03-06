#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>
#include <QtMath>

#define YAW -110.0f
#define PITCH -10.0f

class Camera
{
public:
    Camera(QVector3D pos={2.0f,1.0f,2.0f}, QVector3D worldUp={0.0,1.0,0.0});
    QMatrix4x4 getMatrix();
    void changeYawAndPitch(float yaw, float pitch);
    void moveCam(QSet<int>* keys);

private:
    QVector3D pos;
    QVector3D front;
    QVector3D worldUp;
    QVector3D up;
    QVector3D right;
    float yaw;
    float pitch;

    float movementSpeed;
    float sens;
    void updateCamVectors();
};

#endif // CAMERA_H
