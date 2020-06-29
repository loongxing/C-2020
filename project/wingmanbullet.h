#ifndef WINGMANBULLET_H
#define WINGMANBULLET_H

#include "config.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class gameControl;

class WingmanBullet : public QGraphicsItem
{
public:
    WingmanBullet(gameControl &controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
    gameControl &controller;
};

#endif
