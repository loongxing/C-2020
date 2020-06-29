#include"bossball.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>
#include<QThread>

bossball::bossball(gameControl &control):
    controller(control)
{
    setData(GI_type,GT_bossBall);
    pix.load(BOSSBALL);
    bossball_x=100;
    bossball_y=100;
}

QRectF bossball::boundingRect() const
{
    int w=pix.width();int h=pix.height();
    return QRectF(-w/2,-h/2,w,h);

}

void bossball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);Q_UNUSED(widget);
    painter->save();
    painter->scale(0.7, 0.7);
    int w=pix.width();int h=pix.height();
    painter->drawPixmap(-w/2,-h/2, pix);
    painter->restore();
}

void bossball::advance(int phase)
{
    if(!phase) return;
    moveBy(-vector.y() * 4, -vector.x() * 4);
    if(isInView()){
        controller.removeItem(*this);
    }
}

void bossball::setAngle(qreal angle)
{
    qreal rad = (angle*3.1415926)/180.0;
    vector.setX(-cos(rad));
    vector.setY(sin(rad));
}

bool bossball::isInView()
{
        if(pos().x()<0||pos().x()>VIEW_WIDTH||pos().y()>VIEW_HEIGHT)
        return true;
        return false;

}
