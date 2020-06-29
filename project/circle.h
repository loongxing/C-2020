#ifndef CIRCLE_H
#define CIRCLE_H
#include <QGraphicsItem>
#include <QPainterPath>
#include <QPixmap>
#include <QRectF>
#include "gamecontrol.h"

class gameControl;

class circle : public QGraphicsItem
{
public:
    circle(gameControl &control);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void handleCollision();
private:
    int rad;
    bool statue;
    QPixmap pix;
    gameControl &controller;
    QPainterPath *path;
};

#endif // CIRCLE_H
