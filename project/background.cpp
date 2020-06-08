#include "background.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>

background::background(gameControl &control):
    controller(control)
{
    posx=0;
    posy=0;
    setPos(0,0);
    //qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();可以读取jpg文件
//    qDebug()<<"222";
    pix.load(GAME_BG);
//    if(pix.isNull()){
//        qDebug()<<"YES";
//    }
}

QRectF background::boundingRect() const
{
    return QRectF(0,0,pix.width(),VIEW_HEIGHT);
}

void background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->save();
    int w = pix.width(),h=pix.height();
    painter->drawPixmap(-5,posy,w,h,pix);
    painter->drawPixmap(-5,posy-h,w,h,pix);
    update();
    painter->restore();
}

void background::advance(int phase)
{
    if(!phase)  return;
    posy+=10;
    if(posy>=pix.height()){
        posy=0;
    }
}
