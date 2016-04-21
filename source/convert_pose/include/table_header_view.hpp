#ifndef _TABLE_HEADER_VIEW_HPP_
#define _TABLE_HEADER_VIEW_HPP_

#include <QtGui>
#include <QHeaderView>
#include <QComboBox>

class PoseData;

class CCheckBoxHeaderView: public QHeaderView
{
  Q_OBJECT
public:
  CCheckBoxHeaderView(PoseData* pose_data, Qt::Orientation orientation,
           QWidget * parent = 0);

public slots:
  void comboboxIndexChanged(int box_index);
  void updateHeader();

signals:
  void updateTable();

protected:
  void paintEvent(QPaintEvent *e);

private:
  void CreateCombobox(int column);

private:
  QMap<int, QComboBox *> column_boxes_;
  bool need_reset_pose_index_;
  PoseData* pose_data_;
};

#endif
