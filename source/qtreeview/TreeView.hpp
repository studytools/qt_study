#ifndef TREEVIEW_HPP
#define TREEVIEW_HPP

#include <QtGui>
#include <QTreeView>

class TreeView :public QTreeView
{
public:
  TreeView();
  void iterateOverItems();
  QList<QStandardItem*> returnTheItems();
private:
  QStandardItemModel *model;
};

#endif