#include "MainWindow/MainWindow.h"

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


// FOARTE IMPORTANT
// ca sa ai include DIRECTORY in DIRECTORUL.curent
// set(CMAKE_INCLUDE_CURRENT_DIR ON)


// PRJECT DIR
// ${CMAKE_PROJECT_DIR}
