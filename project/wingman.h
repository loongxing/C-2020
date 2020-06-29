#ifndef WINGMAN_H
#define WINGMAN_H
#include "config.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class gameControl;


class WingMan : public QGraphicsItem
{
public:
    WingMan(gameControl &control);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
private:
    QPixmap pixMap,pixMyplane;
    int cnt;
    gameControl &controller;

};

#endif
