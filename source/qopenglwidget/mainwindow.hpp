#ifndef QT_HELLOOPENGL_QOPENGLWIDGET_MAINWINDOW_HPP_
#define QT_HELLOOPENGL_QOPENGLWIDGET_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QVector>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QPushButton>

QT_FORWARD_DECLARE_CLASS(QOpenGLWidget)

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

private slots:
  void NewEmpytProject();
  void Open();
  bool Save();
  void About();

private:
  QVector<QOpenGLWidget *> opengl_widgets_;

  void CreateActions();
  void CreateMenus();
  void CreateToolBars();
  void CreateStatusBar();

  QMenu *FileMenu;
  QMenu *ToolMenu;
  QMenu *RenderMenu;
  QMenu *HelpMenu;
  QToolBar *FileToolBar;
  QToolBar *ToolToolBar;
  QAction *NewAct;
  QAction *OpenAct;
  QAction *SaveAct;
  QAction *ExitAct;
  QAction *AboutAct;

};


#endif // !QT_HELLOOPENGL_QOPENGLWIDGET_MAINWINDOW_HPP_
