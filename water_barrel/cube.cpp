#include "cube.h"

Cube::Cube()
{

    points={

        QVector3D(-1.0f, -1.0f,  1.0f),  // v0
        QVector3D( 1.0f, -1.0f,  1.0f), // v1
        QVector3D(-1.0f,  1.0f,  1.0f),  // v2-
        QVector3D( 1.0f,  1.0f,  1.0f), // v3-

        // Vertex data for face 1
        QVector3D( 1.0f, -1.0f,  1.0f), // v4
        QVector3D( 1.0f, -1.0f, -1.0f),  // v5
        QVector3D( 1.0f,  1.0f,  1.0f),  // v6-
        QVector3D( 1.0f,  1.0f, -1.0f), // v7-

        // Vertex data for face 2
        QVector3D( 1.0f, -1.0f, -1.0f), // v8
        QVector3D(-1.0f, -1.0f, -1.0f),  // v9
        QVector3D( 1.0f,  1.0f, -1.0f), // v10-
        QVector3D(-1.0f,  1.0f, -1.0f), // v11-

        // Vertex data for face 3
        QVector3D(-1.0f, -1.0f, -1.0f), // v12
        QVector3D(-1.0f, -1.0f,  1.0f),  // v13
        QVector3D(-1.0f,  1.0f, -1.0f), // v14-
        QVector3D(-1.0f,  1.0f,  1.0f),  // v15-

        // Vertex data for face 4
        QVector3D(-1.0f, -1.0f, -1.0f), // v16
        QVector3D( 1.0f, -1.0f, -1.0f), // v17
        QVector3D(-1.0f, -1.0f,  1.0f), // v18
        QVector3D( 1.0f, -1.0f,  1.0f), // v19

        QVector3D(-1.2f,  1.0f,  1.2f), // v20
        QVector3D( 1.2f,  1.0f,  1.2f), // v21
        QVector3D(-1.2f,  1.0f, -1.2f), // v22
        QVector3D( 1.2f,  1.0f, -1.2f)


     };

    tex_coords={
        QVector2D(0.0f, 0.0f),  // v0
        QVector2D(0.33f, 0.0f), // v1
        QVector2D(0.0f, 0.5f),  // v2
        QVector2D(0.33f, 0.5f), // v3

        // Vertex data for face 1
        QVector2D( 0.0f, 0.5f), // v4
        QVector2D(0.33f, 0.5f), // v5
        QVector2D(0.0f, 1.0f),  // v6
        QVector2D(0.33f, 1.0f), // v7

        // Vertex data for face 2
        QVector2D(0.66f, 0.5f), // v8
        QVector2D(1.0f, 0.5f),  // v9
        QVector2D(0.66f, 1.0f), // v10
        QVector2D(1.0f, 1.0f),  // v11

        // Vertex data for face 3
        QVector2D(0.66f, 0.0f), // v12
        QVector2D(1.0f, 0.0f),  // v13
        QVector2D(0.66f, 0.5f), // v14
        QVector2D(1.0f, 0.5f),  // v15

        // Vertex data for face 4
        QVector2D(0.33f, 0.0f), // v16
        QVector2D(0.66f, 0.0f), // v17
        QVector2D(0.33f, 0.5f), // v18
        QVector2D(0.66f, 0.5f), // v19

        // Vertex data for face 5
        QVector2D(0.33f, 0.5f), // v20
        QVector2D(0.66f, 0.5f), // v21
        QVector2D(0.33f, 1.0f), // v22
        QVector2D(0.66f, 1.0f)


    };

    indices={
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
       12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
       16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
       20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
   };

    normals={
        QVector3D(0.0f,0.0f,  1.0f),  // v0
        QVector3D(0.0f,0.0f,  1.0f),  // v0
        QVector3D(0.0f,0.0f,  1.0f),  // v0
        QVector3D(0.0f,0.0f,  1.0f),  // v0

        QVector3D( 1.0f, 0.0f,  0.0f), // v4
        QVector3D( 1.0f, 0.0f, 0.0f),  // v5
        QVector3D( 1.0f,  0.0f,  0.0f),  // v6-
        QVector3D( 1.0f,  0.0f, 0.0f), // v7-

        QVector3D( 0.0f, 0.0f, -1.0f), // v8
        QVector3D( 0.0f, 0.0f, -1.0f), // v8
        QVector3D( 0.0f, 0.0f, -1.0f), // v8
        QVector3D( 0.0f, 0.0f, -1.0f), // v8

        // Vertex data for face 3
        QVector3D(-1.0f, 0.0f, 0.0f), // v12
        QVector3D(-1.0f, 0.0f,  0.0f),  // v13
        QVector3D(-1.0f, 0.0f, 0.0f), // v14-
        QVector3D(-1.0f, 0.0f,  0.0f),  // v15-

        QVector3D(0.0, -1.0f, 0.0f), // v16
        QVector3D( 0.0f, -1.0f, 0.0f), // v17
        QVector3D(0.0f, -1.0f,  0.0f), // v18
        QVector3D( 0.0f, -1.0f,  0.0f), // v19

        QVector3D(0.0f, 1.0f, 0.0f), // v16
        QVector3D(0.0f, 1.0f, 0.0f), // v16
        QVector3D(0.0f, 1.0f, 0.0f), // v16
        QVector3D(0.0f, 1.0f, 0.0f), // v16


    };

    for(auto& coord: tex_coords)coord*=coord*3;
}

void Cube::draw(QOpenGLShaderProgram *m_program)
{
    initializeOpenGLFunctions();
    m_program->bind();
    m_program->setAttributeArray(0, points.data());
    m_program->setAttributeArray(2,normals.data());
    m_program->setAttributeArray(3,tex_coords.data());

  //  m_program->setAttributeValue(1,QVector3D{0.1f,0.8f,0.1f});

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(2);
    m_program->enableAttributeArray(3);

    glDrawElements(GL_TRIANGLE_STRIP,indices.size(),GL_UNSIGNED_SHORT,indices.data());

    m_program->disableAttributeArray(0);
    m_program->disableAttributeArray(2);
    m_program->disableAttributeArray(3);
    m_program->release();
}
