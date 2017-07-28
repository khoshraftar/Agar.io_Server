//
// Created by hosseinkh on 7/1/17.
//
#include "parts.h"
/////////////////////////////////////// Playerm //////////////////////////////////////////////
Playerm::Playerm(int a, int b, float c, int d) {
    speedx=0;
    speedy=0;
    setAcceleration(0,0);
    x = a;
    y = b;
    r = c;
    color = d;
    setUneatable();
}
void Playerm::setUneatable() {iseatbale=99;}
int Playerm::X() { return x; }
int Playerm::Y() { return y; }
float Playerm::R() { return r; }
int Playerm::speedX() {return speedx;}
int Playerm::speedY() {return speedy;}
int Playerm::Color() {return color;}
void Playerm::eat(float a) {r+=a;}
void Playerm::setspeed(int a, int b) {speedx=a;speedy=b;}
void Playerm::setR(float a) {r=a;}
void Playerm::setAcceleration(int a, int b) {accelerationx=a;accelerationy=b;}
void Playerm::advance(int a,int b)
{
    int tmx=0;
    int tmy=0;
    if(x>a)
        tmx=-1;
    if(x<a)
        tmx=1;
    if(y>b)
        tmy=-1;
    if(y<b)
        tmy=1;
    if(x>10000)
        x=10000;
    if(x<0)
        x=0;
    if(y>10000)
        y=10000;
    if(y<0)
        y=0;
    x+=(10*speedx+5*tmx)/sqrt(r);
    y+=(10*speedy+5*tmy)/sqrt(r);
    setspeed(speedx+accelerationx,speedy+accelerationy);
    if(set==0 && sign)
    {
        setspeed(speedx/2,speedy/2);
        sign=0;
    }
    if(set)
        set--;
    if(iseatbale)
        iseatbale--;
}
Playerm::Playerm() {}
int Playerm::Iseatable() {return iseatbale;}
/////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////// Player ///////////////////////////////////
Player::Player(){};
Player::Player(int a, int b ,int c,float d)
{
    Playerm tmp(a,b,d,c);
    childs.push_back(tmp);
    n=1;
    color=c;

}
int Player::centerx()
{
    int tmp=0;
    for(int i=0;i<n;i++) tmp+=childs[i].X();
    return tmp/n;
}
int Player::centery() {
    int tmp=0;
    for(int i=0;i<n;i++) tmp+=childs[i].Y();
    return tmp/n;
}
void Player::advance()
{
    for(int i=0;i<n;i++)
    {

        childs[i].advance(centerx(),centery());
    }
}
float Player::sumr()
{
    float tmp=0;
    for(int i=0;i<n;i++)
    {
        tmp+=childs[i].R();
    }
    return tmp;
}
void Player::split()
{
    for(int i=0;i<n;i++)
    {
        if(childs[i].R()>40)
        {
            Playerm ch(childs[i].X(),childs[i].Y(),childs[i].R()/2,childs[i].Color());
            ch.setUneatable();
            childs[i].setUneatable();
            childs[i].setR(childs[i].R()/2);
            ch.setspeed(childs[i].speedX()*2,childs[i].speedY()*2);
            ch.set=20;
            ch.sign=1;
            childs.push_back(ch);
        }
    }
    n=childs.size();
    std::cout<<"splited"<<std::endl;
    std::cout<<sumr()<<std::endl;
}
bool Player::eyeSight(int x,int y,int r)
{
    if((centerx()-x)*(centerx()-x)+(centery()-y)*(centery()-y)<(22*sumr()+r)*(22*sumr()+r))
        return 1;
    return 0;
}
void Player::explode(int a)
{
    int x1=childs[a].X();
    int y1=childs[a].Y();
    int color2=childs[a].Color();
    float r1=childs[a].R();
    Playerm e1(x1+20,y1+20,r1/8,color2);
    Playerm e2(x1+20,y1,r1/8,color2);
    Playerm e3(x1+20,y1-20,r1/8,color2);
    Playerm e4(x1,y1+20,r1/8,color2);
    Playerm e5(x1-20,y1+20,r1/8,color2);
    Playerm e6(x1-20,y1,r1/8,color2);
    Playerm e7(x1-20,y1-20,r1/8,color2);
    Playerm e8(x1,y1-20,r1/8,color2);
    childs.erase(childs.begin()+a);
    childs.push_back(e1);
    childs.push_back(e2);
    childs.push_back(e3);
    childs.push_back(e4);
    childs.push_back(e5);
    childs.push_back(e6);
    childs.push_back(e7);
    childs.push_back(e8);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////// Food  ///////////////////////////////////////////////
Food::Food(){}
Food::Food(int a, int b, int c)
{
    x=a;
    y=b;
    color=c;
    ate=0;
}
int Food::X(){return x;}
int Food::Y(){return y;}
int Food::Ate(){return ate;}
int Food::Color(){return color;}
void Food::advance(bool iseaten)
{
    if(iseaten) ate=660;
    else
    {
        if(ate==0)
            return;
        ate--;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// Mass /////////////////////////////////
Mass::Mass() {}
Mass::Mass(int a, int b, int c, int d, int e)
{
    x=a;
    y=b;
    speedx=c;
    speedy=d;
    color=e;
}
int Mass::X(){return x;}
int Mass::Y(){return y;}
int Mass::speedX(){return speedx;}
int Mass::speedY(){return speedy;}
int Mass::Color(){return color;}
void Mass::advance()
{
    x+=speedx;
    y+=speedy;
    if(speedx>0)
    speedx--;
    if(speedx<0)
        speedx++;
    if(speedy>0)
        speedy--;
    if(speedy<0)
        speedy++;
}
void Mass::setspeed(int a, int b)
{
    speedx=a;
    speedy=b;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////// virus /////////////////////////////////////////////////////
Virus::Virus() {}
Virus::Virus(int a, int b){x=a;y=b;}
int Virus::X() {return x;}
int Virus::Y() {return y;}
///////////////////////////////////////////////////////////////////////////////////////////////

/********************************************* world *******************************************/
world::world() {}
world::world(int h, int w,int f,int v)
{
    Specter=0;
    players=0;
    masses=0;
    viruses=v;
    foods=f;
    for(int i=0;i<f;i++)
    {
        Food a(rand()%w,rand()%h,rand()%17);
        food.push_back(a);
    }
    for(int i=0;i<v;i++)
    {
        Virus a(rand()%w,rand()%h);
        virus.push_back(a);
    }
}
void world::addSpecter(int c) {Specter++;specters.push_back(c);}
int world::specter() {return Specter;}
int world::Players(){return players;}
int world::Viruses(){return viruses;}
int world::Masses(){return masses;}
int world::Foods(){return foods;}
void world::addPlayer(int c)
{
    players++;
    int tx=rand()%10000;
    int ty=rand()%10000;
    Player a(tx,ty,c,40);
    player.push_back(a);

}
void world::newTask(int a, int b, int c, int d)
{
    //////////////////////////////////////move////////////////////////////////////////
    if(c<330 && c>310 && d<330 &&d>310)
    {
        for(int i=0;i<player[a].n;i++)
        {
            player[a].childs[i].setspeed(0,0);
        }
        return;
    }
    if(b==1)
    {
        int speedx=25*(c-320)*(c-320)/((c-320)*(c-320)+(d-320)*(d-320));
        int speedy=25*(d-320)*(d-320)/((c-320)*(c-320)+(d-320)*(d-320));
        int tmpx=0;
        if(c>320)
            tmpx=1;
        else
            tmpx=-1;
        int tmpy=0;
        if(d>320)
            tmpy=1;
        else
            tmpy=-1;
        for(int i=0;i<player[a].n;i++)
        {
            player[a].childs[i].setspeed(tmpx*sqrt(speedx)*2,tmpy*sqrt(speedy)*2);
        }
        return;
    }
    //////////////////////////////////////feed///////////////////////////////////////
    if(b==2)
    {
        for(int i=0;i<player[a].childs.size();i++)
        {
            float R=player[a].childs[i].R();
            int x=player[a].childs[i].X();
            int y=player[a].childs[i].Y();
            int cl=player[a].color;
            if(R>24)
            {
                int speedx=100*(c-320)*(c-320)/((c-320)*(c-320)+(d-320)*(d-320));
                int speedy=100*(d-320)*(d-320)/((c-320)*(c-320)+(d-320)*(d-320));
                int tmpx=0;
                if(c>320)
                    tmpx=1;
                else
                    tmpx=-1;
                int tmpy=0;
                if(d>320)
                    tmpy=1;
                else
                    tmpy=-1;
                player[a].childs[i].setR(R-4);
                Mass ab(x,y,20,20,cl);
                ab.setspeed(tmpx*sqrt(speedx)*3,tmpy*sqrt(speedy)*3);
                mass.push_back(ab);
                masses++;
            }
        }
        return;
    }
    /////////////////////////////////split///////////////////////////////////////
    if(b==3)
    {
        int speedx=25*(c-320)*(c-320)/((c-320)*(c-320)+(d-320)*(d-320));
        int speedy=25*(d-320)*(d-320)/((c-320)*(c-320)+(d-320)*(d-320));
        int tmpx=0;
        if(c>320)
            tmpx=1;
        else
            tmpx=-1;
        int tmpy=0;
        if(d>320)
            tmpy=1;
        else
            tmpy=-1;
        for(int i=0;i<player[a].childs.size();i++)
        {
            player[a].childs[i].setspeed(tmpx*sqrt(speedx)*3,tmpy*sqrt(speedy)*3);
        }
        player[a].split();
    }
}
void world::kickPlayer(int a)
{
    player.erase(player.begin()+a);
    players--;
}
void world::advance()
{
    if(!players)
        return;
    for(int i=0;i<players;i++)
    {
        player[i].advance();
    }

    for(int i=0;i<masses;i++)
    {
        mass[i].advance();
    }
    // ///////////////////// food eating ////////////////////////
    for(int i=0;i<foods;i++)
    {
        if(food[i].Ate())
        {
            food[i].advance(0);
            continue;
        }
        int fx=food[i].X();
        int fy=food[i].Y();
        int tmp=0;
        for(int j=0;j<players;j++)
        {
            for(int k=0;k<player[j].n;k++)
            {
                int tx=player[j].childs[k].X();
                int ty=player[j].childs[k].Y();
                if((tx-fx)*(tx-fx)+(ty-fy)*(ty-fy)<(player[j].childs[k].R())*(player[j].childs[k].R()))
                {
                    food[i].advance(1);
                    player[j].childs[k].eat(0.1);
                    tmp=1;
                    continue;
                }
                if(tmp)
                    continue;
            }
            if(tmp)
                continue;
        }
    }
    // //////////////////// player eating //////

    for(int i=0;i<players;i++)
    {
        for(int j=0;j<player[i].n;j++)
        {
            int x1=player[i].childs[j].X();
            int y1=player[i].childs[j].Y();
            float r1=player[i].childs[j].R();
            for(int i2=0;i2<players;i2++)
            {
                for(int j2=0;j2<player[i2].n;j2++)
                {
                    int x2=player[i2].childs[j2].X();
                    int y2=player[i2].childs[j2].Y();
                    float r2=player[i2].childs[j2].R();
                    if(i!=i2 || j!=j2)
                    {
                        if(r1-r2>5 || i==i2)
                        {
                            if(i==i2 && player[i2].childs[j2].Iseatable())
                                break;
                            if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=r1*r1)
                            {
                                player[i].childs[j].eat(r2);
                                player[i2].childs.erase(player[i2].childs.begin()+j2);
                                player[i2].n--;
                                return;
                            }
                        }
                        if(r2-r1>5 || i==i2)
                        {
                            if(i==i2 && player[i].childs[j].Iseatable())
                                break;
                            if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=r2*r2)
                            {
                                player[i2].childs[j2].eat(r1);
                                player[i].childs.erase(player[i].childs.begin()+j);
                                player[i].n--;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    // ///////////////////////////////// mass eating ////////////////////////
    for(int i=0;i<masses;i++)
    {
        int x1=mass[i].X();
        int y1=mass[i].Y();
        if((mass[i].speedX()+mass[i].speedY()))
            continue;
        for(int j=0;j<players;j++)
        {
            int tmp=0;
            for(int k=0;k<player[j].n;k++)
            {
                int x2=player[j].childs[k].X();
                int y2=player[j].childs[k].Y();
                float r2=player[j].childs[k].R();
                if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<r2*r2)
                {
                    player[j].childs[k].eat(4);
                    mass.erase(mass.begin()+i);
                    masses--;
                    tmp=1;
                    break;
                }
            }
            if(tmp) break;
        }
    }
    // /////////////////////////////// virus eating ///////////////////////////
    for(int v=0;v<viruses;v++)
    {
        int x1=virus[v].X();
        int y1=virus[v].Y();
        for(int i=0;i<players;i++)
        {
            int tmp=0;
            for(int j=0;j<player[i].n;j++)
            {
                if(player[i].childs[j].R()>=80)
                {
                    int x2=player[i].childs[j].X();
                    int y2=player[i].childs[j].Y();
                    float r2=player[i].childs[j].R();
                    if((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<r2*r2)
                    {
                        player[i].split();
                        player[i].split();
                        //player[i].explode(j);
                        virus.erase(virus.begin()+v);
                        viruses--;
                        tmp=1;
                        break;
                    }
                }
            }
            if(tmp)
                break;
        }
    }
}
QString world::packMap(int a)
{
    if(player[a].n==0)
        return "Game Over Noob";
    std::string res="";
    int x=player[a].centerx();
    int y=player[a].centery();
    float r=player[a].sumr();
    for(int i=0;i<player[a].n;i++)
    {
        float tr=player[a].childs[i].R();
        std::string tx=std::to_string(int(20*(player[a].childs[i].X()-x)/r+320));
        std::string ty=std::to_string(int(20*(player[a].childs[i].Y()-y)/r+320));
        res=res+(std::to_string(int(40*(tr/r)))+' '+tx+' '+ty +' ');
    }
    res=res+std::to_string(-99999)+' ';
    for(int i=0;i<foods;i++)
    {
        int tx=food[i].X();
        int ty=food[i].Y();
        if(food[i].Ate()==0 && player[a].eyeSight(tx,ty,10))
        {
            res=res+(std::to_string(int(20*(tx-x)/r+320))+' '+std::to_string(int(20*(ty-y)/r+320))+' '+std::to_string(int(10*40/r))+' '+std::to_string(food[i].Color()) +' ');
        }
    }
    res=res+std::to_string(-99999)+' ';
    for(int j=0;j<players;j++)
    {
        if(j!=a)
        {
            for(int i=0;i<player[j].n;i++)
            {
                if(player[a].eyeSight(player[j].childs[i].X(),player[j].childs[i].Y(),player[j].childs[i].R()))
                res=res+(std::to_string(int(20*(player[j].childs[i].X()-x)/r+320)) + ' ' + std::to_string(int(20*(player[j].childs[i].Y()-y)/r)+320)+
                        ' '+std::to_string(int(player[j].childs[i].R()*40/r))+' '+std::to_string(player[j].childs[i].Color())+' ');
            }
        }
    }
    res=res+std::to_string(-99999)+' ';
    for(int i=0;i<masses;i++)
    {
        if(player[a].eyeSight(mass[i].X(),mass[i].Y(),20))
        res=res+(std::to_string(int(20*(mass[i].X()-x)/r+320))+' '+std::to_string(int(20*(mass[i].Y()-y)/r+320))+' '+std::to_string(int(20*20/player[a].sumr()))+' '+std::to_string(mass[i].Color())+' ');
    }
    res=res+std::to_string(-99999)+' ';
    for(int i=0;i<viruses;i++)
    {
        if(player[a].eyeSight(virus[i].X(),virus[i].Y(),100)){
                res = res + (std::to_string(int(20*(virus[i].X()-x)/r+320)) + ' ' + std::to_string(int(20*(virus[i].Y()-y)/r+320)) + ' ' + std::to_string(int(160 * 20 / player[a].sumr())) + ' ');
        }
    }
    res=res+std::to_string(-99999);
    QString qres=QString::fromStdString(res);
    return qres;
}