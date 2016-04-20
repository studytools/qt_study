#include <QApplication>
#include <QStringList>
#include <QDialog>
#include <QDebug>

#include "qtpopmenu.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  MainWidget* main_widget = new MainWidget;
  main_widget->show();
  return app.exec();
}
