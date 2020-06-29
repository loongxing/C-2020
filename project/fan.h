#ifndef FAN_H
#define FAN_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"
#include"boss.h"

class gameControl;

class fan : public QGraphicsItem
{
public:
    fan(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void setAngle(qreal angle);
    bool isInView();
private:
    double bossball_x,bossball_y;
    QPointF vector;
    QPixmap pix;
    gameControl &controller;
    int ji;
    qreal rad;
};

#endif
