#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "pose_data.hpp"
#include "table_header_view.hpp"

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
  void Clear();

private slots:
  void RefreshTable();
  void RefreshIdColumn();
  void OnLineEditSplitChanged();
  void OnPushButtonKML();
  void OnPushButtonIndex();
  void OnPushButtonPrefix();
  void OnPushButtonsuffix();
  void OnPushButtonInput();
  void OnPushButtonOutput();
  void OnLineEditId();
  void OnLineEditSkip();

private:
  Ui::Widget *ui;
  PoseData pose_data_;
  CCheckBoxHeaderView* header_view_;
};

#endif // MAINWINDOW_H


