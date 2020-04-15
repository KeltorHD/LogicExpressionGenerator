#include "mainwidget.h"

#include <QApplication>
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget window;
    window.setWindowTitle("LOGIC EXPRESSION GENERATOR");
    window.show();



    return a.exec();
}
