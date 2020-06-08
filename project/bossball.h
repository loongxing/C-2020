#ifndef BOSSBALL_H
#define BOSSBALL_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"
#include"boss.h"


class gameControl;
class boss;
class bossball : public QGraphicsItem
{
public:
    bossball(gameControl &control,boss &b);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void setAngle(qreal angle);
private:
    double bossball_x[15],bossball_y[15];
    QPixmap pix[15];
    QPointF vector;
    gameControl &controller;
    boss &bos;
    bool shoot[3];
    int qu;
};

#endif
