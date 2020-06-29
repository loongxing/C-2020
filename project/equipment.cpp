#include "equipment.h"
#include "gamecontrol.h"
#include <QPainter>


equipment::equipment(gameControl &control):
    controller(control)
{
    setData(GI_type,GT_equipment);
    pixMap.load(EQUIPMENT);
//    if(pixMap.isNull())
//        qDebug()<<"Yws";
}

QRectF equipment::boundingRect() const
{
    int w = pixMap.width(), h = pixMap.height();
    return QRectF(-w/2, -h/2, w, h);
}

void equipment::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    if(!pixMap.isNull()) {
        painter->save();
        int w = pixMap.width(), h = pixMap.height();
        painter->drawPixmap(QPoint(-w/2, -h/2), pixMap);
        painter->restore();
    }
}

void equipment::advance(int phace)
{
    if(!phace) return;
    moveBy(0, 12);
    if(!controller.isInView(pos())){
        controller.removeItem(*this);
    }
}

