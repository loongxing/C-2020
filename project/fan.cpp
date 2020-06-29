#include"fan.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>
#include<QThread>

fan::fan(gameControl &control):
    controller(control)
{
    ji=0;
    setData(GI_type,GT_bossBall);
    pix.load(BOSS_FAN);
    bossball_x=100;
    bossball_y=100;
    rad=30;
}

QRectF fan::boundingRect() const
{
    int w=pix.width();int h=pix.height();
    return QRectF(-w/2,-h/2,w,h);

}

void fan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    painter->save();
    painter->rotate(rad);
    //painter->scale(0.1, 0.1);
    int w=pix.width();int h=pix.height();
    painter->drawPixmap(-w/2,-h/2, pix);
    painter->restore();
}

void fan::advance(int phase)
{
    if(!phase) return;
    moveBy(-vector.y() * 4, -vector.x() * 4);

    if((pos().x()-pix.width()/2)<0)
        {
            ji++;
            vector.setY(-vector.y());
        }
    if((pos().x()+pix.width()/2)>VIEW_WIDTH)
        {
            ji++;
            vector.setY(-vector.y());
        }

    if((pos().y()+pix.height()/2)>VIEW_HEIGHT)
        {
            ji++;
            vector.setX(-vector.x());
        }

    if(isInView()){
        controller.removeItem(*this);
    }

    rad+=30;
    if(rad==360)
        rad=0;

}

void fan::setAngle(qreal angle)
{
    qreal q = (angle*3.1415926)/180.0;
    vector.setX(-cos(q));
    vector.setY(sin(q));
}

bool fan::isInView()
{
        if(pos().y()<0 || ji==3)
        return true;
        return false;

}
