#include"bossball.h"
#include "config.h"
#include <QPainter>
#include <QDebug>
#include <QRectF>
#include <QImageReader>
#include <QString>
#include <QPixmap>
#include<QThread>

bossball::bossball(gameControl &control,boss &b):
    controller(control)
   ,bos(b)
{
    for(int i=0;i<3;i++)
        shoot[i]=false;     //false 在屏幕
    for(int i=0;i<15;i++)
    {
    bossball_x[i]=bos.boss_x+bos.pix.width();
    bossball_y[i]=bos.boss_y+bos.pix.height();
    }
//    setPos(0,0);
    //qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();可以读取jpg文件
    qDebug()<<"222";
    for(int i=0;i<15;i++)
    pix[i].load(BOSSBALL);
    if(pix[0].isNull()){
        qDebug()<<"YES";
    }
}

QRectF bossball::boundingRect() const
{
    return QRectF(0,0,bos.pix.width(),bos.pix.height());

}

void bossball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);

    painter->save();
//第一波
    if(shoot[0]==true){
        for(int i=0;i<5;i++)
        {
        bossball_x[i]=bos.boss_x+bos.pix.width()/2;
        bossball_y[i]=bos.boss_y+bos.pix.height();
        shoot[0]=false;
        }
    }

    if(!shoot[0])
        for(int i=0;i<5;i++)
        {
            painter->drawPixmap(int(bossball_x[i]),int(bossball_y[i]),pix[i]);
        }
//第二波
    if(shoot[1]==true){
        for(int i=5;i<10;i++)
        {
        bossball_x[i]=bos.boss_x+bos.pix.width()/2;
        bossball_y[i]=bos.boss_y+bos.pix.height();
        shoot[1]=false;
        }
    }

    if(!shoot[2])
        for(int i=5;i<10;i++)
        {
            painter->drawPixmap(int(bossball_x[i]),int(bossball_y[i]),pix[i]);
        }

//第三波
    if(shoot[2]==true){
        for(int i=10;i<15;i++)
        {
        bossball_x[i]=bos.boss_x+bos.pix.width()/2;
        bossball_y[i]=bos.boss_y+bos.pix.height();
        shoot[2]=false;
        }
    }

    if(!shoot[2])
        for(int i=10;i<15;i++)
        {
            painter->drawPixmap(int(bossball_x[i]),int(bossball_y[i]),pix[i]);
        }


    update();









    painter->restore();
}

void bossball::advance(int phase)
{
    if(!phase)  return;
    if(!shoot[0]){
    bossball_x[0]-=1*bossBall_speed;
    bossball_y[0]+=sqrt(3)*bossBall_speed;
    bossball_x[1]-=0.5176*bossBall_speed;
    bossball_y[1]+=1.9319*bossBall_speed;
    bossball_y[2]+=2*bossBall_speed;
    bossball_x[3]+=1*bossBall_speed;
    bossball_y[3]+=sqrt(3)*bossBall_speed;
    bossball_x[4]+=0.5176*bossBall_speed;
    bossball_y[4]+=1.9319*bossBall_speed;}
    for(int i=0,j=0;i<5;i++)
    {
    if(bossball_x[i]>VIEW_WIDTH||bossball_x[i]<0||bossball_y[i]>VIEW_HEIGHT)
        j++;
    if(j==5)
        {
            shoot[0]=true;qu=1;
        }
    }

    //延时一波





    if(!shoot[1]){
    bossball_x[5]-=1*bossBall_speed;
    bossball_y[5]+=sqrt(3)*bossBall_speed;
    bossball_x[6]-=0.5176*bossBall_speed;
    bossball_y[6]+=1.9319*bossBall_speed;
    bossball_y[7]+=2*bossBall_speed;
    bossball_x[8]+=1*bossBall_speed;
    bossball_y[8]+=sqrt(3)*bossBall_speed;
    bossball_x[9]+=0.5176*bossBall_speed;
    bossball_y[9]+=1.9319*bossBall_speed;}
    for(int i=5,j=0;i<10;i++)
    {
    if(bossball_x[i]>VIEW_WIDTH||bossball_x[i]<0||bossball_y[i]>VIEW_HEIGHT)
        j++;
    if(j==5){
        shoot[1]=true;qu=1;}
    }


//    if(qu==1)
//    {
//        Sleep(2000);
//        qu=0;
//    }


    if(!shoot[2]){
    bossball_x[10]-=1*bossBall_speed;
    bossball_y[10]+=sqrt(3)*bossBall_speed;
    bossball_x[11]-=0.5176*bossBall_speed;
    bossball_y[11]+=1.9319*bossBall_speed;
    bossball_y[12]+=2*bossBall_speed;
    bossball_x[13]+=1*bossBall_speed;
    bossball_y[13]+=sqrt(3)*bossBall_speed;
    bossball_x[14]+=0.5176*bossBall_speed;
    bossball_y[14]+=1.9319*bossBall_speed;}
    for(int i=10,j=0;i<15;i++)
    {
    if(bossball_x[i]>VIEW_WIDTH||bossball_x[i]<0||bossball_y[i]>VIEW_HEIGHT)
        j++;
    if(j==5){
        shoot[2]=true;qu=1;}
    }


}
