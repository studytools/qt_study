#include "read_file.hpp"

#include <QFile>

ReadFile::ReadFile(const QString& file_path)
{
  QFile data(file_path);
  if (data.open(QFile::ReadOnly))
  {
    text_stream_ = new QTextStream(&data);
    QString line;
    do {
      line = text_stream_->readLine();
    } while(!line.isNull());
  }
  

}

bool ReadFile::Read(const QString& file_path)
{

  return true;
}
