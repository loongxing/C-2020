#ifndef MYPLANE_H
#define MYPLANE_H
#include <QGraphicsItem>
#include <QPixmap>
#include "gamecontrol.h"

class gameControl;

class myPlane : public QGraphicsItem
{
public:
    myPlane(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void setSpeedX(int x);
    void setSpeedY(int y);
    void setFireStatue(bool statue);
    void fire(int speed);
    void handleCollision();
    void setCircleStatue(bool s);
    bool getCircleStatue();
    void addBulletRain(int );
    int getBUlletRain();
    void addWingPlane(int s);
    int getWingPlane();
    void handleLife(int s);
    int getLife();
    int getHurt();
private:
    QLinearGradient *gradient;//血量线
    gameControl &controller;
    QPixmap pix,pic;
    int speedX,speedY,isFiring;
    bool circleStatue;
    int bulletRain,life,tempCount,flag,wingPlane,idx,hurt,book;
};

#endif // MYPLANE_H
