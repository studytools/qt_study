#include <QApplication>
#include <QStringList>

#include "TreeView.hpp"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  TreeView view;
  view.iterateOverItems();
  view.show();

  return app.exec();
}
