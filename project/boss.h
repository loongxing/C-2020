#ifndef BOSS_H
#define BOSS_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"

class gameControl;

class boss : public QGraphicsItem
{
public:
    boss(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void bossDie();
    void bossLifeChange(int s);
    void handleCollisions();
    void bossAddStop();
    void NewBoss();
    void bossStart();
    void bossStart(int s);
    bool bossIsActive();

//private:
    int boss_x,boss_y;
    int Blood,cut,BLOOD;
    QLinearGradient *gradient; //渐变色
    QPixmap pix;
    gameControl &controller;
    bool firstBoss;
    QTimer addBos;
};

#endif
