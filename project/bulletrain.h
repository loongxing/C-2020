#ifndef BULLETRAIN_H
#define BULLETRAIN_H
#include <QGraphicsItem>
#include <gamecontrol.h>
#include <QPixmap>

class gameControl;

class bulletRain : public QGraphicsItem
{
public:
    bulletRain(gameControl &control, int num);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void advance(int phase);
    void setSpeed(int s);
private:
    int number,speed;
    gameControl &controller;
    QPixmap pix;
    const double PEI=3.14159;
};

#endif // BULLETRAIN_H
