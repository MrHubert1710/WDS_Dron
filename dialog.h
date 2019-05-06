#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <memory>
#include "texturedsphere.h"

class Dialog : public QOpenGLWidget
{
Q_OBJECT
public:
    Dialog(QWidget *parent);

public slots:
    void setRotation(float yaw, float pitch, float roll);
    void setRotationY(int yaw);
    void setRotationP(int pitch);
    void setRotationR(int roll);
    void setZoom(int zoom);

private slots:
    void nextFrame();

protected:

    void initializeGL();
    void paintGL();


private:

    float a_roll=0;
    float a_pitch=0;
    float a_yaw=0;
    QMatrix4x4 m_view;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;
    QMatrix4x4 m_model_def;

    QOpenGLShaderProgram m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_cubeVertices;
    QOpenGLBuffer m_cubeIndices;

    TexturedSphere m_sphere;

    QOpenGLTexture* m_texture;

    QVector3D m_cameraVelocity;

};

#endif // DIALOG_H
