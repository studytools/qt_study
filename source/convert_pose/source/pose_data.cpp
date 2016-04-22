#include "pose_data.hpp"

PoseData::PoseData()
  : last_split_char_(' ')
  , offset_(0)
  , skip_line_(0)
{
  header_ << "id" 
          << QString::fromLocal8Bit("经度")
          << QString::fromLocal8Bit("纬度")
          << QString::fromLocal8Bit("高度")
          << QString::fromLocal8Bit("俯仰角") 
          << QString::fromLocal8Bit("横滚角") 
          << QString::fromLocal8Bit("偏航角");
}

void PoseData::set_offset(int val)
{
  if (!data_.empty() && !data_.at(0).empty() && 
      !data_.at(skip_line_).at(0).isEmpty())
  {
    int id_index = column_type_.key(ID);
    QString id = data_.at(skip_line_).at(column_type_.key(ID));
    bool is_number = false;
    int first_id = id.toInt(&is_number);
    if (is_number)
    {
      offset_ = first_id - val;
    }
  }
}

void PoseData::set_skip_line(int val)
{
  skip_line_ = val;
}

QStringList PoseData::header()
{
  return header_;
}

QList<QStringList>& PoseData::data()
{
  return data_;
}

const QList<QStringList>& PoseData::data() const
{
  return data_;
}

int PoseData::columns() const
{
  if (data_.empty() || data_.size() < skip_line_) return 0;
  return data_.at(skip_line_).size();
}

int PoseData::column_type(Type type) const
{
  return column_type_.key(type);
}

PoseData::Type PoseData::column_type(int col) const
{
  return column_type_[col];
}

int PoseData::rows() const
{
  return data_.size() - skip_line_;
}

QString PoseData::data(int row, int col) const
{
  row += skip_line_;

  if (data_.empty()) return QString();
  if (data_.size() <= row || data_.at(row).empty()) return QString();
  if (data_.at(row).size() <= col) return QString();
  
  if (column_type_[col] == ID)
  {
    bool is_number = false;
    int id = data_.at(row).at(col).toInt(&is_number);
    if(is_number)
    {
      return prefix_ + QString::number(id - offset_) + suffix_;
    }
    return prefix_ + data_.at(row).at(col) + suffix_;
  }
  return data_.at(row).at(col);
}

void PoseData::set_prefix(const QString& prefix)
{
  prefix_ = prefix;
}
void PoseData::set_suffix(const QString& suffix)
{
  suffix_ = suffix;
}

void PoseData::set_column_type(int col,Type type)
{
  column_type_[col] = type;
}

void PoseData::RemoveColumnType(int key)
{
  column_type_.remove(key);
}

void PoseData::Clear()
{
  data_.clear();
  last_split_char_ = ' ';
  offset_ = 0;
  skip_line_ = 0;
  prefix_.clear();
  suffix_.clear();
  column_type_.clear();
}

bool PoseData::SplitPose(QChar split_char)
{
  QStringList list;
  for (auto& row : data_)
  {
    //先合并
    QString line;
    for (auto& col : row)
    {      
      line = line + col + last_split_char_;
    }
    line.remove(line.size()-1,1);
    //再分割
    row = line.split(split_char,QString::SkipEmptyParts);
//     row.swap(list);
  }
  last_split_char_ = split_char;
  return true;
}

bool PoseData::empty() const
{
  return data_.empty();
}
