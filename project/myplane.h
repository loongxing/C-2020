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
private:
    QLinearGradient *gradient;//血量线
    gameControl &controller;
    QPixmap pix;
    int speedX,speedY,isFiring;
};

#endif // MYPLANE_H
