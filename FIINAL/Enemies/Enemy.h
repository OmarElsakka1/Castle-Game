#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	const int ID;         //Each enemy has a unique ID (sequence number)
	const int ArrvTime;	//arrival time (time it starts to join battle)

	ENMY_STATUS status;	    //status of the enemy (inactive, active, frosted, killed)
	int Distance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)
	double Health;	//Enemy health

	double originalHealth; // omar adding
	//ENMY_TYPE TYPE; //omar adding
	int Power; //omar adding
	int Reload_Period;//omar adding
	int Speed;//omar adding
	int TFS =-1;                // Time of first shot;1
	int Tkilled =- 1;              //Time of Killing
	int KillDelay;
	int LifeTime;
	int FirstShotDelay;
	int tRemain ; //time remainig untill reload period end;
	double Ice_Amount;
	double Meltingrate;
	const double ice_Thershold = 10; 

public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	virtual ~Enemy();

	void setTimeFirstShot(int t);
	int getTimeFirstShot();
	void setKillingTime(int t);
	int getKillingTime();
	int getKilldelay();
	int getLifeTime();
	int getFirstShotDelay();
	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);

	void DecrementDist();

	void SetDistance(int);
	int GetDistance() const;
	int GetArrvTime() const;

	void Set_Health(int H); //omar adding
	int Get_Health() const; //omar adding
	void Set_Power(int POW); //omar adding
	int Get_Power() const; //omar adding
	void Set_Reload(int RLD); //omar adding
	int Get_Reload() const; //omar adding
	void Set_Speed(int SPD); //omar adding
	int Get_Speed() const; //omar adding
	
	double Get_Original_Health() const; //omar adding
	void Set_Original_Health(double OH); //omar adding

	// Virtual Functions: ----------------

	virtual void Move() = 0;
	
	//All enemies can move
	virtual double Act() = 0;         	//Acting means fighting or healing


	void DecreaseTimeRemaning();
	int getTimeRemaning();

	/// freezing info
	void Set_Frosted();
	void Melting_Rate();
	double GetIceAmount();
	////////////////////////////////////////////////////////////////////////////
	bool IsFrosted();
	double Get_Thershold() const;
	//
	// TODO: Add More Member Functions As Needed
	//

};

