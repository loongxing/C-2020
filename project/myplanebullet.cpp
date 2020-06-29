#include "myplanebullet.h"
#include "config.h"
#include <QPainter>

myPlaneBullet::myPlaneBullet(gameControl &control):
    controller(control)
{
    setData(GI_type, GT_myplaneBall);
    speed = 0;
    idx=1;
    if(attackStyle ==1 ){
        pix.load(MYPLANE_BULLET);
    }
    else if(attackStyle == 2){
        pix.load(":/image/res/bullet_9.png");
    }
    else if(attackStyle == 3){
        pix.load(QString(":/image/res/sucai-%1.png").arg(idx));
    }

}

QRectF myPlaneBullet::boundingRect() const
{
    int w = pix.width(), h = pix.height();
    return QRectF(-w/2,-h/2,w,h);
}

void myPlaneBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pix.isNull()){
        painter->save();
        int w = pix.width(), h = pix.height();
        if(boundingRect() == QRectF(-15,-15,30,30)) painter->scale(3,3);
        painter->drawPixmap(QPoint(-w/2,-h/2),pix);
        painter->restore();
    }
}

void myPlaneBullet::advance(int phase)
{
    if(!phase)  return;
    idx=idx%5+1;
    moveBy(0,-speed);//子弹往上走，即x坐标变小
    if(!controller.isInView(pos())){
        controller.removeItem(*this);
    }
}

void myPlaneBullet::setSpeed(int x)
{
    speed = x;
}

