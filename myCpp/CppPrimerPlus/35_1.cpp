/*************************************************************************
	> File Name: 35_1.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年02月26日 星期日 19时04分00秒
 ************************************************************************/

#include<iostream>
class GameCharacter{
public:
    int const healthValue()const{return gethealth();}
    GameCharacter(int s):health(s){}
private:
    virtual int const gethealth()const{std::cout<<"This is a GameCharacter. That's all. Thank you."<<std::endl;}
    int health;
};
class Badgay:public GameCharacter{
public:
    Badgay(int s):GameCharacter(s){}
private:
    int const gethealth()const{std::cout<<"This is a Badgay. That's all, Thank you."<<std::endl;}
};
int main()
{
    GameCharacter a(72);
    Badgay b(76);
    GameCharacter *c=new Badgay(82);
    a.healthValue();
    c->healthValue();
    return 0;
}

