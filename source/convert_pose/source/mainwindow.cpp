#include "mainwindow.hpp"
#include "ui_widget.h"
#include "read_file.hpp"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent):
QWidget(parent),
    ui(new Ui::Widget)
{
  ui->setupUi(this);
 creatConnect();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::creatConnect()
{
  connect(ui->pushButton_input,&QPushButton::clicked,this,&MainWindow::openPoseFile);
}

void MainWindow::openPoseFile()
{
  QString file_name =  QFileDialog::getOpenFileName(
    this,
    tr("Open Pose File"),
    "",
    tr("Pose Files (*.txt *.log) || All Files (*.*)"));

  ui->lineEdit_input->setText(file_name);

 ReadFile rf(file_name);

}