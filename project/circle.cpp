#include "circle.h"
#include "config.h"
#include <QPainter>

circle::circle(gameControl &control):
    controller(control)
{
    setData(GI_type,GT_circle);
    rad = 0;
    pix.load(CIRCLE_PIXMAP);
    qreal w=pix.width(),h=pix.height();
    path = new QPainterPath;
    path->addEllipse(QRectF(-w/2,-h/2,w,h));
}

QRectF circle::boundingRect() const
{
    qreal w=pix.width(),h=pix.height();
    return QRectF(-w/2,-h/2,w,h);
}

QPainterPath circle::shape() const
{
    return *path;
}

void circle::advance(int phase)
{
    if(!phase)  return;
    rad = (rad+15)%360;
    handleCollision();
}

void circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    if(!pix.isNull()){
        painter->save();
        qreal w=pix.width(),h=pix.height();
        painter->rotate(rad);
        painter->drawPixmap(QPointF(-w/2,-h/2),pix);
        painter->restore();
    }
}

void circle::handleCollision()
{
    QList<QGraphicsItem*> collisions = collidingItems();
    foreach(QGraphicsItem * item, collisions){
        auto t = item->data(GI_type);
        if( t == GT_bossBall || t == GT_enemy || t == GT_enemyBall){
            controller.removeItem(*item);
            //护盾杀敌不加积分
            controller.startCollision(item->pos());
            return;
        }
    }
}
