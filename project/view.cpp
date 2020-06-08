#include "view.h"
#include "config.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>

view::view(QWidget *parent) : QGraphicsView(parent)
{
    QMediaPlayer * player = new QMediaPlayer(this);     //背景音乐
    QMediaPlaylist * list = new QMediaPlaylist(this);   //音乐列表
    list->addMedia(QUrl("qrc:/music/res/bg.wav"));
    list->setCurrentIndex(0);
    list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);   //单曲循环
    player->setPlaylist(list);  //播放器得到列表
    player->play(); //播放
    //QSound::play(SOUND_BACKGROUND);

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
    //connect(control, SIGNAL(exitApp()), this, SLOT(close()));
}
