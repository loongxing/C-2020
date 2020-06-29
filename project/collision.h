#ifndef COLLISION_H
#define COLLISION_H
#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <gamecontrol.h>

class gameControl;

class collision : public QGraphicsItem
{
public:
    collision(gameControl &control);
    QRectF boundingRect() const;
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    void setScale(double sc);
private:
    QVector<QPixmap> pixArr;
    gameControl &controller;
    int idx,cnt;
    double scale;

};

#endif // COLLISION_H
