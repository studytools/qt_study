#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QMatrix4x4>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT
public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();

protected:
  void resizeGL(int w, int h) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;

private:
  QOpenGLShaderProgram *m_program;
  QOpenGLBuffer m_vbo_v;
  QOpenGLBuffer m_vbo_c;
  GLuint m_posAttr;
  GLuint m_colAttr;
  GLuint m_matrixUniform;

};

#endif