#include "rank.h"
#include "config.h"
#include <QDebug>
#include <QDialog>
#include <QDataStream>
#include <QTextStream>
#include <QtAlgorithms>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTableView>
#include <iostream>

Rank::Rank(QObject *parent) :
    QObject(parent),
    file("rank.dat")
{
    if(!file.open(QIODevice::ReadWrite|QIODevice::Text))
        qDebug() << "Can't open file";
    read();
}

Rank::~Rank()
{
    file.close();
}

void Rank::read()
{
    list.clear();
    file.seek(0);
    QTextStream in(&file);
    while(!in.atEnd()){
        node q;
        in>>q.name>>q.score>>q.time>>q.model;
        list.push_back(q);
    }
}

void Rank::write()
{
    file.resize(0);
    file.seek(0);
    QTextStream out(&file);
    foreach(node q, list){
        out<<q.name<<" "<<q.score<<" "<<q.time<<" "<<q.model<<" ";
    }
}

void Rank::add(node q)
{
    list.push_back(q);
    write();
}

void Rank::show()
{
    read();
    QList<node> showList = list;
    std::sort(showList.begin(),showList.end(),cmp);
    QStandardItemModel *model = new QStandardItemModel(showList.size(),3);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("玩家姓名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("玩家得分")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("时间")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("模式")));
    for(int i = 0; i < list.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(showList[i].name));//设置元素
        model->setItem(i, 1, new QStandardItem(showList[i].score));
        model->setItem(i, 2, new QStandardItem(showList[i].time));
        model->setItem(i, 3, new QStandardItem(showList[i].model));
    }
    QTableView * view = new QTableView;//声明可视化的视图
    view->setModel(model);
    view->setFixedSize(700, 400);
    view->setWindowTitle("飞机大战得分排行榜");
    view->setColumnWidth(2, 200);
    view->setWindowIcon(QIcon(GAME_ICON));
    view->show();
}

int Rank::getRank(node q)
{
    QList<node> rankList = list;
    rankList.push_back(q);
    std::sort(rankList.begin(),rankList.end(),cmp);
    int cnt=0;
    foreach(node x, rankList){
        cnt++;
        if(x.name == q.name && x.score == q.score){
            return cnt;
        }
    }
    return list.size();
}

bool Rank::cmp(const node x, const node y)
{
    return x.score.toInt()>y.score.toInt();
}
