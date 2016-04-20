#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class MainWindow: public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void creatConnect();

private slots:
  void openPoseFile();

private:
  Ui::Widget *ui;
};

#endif // MAINWINDOW_H


