#ifndef BOSSBALL_H
#define BOSSBALL_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"
#include"boss.h"


class gameControl;
class bossball : public QGraphicsItem
{
public:
    bossball(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void setAngle(qreal angle);
    bool isInView();
    void setBBX(int);
    void setBBY(int);
private:
    double bossball_x,bossball_y;
    QPointF vector;
    QPixmap pix;
    gameControl &controller;
    int ji;
};

#endif
