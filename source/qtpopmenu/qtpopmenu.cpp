#include "qtpopmenu.hpp"

myTreeWidget::myTreeWidget(QWidget *parent)
  : QTreeWidget(parent)
{
  openfileAct_ = new QAction(tr("&Open"),this);
  connect(openfileAct_, &QAction::triggered, this, &myTreeWidget::onOpenFile);

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, &QTreeWidget::customContextMenuRequested,
          this, &myTreeWidget::onCustomContextMenuRequested);
}

myTreeWidget::~myTreeWidget()
{
}

void myTreeWidget::onCustomContextMenuRequested(const QPoint& pos) {
  printf("hi\n");
  QTreeWidgetItem* item = itemAt(pos);

  if(item) {
    // Note: We must map the point to global from the viewport to
    // account for the header.
    showContextMenu(item, viewport()->mapToGlobal(pos));
  }
}

void myTreeWidget::onOpenFile()
{
  QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));
}

void myTreeWidget::showContextMenu(QTreeWidgetItem* item, const QPoint& globalPos) {
  QMenu menu;

  switch(item->type()) {
  case BLOCK:
  menu.addAction(openfileAct_);
  break;

  case PHOTO:
  menu.addAction("his is a type PHOTO");
  break;

  case PHOTOS:
  menu.addAction("This is a type 2");
  break;
  }

  menu.exec(globalPos);
}

MainWidget::MainWidget(QWidget *parent)
{
  layout_ = new QHBoxLayout;
  setLayout(layout_);

  tree_ = new myTreeWidget;
  QTreeWidgetItem *cities = new QTreeWidgetItem(myTreeWidget::BLOCK);
  cities->setText(0, tr("Cities"));
  QTreeWidgetItem *osloItem = new QTreeWidgetItem(cities,myTreeWidget::PHOTO);
  osloItem->setText(0, tr("Oslo"));
  tree_->addTopLevelItem(cities);

  QTreeWidgetItem *cities1 = new QTreeWidgetItem(myTreeWidget::PHOTOS);
  cities1->setText(0, tr("Cities1"));

  tree_->addTopLevelItem(cities1);

  layout_->addWidget(tree_);
  test1Act_ = new QAction(tr("test1"),this);
}

