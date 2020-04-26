#include "mainwidget.h"

#include <QApplication>
#include <QStackedWidget>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //qApp->setStyleSheet("");

    MainWidget window;
    window.setWindowTitle("LOGIC EXPRESSION GENERATOR");
    window.show();

    return a.exec();
}
