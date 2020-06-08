#ifndef ENEMY_H
#define ENEMY_H

#include<QPixmap>
#include<QGraphicsItem>
#include"gamecontrol.h"
#include<QTimer>
#include<QObject>
#include"config.h"
class Enemy :public QGraphicsItem
{
public:
    Enemy(gameControl & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();

private:
    qreal speedX,speedY,rad;
    QPixmap pix;
    gameControl &controller;

};

#endif // ENEMY_H
