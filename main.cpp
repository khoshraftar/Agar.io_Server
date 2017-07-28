#include <iostream>
#include "server.h"
#include <QApplication>

using namespace std;

int main(int argc, char **argv) {
    QApplication *app = new QApplication(argc, argv);
    Server *myServer = new Server();
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()),myServer,SLOT(write()));
    timer.start(1000/33);
    myServer->show();
    app -> exec();
    return 0;
}