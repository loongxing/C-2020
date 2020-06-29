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
    setData(GI_type, GT_enemy);
    QString str=QString(ENEMY_PATH).arg(qrand()%5+1);
    pix.load(str);
    rad = -(atan(speedX*1.0/speedY) / 3.1415926) * 180.0;
    count =30;
    if(str== QString(ENEMY_PATH).arg(1)||str==QString(ENEMY_PATH).arg(2)||str == QString(ENEMY_PATH).arg(3))
        Blood=1+level/3;
    else
        Blood=2+level/2;
    BLOOD=Blood;
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
        painter->drawPixmap(QPoint(-w/2, -h/2),pix);
        painter->restore();
    }
}

void Enemy::advance(int phace)
{
    if(!phace)return;
    moveBy(speedX,speedY);
    if(!controller.isInView(pos()))
        controller.removeItem(*this);
    count--;
    if(count == 1)
    {
        controller.shootBall(pos());
        count =30;
    }
    handleCollisions();
}

void Enemy::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *item, collisions) {
        if(item->data(GI_type) == GT_myplaneBall && item->boundingRect() != QRectF(-15,-15,30,30)) {
            Blood+=controller.getMyPlaneHurt();
            controller.removeItem(*item);//子弹
            if(Blood <= 0){
                controller.removeItem(*this);
                int s=100+qrand()%20;
                controller.updataScore(s);
                controller.addText(pos(),s);
                controller.startCollision(pos());
                if(qrand()%100 <10) controller.addLife(pos());
            }
        }
        if(item->data(GI_type) == GT_myplaneBall && item->boundingRect() == QRectF(-15,-15,30,30)) {
            Blood+=controller.getMyPlaneHurt();
            controller.removeItem(*item);
            controller.handleBomb(item->pos());
            if(Blood <= 0){
                controller.removeItem(*this);
                int s=100+qrand()%20;
                controller.updataScore(s);
                controller.addText(pos(),s);
            }
        }
        if(item->data(GI_type) == GT_wingManBullet){
            Blood--;
            controller.removeItem(*item);//子弹消失
            if(Blood <= 0){
                controller.removeItem(*this);//自己爆炸
                int s=50+qrand()%20;
                controller.updataScore(s);
                controller.addText(pos(),s);
                controller.startCollision(pos());
                if(qrand()%100 <20) controller.addLife(pos());
            }
        }
        if(item->data(GI_type) == GT_circle){
            controller.removeItem(*this);//自己爆炸
            controller.startCollision(pos());//敌机爆炸，无加分
            return;
        }
    }
}
