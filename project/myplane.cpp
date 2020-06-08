#include "myplane.h"
#include "config.h"
#include <QPainter>

myPlane::myPlane(gameControl &control):
    controller(control)
{
    pix.load(MYPLANE);

    speedX = 0;
    speedY = 0;
    isFiring = 0;

    //血条渐变
    gradient = new QLinearGradient(QPoint(-50, -50), QPoint(50, 50));//渐变色
    gradient->setColorAt(0, Qt::red);
    gradient->setColorAt(0.2, Qt::yellow);
    gradient->setColorAt(0.7, Qt::blue);
    gradient->setColorAt(1, Qt::green);
}

QRectF myPlane::boundingRect() const
{
    //注意中心点是图片中央
    qreal w = pix.width(), h = pix.height();
    return QRectF(-w/2, -h/2, w, h);
}

void myPlane::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pix.isNull()) {
        painter->save();//保存Qpainter的状态
        //qreal sc = qMin((1.0+controller.getRank()/10.0), 2.0);//取最小，实际是血量的变厚
        //painter->scale(0.6 * sc, 0.6 * sc);//变化坐标轴刻度，实际作用可理解为图片的放大与缩小，作用是实现飞机的升级
        painter->scale(0.6 * 2.0, 0.6 * 2.0);
        int w = pix.width(), h = pix.height();

        //飞机出现
        painter->drawPixmap(QPoint(-w/2, -h/2), pix);

        //血条出现
        painter->setBrush(*gradient);//Brush画刷，用于填充颜色

        //血条成比例
        //painter->drawRect(-w/2, -h/2 - 10, qMin(w*controller.getMyPlaneLife()/myPlaneFullLife, w), 8);
        painter->drawRect(-w/2, -h/2 - 10, w , 8);
        painter->restore();//通常与save配套使用，用于恢复成保存的状态
    }

}

void myPlane::advance(int phase)
{
    if(!phase)  return;
    setPos(pos().x()+speedX,pos().y()+speedY);
    if(pos().x() < pix.width()/2) setPos(pix.width()/2, pos().y());
    if(pos().x() > VIEW_WIDTH-pix.width()/2) setPos(VIEW_WIDTH-pix.width()/2, pos().y());
    if(pos().y() < pix.height()/2) setPos(pos().x(), pix.height()/2);
    if(pos().y() > VIEW_HEIGHT-pix.height()/2) setPos(pos().x(), VIEW_HEIGHT-pix.height()/2);

    if(isFiring){
        if(isFiring % 7 ==  1)  fire(BULLET_SPEED);//取余保证长按发射键不会高次数发射子弹
        isFiring++;
    }
}

void myPlane::setSpeedX(int x)
{
    speedX = x;
}

void myPlane::setSpeedY(int y)
{
    speedY = y;
}

void myPlane::setFireStatue(bool statue)
{
    if(isFiring ==0 && statue){
        isFiring = 1;
    }
    else if(isFiring > 0 && !statue){
        isFiring = 0;
    }
}

void myPlane::fire(int speed)
{
    int x=pos().x(),y=pos().y()-pix.height()/2;
    controller.myPlaneShoot(QPointF(x,y),speed);
}
