#include "ApplicationWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DontShowIconsInMenus, false);

    QApplication::setApplicationName(CMAKE_DEF_APP_NAME);
    QApplication::setApplicationVersion(CMAKE_DEF_PROJECT_VERSION);

    // this shows the MainWindow
    ApplicationWindow w;
    w.show();

    // this processes Messages for the MainWindow
    return a.exec();
}


// FOARTE IMPORTANT
// ca sa ai include DIRECTORY in DIRECTORUL.curent
// set(CMAKE_INCLUDE_CURRENT_DIR ON)


// PRJECT DIR
// ${CMAKE_PROJECT_DIR}
