#pragma once
#include "Enemies/Enemy.h"
#include"Generic_DS/Queue.h"
class Healer :
    public Enemy
{
private:
    bool Backward = false;
public:
    Healer(int id, int at, int d);
    void Move();
    void increaseHealth(Queue<Enemy*>& CopyofActiveFormMove);
    double Act();
};


