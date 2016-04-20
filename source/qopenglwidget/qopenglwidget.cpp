#include "qopenglwidget.hpp"
#include <QOpenGLShaderProgram>

GLWidget::GLWidget(QWidget *parent)
  :QOpenGLWidget(parent) 
{
  setMinimumSize(300, 250);
}

GLWidget::~GLWidget()
{
  makeCurrent();
  delete m_program;
  m_vbo_v.destroy();
  m_vbo_c.destroy();
  doneCurrent();
}

static const char *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 setPosition;\n"
    "layout(location = 1) in vec3 setColor;\n"
    "out vec3 color;\n"
    "uniform  mat4 matrix;\n"
    "void main()\n"
    "{\n"
       "gl_Position = matrix * vec4(setPosition, 1.0);\n"
       "color = setColor;\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 color;\n"
    "out vec3 Outcolor;\n"
    "void main()\n"
    "{\n"
       "Outcolor = color;\n"
    "}\n" ;


void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program->link();

  m_posAttr       = m_program->attributeLocation("setPosition");
  m_colAttr       = m_program->attributeLocation("setColor");
  m_matrixUniform = m_program->uniformLocation("matrix");

}

void GLWidget::paintGL()
{

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  QMatrix4x4 modelview;
  modelview.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
  modelview.translate(0, 0, -2);

  m_program->bind();
  m_program->setUniformValue(m_matrixUniform, modelview);
  GLfloat vertices[] = {
    0.0f, 0.707f,
    -0.5f, -0.5f,
    0.5f, -0.5f
  };

  GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
  };

  glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
  glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  m_program->release();

  glDisable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h)
{
}
