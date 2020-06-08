#include "enemy.h"
#include<QString>
#include<QPainter>
#include<cmath>
#include<QPointF>
Enemy::Enemy(gameControl &controller):
    speedX(qrand()%7-3),
    speedY(7),
     controller(controller)
{
    QString str=QString(EnemyPath).arg(qrand()%5+1);
    pix.load(str);
    rad = -(atan(speedX*1.0/speedY) / 3.1415926) * 180.0;

}

QRectF Enemy::boundingRect() const
{
    int w = pix.width(), h = pix.height();
    return QRectF(-w/2, -h/2, w, h);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pix.isNull())
    {
    painter->save();
    painter->rotate(rad);
    int w = pix.width(), h = pix.height();
    painter->drawPixmap(-w/2,-h/2,pix);
    painter->restore();
    }

}

void Enemy::advance(int phace)
{
    if(!phace)return;
    moveBy(speedX,speedY);
//    if(!isInView(pos()))
//        controller.removeItem(*this);

}

void Enemy::handleCollisions()
{

}
