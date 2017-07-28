//
// Created by hosseinkh on 7/1/17.
//

#ifndef AGARSERVER_PARTS_H
#define AGARSERVER_PARTS_H

#include <vector>
#include <string>
#include <QtCore/QString>
#include <iostream>
#include <QtMultimedia/QMediaPlayer>
#include <QFileInfo>

class Playerm{
private:
    int x;
    int y;
    float r;
    int speedx=0;
    int speedy=0;
    int accelerationx=0;
    int accelerationy=0;
    int color;
    int iseatbale;

public:
    int set;
    bool sign;
    Playerm(int,int,float,int);
    Playerm();
    int X();
    int Y();
    float R();
    int speedX();
    int speedY();
    int Color();
    void setspeed(int,int);
    void setAcceleration(int,int);
    void setR(float);
    int Iseatable();
    void setUneatable();
    void advance(int,int);
    void eat(float);
};
class Player{
public:
    int color;
    Player(int,int,int,float);
    Player();
    std::vector<Playerm>childs;
    int centerx();
    int centery();
    int n;
    float sumr();
    bool eyeSight(int x,int y,int r);
    void advance();
    void split();
    void explode(int);
};
class Food{
private:
    int x;
    int y;
    int color;
    int ate;
public:
    Food(int,int,int);
    Food();
    void advance(bool iseaten);
    int X();
    int Y();
    int Color();
    int Ate();
};
class Mass{
private:
    int x;
    int y;
    int speedx;
    int speedy;
    int color;
public:
    Mass(int,int,int,int,int);
    Mass();
    void setspeed(int,int);
    int X();
    int Y();
    int speedX();
    int speedY();
    int Color();
    void advance();

};
class Virus{
private:
    int x;
    int y;
public:
    Virus(int,int);
    Virus();
    int X();
    int Y();
};
class world{
    int h;
    int w;
    int Specter;
    int players;
    int viruses;
    int masses;
    int foods;
    std::vector<Player>player;

    std::vector<Virus>virus;
    std::vector<Mass>mass;
    std::vector<Food>food;
public:
    QMediaPlayer *myplayer;
    world();
    world(int,int,int,int);
    void addPlayer(int c);
    void addSpecter(int);
    std::vector<int>specters;
    int Players();
    int specter();
    int Viruses();
    int Masses();
    int Foods();
    void kickPlayer(int n);
    void advance();
    void newTask(int ,int,int,int);
    QString packMap(int);


};
#endif //AGARSERVER_PARTS_H
