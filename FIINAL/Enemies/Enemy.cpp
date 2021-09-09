#include"Enemy.h"

Enemy::Enemy(int id, int arrTime, int d) :ID(id), ArrvTime(arrTime)
{
	SetDistance(d);
	tRemain = 0;
	Ice_Amount = 0;
	Meltingrate = 0;
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}


void Enemy::Set_Health(int H)
{
	if (H > 0)
	{
		Health = H;
	}
	else
	{
		Health = 0;
	}
}
int Enemy::Get_Health() const
{
	return Health;
}
void Enemy::Set_Power(int POW)
{
	if (POW > 0)
	{
		Power = POW;
	}
	else
	{
		Power = 0;
	}
}
int Enemy::Get_Power() const
{
	return Power;
}
void Enemy::Set_Reload(int RLD)
{
	if (RLD > 0)
	{
		Reload_Period = RLD;
	}
	else
	{
		Reload_Period = 0;
	}
}
int Enemy::Get_Reload() const
{
	return Reload_Period;
}
void Enemy::Set_Speed(int SPD)
{
	if (SPD > 0)
	{
		Speed = SPD;
	}
	else
	{
		Speed = 0;
	}
}
int Enemy::Get_Speed() const
{
	return Speed;
}


void Enemy::Set_Original_Health(double OH)
{
	if (OH > 0)
	{
		originalHealth = OH;
	}
	else
	{
		originalHealth = 0;
	}
}
double Enemy::Get_Original_Health() const
{
	return originalHealth;
}


int Enemy::getFirstShotDelay() {
	return TFS - ArrvTime;
}

void Enemy::setTimeFirstShot(int t) {
	if (t < 0)
		return;
	TFS = t;
}
int Enemy::getTimeFirstShot() {
	return TFS;
}
void Enemy::setKillingTime(int t) {
	Tkilled = t;
}
int Enemy::getKillingTime() {
	return Tkilled;
}
int Enemy::getKilldelay() {
	return Tkilled - TFS;
}
int Enemy::getLifeTime() {
	return Tkilled - ArrvTime;
}

void Enemy::DecreaseTimeRemaning() {
	--tRemain;
}
int Enemy::getTimeRemaning() {
	return tRemain;
}

double Enemy::GetIceAmount()
{
	return Ice_Amount;
}

void Enemy::Melting_Rate()
{
	Meltingrate =(Health+Power) / 10;
	Ice_Amount = Ice_Amount - Meltingrate;

	if (Ice_Amount < 0)
		Ice_Amount = 0;

	if (Ice_Amount < ice_Thershold )
	{
		status = ACTV;
	}
}

void Enemy::Set_Frosted()
{
	double ice_thrown = 0;

	ice_thrown = 60 / (Health * Distance);

	Ice_Amount = Ice_Amount + ice_thrown;

	if (Ice_Amount >= ice_Thershold)
		status = FRST;

	if (Health < (originalHealth / 2))
	{
		Speed = Speed -(2* Ice_Amount);
	}
	else 
	{
		Speed = Speed - Ice_Amount;
	}

}
bool Enemy::IsFrosted()
{
	if (Ice_Amount >= ice_Thershold)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double Enemy::Get_Thershold() const
{
	return ice_Thershold;
}