// #include <vld.h> 

#include "iostream"

#include <QApplication>
#include <QSurfaceFormat>

#include <QImageReader> 
#include <QImage> 

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QImageReader image_reader("Lenna.tif");

  QImage image;
  if(image_reader.read(&image))
  {
    for(int y = 0; y < image.height(); y++)
    {
      for(int x = 0; x < image.width(); x++)
      {
        QRgb height = image.pixel(x,y);
        std::cout << "height:" << height << "\n";
      }
    }
  }

  return app.exec();
}
