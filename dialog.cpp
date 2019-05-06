#include "dialog.h"
#include "ui_mainwindow.h"

#include <array>


#include <QOpenGLFunctions>
#include <QWidget>
#include <QQuaternion>
#include <QOpenGLTexture>
#include <QImage>
#include <QDebug>

#include <glm/glm.hpp>

constexpr float CAMERA_SPEED = 3.0f;


void Dialog::setRotation(float yaw, float pitch, float roll){
    m_model=m_model_def;
    a_yaw=yaw;
    a_pitch=pitch;
    a_roll=roll;

    m_model.rotate(a_yaw, 0.0f, 1.0f, 0.0f);
    m_model.rotate(a_pitch, 0.0f, 0.0f, 1.0f);
    m_model.rotate(a_roll, 1.0f, 0.0f, 0.0f);
    update();
}

void Dialog::setRotationY(int yaw){
    a_yaw=yaw+90;
    m_model=m_model_def;

    m_model.rotate(a_yaw, 0.0f, 1.0f, 0.0f);
    m_model.rotate(a_pitch, 0.0f, 0.0f, 1.0f);
    m_model.rotate(a_roll, 1.0f, 0.0f, 0.0f);
    update();
}
void Dialog::setRotationP(int pitch){
    a_pitch=pitch;
    m_model=m_model_def;

    m_model.rotate(a_yaw, 0.0f, 1.0f, 0.0f);
    m_model.rotate(a_pitch, 0.0f, 0.0f, 1.0f);
    m_model.rotate(a_roll, 1.0f, 0.0f, 0.0f);
    update();
}
void Dialog::setRotationR(int roll){
    a_roll=roll;
    m_model=m_model_def;

    m_model.rotate(a_yaw, 0.0f, 1.0f, 0.0f);
    m_model.rotate(a_pitch, 0.0f, 0.0f, 1.0f);
    m_model.rotate(a_roll, 1.0f, 0.0f, 0.0f);
    update();
}
void Dialog::setZoom(int zoom){
    if(zoom){

    }

}

Dialog::Dialog(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_view()
    , m_cubeIndices(QOpenGLBuffer::IndexBuffer)
    , m_sphere(100, 100)
{
    m_model_def=m_model;

}


// Use C++11 raw string literals for GLSL shader source code

static const char *vertexShaderSourceCore = R"(
    #version 120
    uniform mat4 projMatrix;
    uniform mat4 mvMatrix;

    attribute vec4 vertex;
    attribute vec2 in_texcoord;

    varying vec2 v_texcoord;

    void main() {
       gl_Position = projMatrix * mvMatrix * vertex;
       v_texcoord = in_texcoord;
    }
)";

static const char *fragmentShaderSourceCore = R"(
    #version 120
    uniform sampler2D texture;

    varying vec2 v_texcoord;

    void main() {
       gl_FragColor = texture2D(texture, v_texcoord);
    }
)";

void Dialog::initializeGL()
{

    m_view.setToIdentity();
    m_view.translate(0, 0, -3);

    glClearColor(1, 1, 1, 1);

    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);

    m_program.link();

    m_program.bind();

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);


    const std::vector<VertexData>& vertices = m_sphere.getVertexData();
    const std::vector<unsigned short>& vertexIndices = m_sphere.getIndices();

    static_assert(sizeof(VertexData) == 5*sizeof(float), "VertexData layout not as expected");

    // Setup our vertex buffer object.
    m_cubeVertices.create();
    m_cubeVertices.bind();
    m_cubeVertices.allocate(vertices.data(), vertices.size() * sizeof(VertexData));

    m_cubeIndices.create();
    m_cubeIndices.bind();
    m_cubeIndices.allocate(vertexIndices.data(), vertexIndices.size() * sizeof(GLushort));

    // Tell OpenGL programmable pipeline how to locate vertex position data
    m_program.enableAttributeArray("vertex");
    m_program.setAttributeBuffer("vertex", GL_FLOAT, 0, 3, sizeof(VertexData));

    m_program.enableAttributeArray("in_texcoord");
    m_program.setAttributeBuffer("in_texcoord", GL_FLOAT, sizeof(glm::vec3), 2, sizeof(VertexData));

    m_program.release();

    // Load textures
    m_texture = new QOpenGLTexture(QImage(":/img/map1.png").mirrored(true, true));
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void Dialog::paintGL()
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(this->width()) / this->height(), 0.01f, 100.0f);

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);

    m_vao.bind();

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program.bind();
    m_program.setUniformValue("projMatrix", m_proj);
    m_program.setUniformValue("mvMatrix", m_view * m_model);
    m_texture->bind();
    // Texture unit 0
    m_program.setUniformValue("texture", 0);


    // Draw cube geometry using indices from VBO 1
    f->glDrawElements(GL_TRIANGLES, m_sphere.getIndices().size(), GL_UNSIGNED_SHORT, 0);

    m_program.release();
}

void Dialog::nextFrame()
{

    update();
}

