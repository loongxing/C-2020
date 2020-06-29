#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "config.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
class gameControl;

class equipment : public QGraphicsItem
{
public:
    equipment(gameControl & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void handleCollisions();
private:
    QPixmap pixMap;
    gameControl &controller;
};

#endif
