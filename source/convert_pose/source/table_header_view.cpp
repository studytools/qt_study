#include "table_header_view.hpp"
#include "pose_data.hpp"


CCheckBoxHeaderView::CCheckBoxHeaderView(PoseData* pose_data,
    Qt::Orientation orientation,QWidget * parent)
  : QHeaderView(orientation,parent)
  , pose_data_(pose_data) 
{
}

void CCheckBoxHeaderView::paintEvent(QPaintEvent *e)
{
  if(column_boxes_.size() == count())
  {
    for(int i=0; i<count(); i++)
    {
      column_boxes_[i]->setGeometry(sectionViewportPosition(i)+2,0,
                             sectionSize(i)-5,height()-2);
    }
  }
  QHeaderView::paintEvent(e);
}

void CCheckBoxHeaderView::comboboxIndexChanged(int box_index)
{
  QComboBox* box = dynamic_cast<QComboBox*>(sender());
  int col_index = column_boxes_.key(box);

  if(box_index == 0 || box_index > pose_data_->header().size())
    pose_data_->set_column_type(col_index,PoseData::UNKNOWN);
  else
    pose_data_->set_column_type(col_index,(PoseData::Type)(box_index));

  for(int col =0; col<count(); col++)
  {
    if (col_index == col || column_boxes_[col]->currentIndex() == 0) continue;

    if(column_boxes_[col]->currentIndex() == box_index)
    {
      pose_data_->set_column_type(col,PoseData::UNKNOWN);
      column_boxes_[col]->setCurrentIndex(0);
    }
  }
  emit updateTable();
}

void CCheckBoxHeaderView::updateHeader()
{
  if(column_boxes_.size() < count())
  {
    for(int i=0; i<count(); i++)
    {
      if(!column_boxes_[i])
        CreateCombobox(i);
    }
  }
  else if(column_boxes_.size() > count())
  {
    int boxes_count = column_boxes_.size();
    for (int i = count(); i < boxes_count; i++)
    {
      delete column_boxes_[i];
      column_boxes_.remove(i);
      pose_data_->RemoveColumnType(i);
    }
  }
}

void CCheckBoxHeaderView::CreateCombobox(int column)
{
  QComboBox *box = new QComboBox(this);
  box->addItem("?");
  box->addItems(pose_data_->header());
  column_boxes_[column] = box;
  if(column >= pose_data_->header().size())
  {
    box->setCurrentIndex(0);
    pose_data_->set_column_type(column,PoseData::UNKNOWN);
  }
  else
  {
    box->setCurrentIndex(column+1);
    pose_data_->set_column_type(column,(PoseData::Type)(column+1));
  }
  void (QComboBox::*currentIndexChanged)(int) =
    &QComboBox::currentIndexChanged;
  connect(box,currentIndexChanged,
    this,&CCheckBoxHeaderView::comboboxIndexChanged);
  box->show();

}