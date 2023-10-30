//#include "Menu.h"
#include "ClientSimulator.h"

#include <QObject>

int main(int argc, char *argv[])
{
    // orice main() de aplicatie Qt va contine aceasta linie>
    // incat sa creeze EVENT LOOP-ul specific Qt-ului
    // VEZI la sfarsit: return a.exec();
    QCoreApplication a(argc, argv);

    ClientSimulator clientSimulator;
    QThread workerThread;
    clientSimulator.moveToThread(&workerThread);
    QObject::connect(&workerThread, &QThread::started, &clientSimulator, &ClientSimulator::run);
    QObject::connect(&workerThread, &QThread::finished, &clientSimulator, &QObject::deleteLater);
    workerThread.start();

    clientSimulator.init();
    workerThread.quit();
    workerThread.wait();

    return a.exec();
}
