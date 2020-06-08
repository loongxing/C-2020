#include "myplanebullet.h"
#include "config.h"
#include <QPainter>

myPlaneBullet::myPlaneBullet(gameControl &control):
    controller(control)
{
    pix.load(":/image/res/bullet_11.png");

    speed = 0;
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
        painter->drawPixmap(QPoint(-w/2,-h/2),pix);
        painter->restore();
    }
}

void myPlaneBullet::advance(int phase)
{
    if(!phase)  return;
    moveBy(0,-speed);//子弹往上走，即x坐标变小
    if(!isInView(pos())){
        controller.removeItem(*this);
    }
}

void myPlaneBullet::setSpeed(int x)
{
    speed = x;
}

bool myPlaneBullet::isInView(const QPointF &p)
{
    return (p.x()<VIEW_WIDTH && p.x()>0) && (p.y()<VIEW_HEIGHT && p.y() >0);
}

