#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include "gamecontrol.h"

class gameControl;

class background : public QGraphicsItem
{
public:
    background(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
private:
    int posx,posy;
    QPixmap pix;
    gameControl &controller;
};

#endif // BACKGROUND_H
