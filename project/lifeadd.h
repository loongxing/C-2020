#ifndef LIFEADD_H
#define LIFEADD_H

#include "config.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
class gameControl;

class lifeAdd : public QGraphicsItem
{
public:
    lifeAdd(gameControl & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap;
    gameControl &controller;
};

#endif
