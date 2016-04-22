#ifndef _POSE_DATA_HPP_
#define _POSE_DATA_HPP_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTextStream>


class PoseData : public QObject
{
  Q_OBJECT
public:
  enum Type
  {
    UNKNOWN = 0,
    ID,
    LONGITUDE,
    LATITUDE,
    ALTITUDE,
    PITCH,
    ROLL,
    YAW,
  };

  PoseData();

  void set_columns(int val);
  void set_rows(int val);
  void set_offset(int val);
  void set_skip_line(int val);
  void set_prefix(const QString& prefix);
  void set_suffix(const QString& suffix);
  void set_column_type(int col, Type type);
  void RemoveColumnType(int key);
  void Clear();

  QStringList header();
  QList<QStringList>& data();
  const QList<QStringList>& data() const;
  int columns() const;
  int columns(int row);
  int column_type(Type type) const;
  Type column_type(int col) const;
  int rows() const;
  QString data(int row, int col) const;
  bool empty() const;

public slots:
  bool SplitPose(QChar split_char);

private:
  QStringList header_;
  QList<QStringList> data_;
  QChar last_split_char_;
  int offset_;
  int skip_line_;
  int id_width_;
  QString prefix_;
  QString suffix_;
  QMap<int, Type> column_type_;
};

#endif