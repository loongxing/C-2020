#include "gamecontrol.h"
#include "view.h"
#include "config.h"
#include "logindlg.h"
#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{
    //QResource::registerResource(GAME_RES_PATH);
    QApplication a(argc, argv);
    LogInDlg dlg;
    dlg.show();
    if(dlg.exec() == QDialog::Accepted){
        view v;
        v.show();
        return a.exec();
    }
    return 0;
}
