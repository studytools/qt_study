#ifndef _READ_FILE_HPP_
#define _READ_FILE_HPP_

#include <QTextStream>
#include <QString>

#include "pose_data.hpp"

class ReadWriteFiles
{
public:
  static bool ReadPoseFile(const QString& file_path,const QString& split_char,
                          PoseData& pose_data);

  static bool WritePoseFile(
    const QString& file_path,
    const PoseData& pose_data);

  static bool WritePoseFileKML(
    const QString& file_path,
    const PoseData& pose_data);
};


#endif
