#include"boss.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>

boss::boss(gameControl &control):
    controller(control)
{
    pix.load(BOSS_PIX);
    if(pix.isNull()){
        qDebug()<<"YES";
    }
    boss_x=VIEW_WIDTH/2-pix.width()/2;
    boss_y=-pix.height();
    setPos(0,0);
    //qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();可以读取jpg文件
    qDebug()<<"222";

}

QRectF boss::boundingRect() const
{
    return QRectF(boss_x,boss_y,pix.width(),pix.height());
}

void boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    painter->save();
    int w = pix.width();
    painter->drawPixmap(boss_x,boss_y,pix);
    update();
    painter->restore();
}

void boss::advance(int phase)
{
    if(!phase)  return;
    if(boss_y<0)         //出场
        boss_y+=2;

    if(boss_x<1)        //1用我的飞机坐标代替
        boss_x+=2;
    if(boss_x>1)
        boss_x-=2;


}


