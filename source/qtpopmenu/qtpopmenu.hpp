#ifndef QTPOPMENU_HPP_
#define QTPOPMENU_HPP_

#include <iostream>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>
#include <QFileDialog>

class myTreeWidget: public QTreeWidget
{
  Q_OBJECT

public:
  enum ItemType
  {
    BLOCK = QTreeWidgetItem::UserType,
    PHOTOS,
    PHOTO,
    FEATURE_MATCH,
    PHOTO_ORIENTATION,
    POINT_CLOUD,
    SURFACE_MODEL,
    DEM,
    TEXTURE,
    DOM
  };

  myTreeWidget(QWidget *parent = 0);
  ~myTreeWidget();
private slots:
  void onCustomContextMenuRequested(const QPoint& pos);
  void onOpenFile();

private:
  void showContextMenu(QTreeWidgetItem* item, const QPoint& globalPos);



private:
  QAction *openfileAct_;
};

class MainWidget: public QWidget
{
  Q_OBJECT
public:
  MainWidget(QWidget *parent = NULL);

private:
  myTreeWidget *tree_;
  QHBoxLayout *layout_;
  QAction *test1Act_;
  QMenu *popMenu_;
};



#endif