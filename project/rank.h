#ifndef RANK_H
#define RANK_H

#include <QObject>
#include <QString>
#include <QFile>

struct node{
    QString name;
    QString score;
    QString time;
    QString model;
};

class Rank : public QObject
{
    Q_OBJECT
public:
    explicit Rank(QObject *parent = nullptr);
    ~Rank();
    void read();
    void write();
    void add(node q);
    void show();
    int getRank(node q);
    static bool cmp(const node x,const node y);
//    static bool cmp(const node &x,const node &y);
private:
    QFile file;
    QList<node> list;
signals:

};

#endif // RANK_H
