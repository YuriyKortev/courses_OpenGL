#include "fire.h"

Fire::Fire():nump(900)
{


    for(GLuint i=0;i<nump;i++){
        points.append(QVector3D(0.5f,0.0f,0.5f));
    }
    for(GLuint i=0;i<nump;i++){
        veloc.append(QVector3D(randFloat(-0.5f,0.5f),randFloat(1.0f,2.9f),randFloat(0.0f,-0.2f)));
    }

    for(GLuint i=0;i<nump;i++){
        w.append(randFloat());
    }
    for(GLuint i=0;i<nump;i++){
        i<nump/2 ? direction.append(-1.0f) : direction.append(1.0f);
    }
}

void Fire::drawFire(QOpenGLShaderProgram *m_program, float time)
{
    initializeOpenGLFunctions();

    m_program->bind();
    m_program->setUniformValue("time",time);

    GLuint m_posAttr = m_program->attributeLocation( "vertexAttr" );
    GLuint m_veloc = m_program->attributeLocation( "veloc" );
    GLuint m_w=m_program->attributeLocation("w");
    m_program->setAttributeArray( m_posAttr, points.data());
    m_program->setAttributeArray( m_veloc, veloc.data());
    m_program->setAttributeArray(m_w,w.data(),1);
    m_program->setAttributeArray(3,direction.data(),1);
    m_program->enableAttributeArray(m_w);
    m_program->enableAttributeArray( m_posAttr );
    m_program->enableAttributeArray( m_veloc );
    m_program->enableAttributeArray(3);

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    glAlphaFunc(GL_GREATER,0.1f);
    glDrawArrays(GL_POINTS,0,points.size());



    m_program->disableAttributeArray( m_posAttr);
    m_program->disableAttributeArray( m_veloc );
    m_program->disableAttributeArray(m_w);
    m_program->disableAttributeArray(3);
    m_program->release();
}

float Fire::randFloat()
{
    return rand () / (float) RAND_MAX;
}

float Fire::randFloat(float a, float b)
{
    return a + randFloat() * (b - a);
}
