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
    QPoint getPoint();

//private:
    int boss_x,boss_y;
    QPixmap pix;
    gameControl &controller;
};

#endif
