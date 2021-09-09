#pragma once
#include"Enemies/Enemy.h"
class SuperSoldiers
{
	int const speed = 3;
	int ArrvTime;
	int Distance=0;
	bool Backward;
	ENMY_STATUS status=ACTV;
	double Health = 25;
public:

	int getArrvTime() const;
	void setArrvTime(int t);
	int getDistance() const;
	void setDistance(int t);
	void Move(int placeOfMaxNumbOfEnemies);
	void Act(Enemy* enemy, int currTimeStep) const;
	void setStatus(ENMY_STATUS s);
	ENMY_STATUS getStatus()const;
	void setHealth(double h);
	void DecreaseHeath(double h);
};

