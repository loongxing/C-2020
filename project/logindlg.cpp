#include "logindlg.h"
#include "qpainter.h"
#include<QPainter>
#include <QIcon>
#include <QTextEdit>
#include <QDateTime>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QMessageBox>

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
    ui->lineEdit->setText(QString("玩家%1").arg(qrand()%30));

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
    accept();
}

void LogInDlg::on_Ours_clicked()
{
    QMessageBox::about(this, tr("关于作者"), tr("杰哥nb！"));
}

void LogInDlg::on_Help_clicked()
{

}

void LogInDlg::on_rank_clicked()
{

}

void LogInDlg::saveBackGroundType()
{
    QString str=ui->comboBox_3->currentText();

}

void LogInDlg::saveBackGroundLoop()
{
    QString str=ui->comboBox_2->currentText();
}

void LogInDlg::saveLoadMode()
{
    QString str=ui->comboBox_4->currentText();
}

void LogInDlg::saveDifficulty()
{
    QString str=ui->comboBox->currentText();
}

void LogInDlg::savePlayerName()
{

}
