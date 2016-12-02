#include "widget.h"
#include <QApplication>
#include<QRect>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

  //  app.seWindowIcon(QIcon("mypwd.ico"));
    w.show();
    return a.exec();
}
