#ifndef MYPLANEBULLET_H
#define MYPLANEBULLET_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QRectF>
#include <QPointF>
#include "gamecontrol.h"

class gameControl;

class myPlaneBullet : public QGraphicsItem
{
public:
    myPlaneBullet(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void setSpeed(int x);
    bool isInView(const QPointF &p);
private:
    QPixmap pix;
    gameControl &controller;
    int speed;
};

#endif // MYPLANEBULLET_H
