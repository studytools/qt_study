#ifndef _READ_FILE_HPP_
#define _READ_FILE_HPP_

#include <QTextStream>
#include <QString>

class ReadFile
{
public:
  ReadFile(const QString& file_path);

  bool Read(const QString& file_path);

protected:

private:
  QTextStream* text_stream_;
};

#endif