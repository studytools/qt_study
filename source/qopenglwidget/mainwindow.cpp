#include "mainwindow.hpp"
#include "qopenglwidget.hpp"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow()
  : QMainWindow()
{
  resize(800, 600);
  CreateActions();
  CreateMenus();
  CreateToolBars();
  CreateStatusBar();

}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateActions()
{
  NewAct = new QAction(QIcon(":/resource/new_file"), tr("&New Empty Project"), this);
  NewAct->setShortcuts(QKeySequence::New);
  NewAct->setStatusTip(tr("New Empty Project."));
  connect(NewAct, &QAction::triggered, this, &MainWindow::NewEmpytProject);

  OpenAct = new QAction(QIcon(":/resource/open_file"), tr("&Open"), this);
  OpenAct->setShortcuts(QKeySequence::Open);
  OpenAct->setStatusTip(tr("Open an existing file"));
  connect(OpenAct, &QAction::triggered, this, &MainWindow::Open);

  SaveAct = new QAction(QIcon(":/resource/save_file"), tr("&Save"), this);
  SaveAct->setShortcuts(QKeySequence::Save);
  SaveAct->setStatusTip(tr("Save the document to disk"));
  connect(SaveAct, &QAction::triggered, this, &MainWindow::Save);

  ExitAct = new QAction(tr("E&xit"), this);
  ExitAct->setShortcuts(QKeySequence::Quit);
  ExitAct->setStatusTip(tr("Exit the application"));
  connect(ExitAct, &QAction::triggered, this, &MainWindow::close);

  AboutAct = new QAction(QIcon(":/resource/about"),tr("&About"), this);
  AboutAct->setStatusTip(tr("Show the application's About box"));
  connect(AboutAct, &QAction::triggered, this, &MainWindow::About);

}

void MainWindow::CreateMenus()
{
  FileMenu = menuBar()->addMenu(tr("&File"));
  FileMenu->addAction(NewAct);
  FileMenu->addAction(OpenAct);
  FileMenu->addAction(SaveAct);
  FileMenu->addSeparator();
  FileMenu->addAction(ExitAct);

  menuBar()->addSeparator();
  ToolMenu = menuBar()->addMenu(tr("&Tool"));

  menuBar()->addSeparator();
  RenderMenu = menuBar()->addMenu(tr("&Render"));

  menuBar()->addSeparator();
  HelpMenu = menuBar()->addMenu(tr("&Help"));
  HelpMenu->addAction(AboutAct);
}

void MainWindow::CreateToolBars()
{
  FileToolBar = addToolBar(tr("File"));
  FileToolBar->addAction(NewAct);
  FileToolBar->addAction(OpenAct);
  FileToolBar->addAction(SaveAct);

  ToolToolBar = addToolBar(tr("Tool"));
}

void MainWindow::CreateStatusBar()
{
  statusBar()->showMessage(tr("Ready"));
}

void MainWindow::NewEmpytProject()
{
   GLWidget *glw = new GLWidget(this);
   setCentralWidget(glw);
//    opengl_widgets_ << glw;
//    foreach (QOpenGLWidget *w, opengl_widgets_)

//      w->update();


}

void MainWindow::Open()
{
}

bool MainWindow::Save()
{
  return true;
}

void MainWindow::About()
{
  QMessageBox::about(this, tr("About Application"),
    tr("The <b>Application</b> qt_hellopengl"));
}


