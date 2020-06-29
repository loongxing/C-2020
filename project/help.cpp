#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::help)
{

    ui->setupUi(this);

    connect(ui->Fly,&QPushButton::clicked,[=](){
        this->close();
    });

}

help::~help()
{
    delete ui;
}
