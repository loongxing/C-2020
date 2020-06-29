#include"wingman.h"
#include"wingmanbullet.h"
#include "gamecontrol.h"
#include <QPainter>

WingmanBullet::WingmanBullet(gameControl &controller):
    controller(controller)
{
    setData(GI_type,GT_wingManBullet);
    pixMap.load(WINGPLANE_BULLET);
}

QRectF WingmanBullet::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void WingmanBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        painter->scale(0.7, 0.7);
        painter->drawPixmap(0,0, pixMap);
        painter->restore();
    }
}

void WingmanBullet::advance(int phace)
{
    if(!phace) return;
    moveBy(0, -8);
    if(!controller.isInView(pos())){
        controller.removeItem(*this);
    }
}

