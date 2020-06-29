#ifndef ENEMYBALL_H
#define ENEMYBALL_H


#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class gameControl;

class EnemyBall : public QGraphicsItem
{
public:
    EnemyBall(gameControl & controller);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phace);
    void setDir();
//    bool isInView(const QPointF & rhs);//判断是否在view
private:
    int dirx, diry;
    QPointF vector;
    QPixmap pixMap;
    gameControl &controller;
};

#endif // BALL_H
