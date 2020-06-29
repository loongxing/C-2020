#include "logindlg.h"
#include "qpainter.h"
#include "rank.h"
#include<QPainter>
#include <QIcon>
#include <QTextEdit>
#include <QDateTime>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QMessageBox>

int myPlaneFullLife;
int level;
int attackStyle;
int difficulty;
QString playerName;//玩家姓名
QString backgroundPath;//地图名字
int gameStyle;//模式
int music;//音乐
int grade;//等级
int hero;//英雄

class Rank;

LogInDlg::LogInDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindlg)
{
    ui->setupUi(this);

    connect(ui->Quit,&QPushButton::clicked,[=](){
        this->close();
    });

    this->setWindowFlags(Qt::FramelessWindowHint);//无上框
    pix = new QPixmap;
    pix->load(START_UI_BG, 0, Qt::AvoidDither|Qt::ThresholdAlphaDither|Qt::ThresholdDither);
    resize(pix->size());
    this->setMask(pix->mask());

    qsrand(QTime::currentTime().msec());
    ui->lineEdit->setText(QString("玩家%1").arg(qrand()%1000000));

    ui->Quit->setFlat(true);//按钮透明
    ui->Help->setFlat(true);
    ui->Ours->setFlat(true);
    ui->rank->setFlat(true);
    ui->Start->setFlat(true);

    QIcon* Icon = new QIcon(GAME_ICON);
    this->setWindowIcon(*Icon);

}

LogInDlg::~LogInDlg()
{
    delete ui;
}
void LogInDlg::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(0, 0, *pix);
}

void LogInDlg::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)//拦截左键
     {
         move(event->globalPos() - this->dragPosition);//定位窗口新位置
         event->accept();
     }
}

void LogInDlg::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)//拦截点击左键动作
      {
          this->dragPosition = event->globalPos() - this->frameGeometry().topLeft(); //计算窗口起始位置并保存
          event->accept();
      }
}

void LogInDlg::on_Start_clicked()
{
    saveBackGroundType();
    saveBackGroundLoop();
    saveLoadMode();
    saveDifficulty();
    savePlayerName();
    savePlaneType();
    accept();
}

void LogInDlg::on_Ours_clicked()
{
    QMessageBox::about(this, tr("关于作者"), tr("2019级软件工程4班\n朱龙兴，陈思杰，肖逸晖\n"));
}

void LogInDlg::on_Help_clicked()
{
    help *Help=new help(this);
    Help->setWindowTitle("Help");
    Help->show();
}

void LogInDlg::on_rank_clicked()
{
    Rank r;
    r.show();
}

//地图类型
void LogInDlg::saveBackGroundType()
{
    QString str=ui->comboBox_3->currentText();
    if(str==tr("青青草原"))     backgroundPath=tr(":/image/res/img_bg_level_1.jpg");
    else if(str==tr("失落城堡"))    backgroundPath=tr(":/image/res/img_bg_level_2.jpg");
    else if(str==tr("西部荒原"))    backgroundPath=tr(":/image/res/img_bg_level_3.jpg");
    else if(str==tr("机械迷城"))    backgroundPath=tr(":/image/res/img_bg_level_4.jpg");
    else if(str==tr("沉沦地狱"))    backgroundPath=tr(":/image/res/img_bg_level_5.jpg");
}

void LogInDlg::savePlaneType()
{
    QString str=ui->Type->currentText();
    if(str==tr("雷霆号"))  hero = 1;
    else if(str==tr("凤凰号"))   hero = 2;
    else if(str==tr("森林号"))   hero = 3;
    else if(str==tr("紫电号"))   hero = 4;
    else if(str==tr("帝皇号"))   hero = 5;
    else if(str==tr("白虎号"))   hero = 7;
}

//改成音乐开关
void LogInDlg::saveBackGroundLoop()
{
    QString str=ui->comboBox_2->currentText();
    if(str == tr("开启")) music = 1;
    else    music=0;
}

//设置模式
void LogInDlg::saveLoadMode()
{
    QString str=ui->comboBox_4->currentText();
    if(str == "冒险模式")   gameStyle = 1;
    else if(str == "无尽模式")   gameStyle = 2;
    else if(str == "无敌模式")   gameStyle = 3;
}

//设置难度
void LogInDlg::saveDifficulty()
{
    QString str=ui->comboBox->currentText();
    if(str == "简单") difficulty=1;
    else if(str == "一般") difficulty=2;
    else if(str == "困难") difficulty=3;
}

void LogInDlg::savePlayerName()
{
    playerName = ui->lineEdit->text();
}
