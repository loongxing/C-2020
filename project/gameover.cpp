#include "gameover.h"
#include"qpainter.h"
#include<QPainter>
#include <QIcon>
#include <QTextEdit>
#include <QDateTime>
#include <QPalette>
#include <QString>
#include"rank.h"
#include <QDebug>
#include <QMessageBox>
#include <QProcess>
#include <QDir>

GameOver::GameOver(QWidget *parent):
  QDialog(parent),
  ui(new Ui::GameOver)
{
    ui->setupUi(this);
    connect(ui->Quit, SIGNAL(clicked(bool)), this, SLOT(close()));
    // 设置背景图片
    this->setWindowFlags(Qt::FramelessWindowHint);
    pix = new QPixmap;
    pix->load(GameOver_UI_BG, 0, Qt::AvoidDither|Qt::ThresholdAlphaDither|Qt::ThresholdDither);
    resize(pix->size());


      QIcon* Icon = new QIcon(GAME_ICON);//游戏图标
      this->setWindowIcon(*Icon);


}
GameOver::~GameOver()
{
    delete ui;
}

void GameOver::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.drawPixmap(0, 0, *pix);
}

void GameOver::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)//拦截左键
     {
         move(event->globalPos() - this->dragPosition);//定位窗口新位置
         event->accept();
     }
}

void GameOver::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)//拦截点击左键动作
      {
          this->dragPosition = event->globalPos() - this->frameGeometry().topLeft(); //计算窗口起始位置并保存
          event->accept();
      }
}

void GameOver::on_pushButton_2_clicked()
{
    Rank rank;
    rank.show();
}

void GameOver::on_pushButton_clicked()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}
