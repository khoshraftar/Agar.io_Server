//
// Created by hosseinkh on 6/30/17.
//

#ifndef AGARSERVER_SERVER_H
#define AGARSERVER_SERVER_H
#include <QUdpSocket>
#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QWidget>
#include <QtWidgets>
#include <QTimer>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include <iostream>
#include "parts.h"
class QTimer;
class QHostAddress;
class QDialog;
class QTcpSocket;
class QTcpServer;
class Server : public QWidget{
Q_OBJECT
public:
    Server(QHostAddress * = new QHostAddress("127.0.0.1"), quint16 = 4444,QWidget *parent=0);
public slots:
    void createConnection();
    void read();
    void write();
private:
    QHostAddress *serverAddress;
    quint16 serverPort;
    QTcpServer *server;
    QList<QTcpSocket*> *clients;
    QList<QTcpSocket*> *Spectators;
    QHBoxLayout *qhb;
    QLabel *ql;
    QTextEdit *qt;
    world* MyWorld;
};
#endif //AGARSERVER_SERVER_H
