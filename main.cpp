#include <QApplication>
#include <QDesktopWidget>
#include "tetrismodel.h"
#include "tetriscontroller.h"
#include "tetrisview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    TetrisView *view = new TetrisView();
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int dx = (myScreenGeometry.width() - view->width()) / 2;
    int dy = (myScreenGeometry.height() - view->height()) / 2;
    view->move(dx, dy);
    view->show();

    return a.exec();
}
