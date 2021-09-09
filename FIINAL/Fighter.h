#pragma once
#include "Enemies/Enemy.h"
#include"SuperSoldiers.h"
class Fighter : public Enemy
{
    int tRemain = 0; //time remainig untill reload period end;
public:
    Fighter(int id, int at, int d);
    void Move();
    void DecreaseTimeRemaning();
    int getTimeRemaning();
    double Act();
    void ActOnSS(SuperSoldiers*& s);
};

