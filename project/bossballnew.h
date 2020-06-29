#ifndef BOSSBALLNEW_H
#define BOSSBALLNEW_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"
#include"boss.h"


class gameControl;
class bossBallNew : public QGraphicsItem
{
public:
    bossBallNew(gameControl &control);
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
    bool pass;
    int ji;
};

#endif
