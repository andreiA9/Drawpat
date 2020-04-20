#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // this shows the MainWindow
    MainWindow w;
    w.show();

    // this processes Messages for the MainWindow
    return a.exec();
}
