#pragma once
#include "Enemies/Enemy.h"
class Freezer :
    public Enemy
{

public:
    Freezer(int id, int at, int d);
    void Move();
    double Act();
};