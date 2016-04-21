#include "mainwindow.hpp"
#include "ui_widget.h"
#include "read_file.hpp"

#include <QFileDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QIntValidator>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent):
QWidget(parent),
    ui(new Ui::Widget)
{
  ui->setupUi(this);

  header_view_ = new CCheckBoxHeaderView(
    &pose_data_,Qt::Horizontal,ui->tableWidget);
  ui->tableWidget->setHorizontalHeader(header_view_);
  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->verticalHeader()->setVisible(false);
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);

  ui->lineEdit_id->setValidator(new QIntValidator());
  ui->lineEdit_id->setText(QString::number(0));
  ui->lineEdit_skip->setValidator(new QIntValidator(0,10000));
  ui->lineEdit_skip->setText(QString::number(0));

 creatConnect();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::creatConnect()
{
  connect(ui->pushButton_input,&QPushButton::clicked,
          this,&MainWindow::OnPushButtonInput);
  connect(ui->pushButton_output,&QPushButton::clicked,
          this,&MainWindow::OnPushButtonOutput);
  connect(ui->pushButton_kml,&QPushButton::clicked,
          this,&MainWindow::OnPushButtonKML);
  connect(ui->lineEdit_split,&QLineEdit::textChanged,
          this,&MainWindow::OnLineEditSplitChanged);
  connect(ui->pushButton_index,&QPushButton::clicked,
          this,&MainWindow::OnPushButtonIndex);
  connect(ui->lineEdit_id,&QLineEdit::textEdited,
          this,&MainWindow::OnLineEditId);
  connect(ui->lineEdit_prefix,&QLineEdit::textEdited,
          this,&MainWindow::OnPushButtonPrefix);
  connect(ui->lineEdit_suffix,&QLineEdit::textEdited,
          this,&MainWindow::OnPushButtonsuffix);
  connect(ui->lineEdit_skip,&QLineEdit::textEdited,
          this,&MainWindow::OnLineEditSkip);
  connect(header_view_,&CCheckBoxHeaderView::updateTable,
          this,&MainWindow::RefreshTable);
}

void MainWindow::OnPushButtonInput()
{
  QString file_name =  QFileDialog::getOpenFileName(
    this,
    QString::fromLocal8Bit("打开pose文件!"),
    "",
    "Pose Files (*.txt *.log) || All Files (*.*)");

  ui->lineEdit_input->setText(file_name);

  QFileInfo file_info(file_name);
  ui->lineEdit_output->setText(file_info.absolutePath());

  if (!ReadWriteFiles::ReadPoseFile(
     file_name,ui->lineEdit_split->text(),pose_data_))
  {
    QMessageBox msgBox;
    msgBox.setText(QString::fromLocal8Bit("读取文件失败!"));
    msgBox.exec();
  }
  RefreshTable();
}

void MainWindow::OnPushButtonOutput()
{
  QString dir = QFileDialog::getExistingDirectory(
    this,QString::fromLocal8Bit("文件保存目录!"),
    "",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  ui->lineEdit_output->setText(dir);
}

void MainWindow::RefreshTable()
{
  int cols = pose_data_.columns();
  int rows = pose_data_.rows();

  ui->tableWidget->clear();
  ui->tableWidget->setColumnCount(pose_data_.columns());
  ui->tableWidget->setRowCount(pose_data_.rows());
  header_view_->updateHeader();
  for (int row = 0; row < pose_data_.rows(); ++row)
  {
    for (int col = 0; col < pose_data_.columns(); ++col)
    {
      ui->tableWidget->setItem(row,col,
        new QTableWidgetItem(pose_data_.data(row,col)));
    }
  }
}

void MainWindow::RefreshIdColumn()
{
  for (int row = 0; row < ui->tableWidget->rowCount(); row++)
  {
    int col = pose_data_.column_type(PoseData::ID);
    QTableWidgetItem* item =
      ui->tableWidget->item(row,col);
    item->setText(pose_data_.data(row,col));
  }
}

void MainWindow::OnLineEditSplitChanged()
{
  QString split = ui->lineEdit_split->text();
  if (!split.isEmpty())
  {
    pose_data_.SplitPose(split.at(0));
    RefreshTable();
    OnLineEditId();
  }
}

void MainWindow::OnPushButtonKML()
{
  QString intpu_file_path = ui->lineEdit_input->text();
  QFileInfo file_name_info(intpu_file_path);
  QString out_file_name = file_name_info.completeBaseName();

  QString file_path = ui->lineEdit_output->text();
  QFileInfo file_info(file_path,out_file_name + QString(".kml"));
  QString full_file = file_info.absoluteFilePath();
  ReadWriteFiles::WritePoseFileKML(full_file,pose_data_);

}

void MainWindow::OnPushButtonIndex()
{
  QString intpu_file_path = ui->lineEdit_input->text();
  QFileInfo file_name_info(intpu_file_path);
  QString out_file_name = file_name_info.completeBaseName();

  QString file_path = ui->lineEdit_output->text();
  QFileInfo file_info(file_path,out_file_name + QString("_out.txt"));
  QString full_file = file_info.absoluteFilePath();
  ReadWriteFiles::WritePoseFile(full_file,pose_data_);
}

void MainWindow::OnLineEditId()
{
  int index = ui->lineEdit_id->text().toInt();
  pose_data_.set_offset(index);
  RefreshIdColumn();
}

void MainWindow::OnPushButtonPrefix()
{
  pose_data_.set_prefix(ui->lineEdit_prefix->text());
  RefreshIdColumn();
}

void MainWindow::OnPushButtonsuffix()
{
  pose_data_.set_suffix(ui->lineEdit_suffix->text());
  RefreshIdColumn();
}

void MainWindow::OnLineEditSkip()
{
  int line = ui->lineEdit_skip->text().toInt();
  pose_data_.set_skip_line(line);
  RefreshTable();
  OnLineEditId();
}
