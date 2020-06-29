#ifndef LASER_H
#define LASER_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"

class gameControl;

class laser : public QGraphicsItem
{
public:
    laser(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void handleCollision();
private:
    gameControl &controller;
    int cnt,idx,cur,posx,count,act;
    double scale;
    QPixmap pix,pic,gra;
};

#endif // LASER_H
