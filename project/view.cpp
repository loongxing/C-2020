#include "view.h"
#include "config.h"
#include <QDir>

view::view(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setMinimumSize(VIEW_WIDTH + 10, VIEW_HEIGHT + 10);  //设置窗口
    setMaximumSize(VIEW_WIDTH + 10, VIEW_HEIGHT + 10);

    Icon = new QIcon(GAME_ICON);
    this->setWindowIcon(*Icon);

    setWindowTitle("C++实训飞机大战");

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,VIEW_WIDTH,VIEW_HEIGHT);
    setScene(scene);

    control = new gameControl(scene, this);
    connect(control, SIGNAL(exitApp()), this, SLOT(close()));
}
