//
// Created by hosseinkh on 6/30/17.
//
#include "server.h"
void Server::createConnection() {
    QTcpSocket *client = server->nextPendingConnection();
    QString s = qt->toPlainText();
    std::string s1 = s.toStdString();
    int tmp = std::stoi(s1);
    qt->setText(QString::fromStdString(std::to_string(tmp + 1)));
    connect(client, SIGNAL(readyRead()), this, SLOT(read()));
    clients->append(client);
}
void Server::read() {
    for (int i = 0; i < clients->size(); i++)
        if (clients->at(i)->bytesAvailable() > 0)
        {
            std::string DataAsString=(clients->at(i)->readAll()).toStdString();
            if(DataAsString.size()==1||DataAsString.size()==2)
            {
                std::string s=DataAsString;
                int c=std::stoi(s);
                MyWorld->addPlayer(c);
            }
            if(DataAsString.size()==3)
            {
                Spectators->push_back(clients->at(i));
                clients->erase(clients->begin()+i);
                i--;
                MyWorld->addSpecter(std::stoi(DataAsString)/100-1);
            }
            if(DataAsString.size()>3)
            {
                std::cout<<"newTask"<<std::endl;
                std::stringstream mystream(DataAsString);
                int x,y,type;
                mystream>>x>>y>>type;
                MyWorld->newTask(i,type,x,y);
            }
        }
}
void Server::write() {
    if(MyWorld->Players()) {
        MyWorld->advance();
        for (int j = 0; j < clients->size(); j++) {
            QByteArray data = &(MyWorld->packMap(j)).toStdString()[0];
            clients->at(j)->write(data);
        }
    }
    if(MyWorld->specter())
    {
        for(int i=0;i<Spectators->size();i++)
        {
            QByteArray data = &(MyWorld->packMap(MyWorld->specters[i])).toStdString()[0];
            Spectators->at(i)->write(data);
        }
    }
}
Server::Server( QHostAddress *serverAddress, quint16 serverPort, QWidget *parent) : serverAddress(serverAddress), serverPort(serverPort) {
    clients = new QList<QTcpSocket *>();
    Spectators=new QList<QTcpSocket*>();
    server = new QTcpServer(this);
    server->listen(*serverAddress, serverPort);
    qhb = new QHBoxLayout;
    ql = new QLabel("number of players");
    qt = new QTextEdit;
    qt->setReadOnly(true);
    qt->setFixedSize(100, 20);
    qt->setText("0");
    qhb->addWidget(ql);
    qhb->addWidget(qt);
    MyWorld=new world(10000,10000,4000,5);
    connect(server, SIGNAL(newConnection()), this, SLOT(createConnection()));
    setLayout(qhb);
    show();
}

