#pragma once
#include "..\Defs.h"
#include"..//SuperSoldiers.h"
#include"..//Generic_DS/Queue.h"
//#include"..//Generic_DS/Priority_queue.h"
#include "..//Enemies/Enemy.h"
#include "..//Fighter.h"
#include "..//Priority_queue.h"
#include "..//Generic_DS/Stack.h"
#include"..//Healer.h"
#include"..//Freezer.h"
class Castle
{
	double Health;
	double Power;//Omar adding
	double OriginalHealth;
	int Max_numofenemy;
	bool Frosted = false; //By Rodina
	double AmountOfice; //By Rodina
	Queue <SuperSoldiers*> QSuperS;      //Mariam
	static int  counter;
	
public:
	Castle();           //Mariam
	void SetHealth(double h);
	void setOriginalHealth(double oh);
	double getOriginalHealth() const;
	double GetHealth() const;
	void SetPower(double P);//Omar adding
	double GetPower() const;//Omar adding
	void SetMax_Enemy(int M);//Omar adding
	int GetMax_Enemy() const;//Omar adding
	bool Get_Frosted() const;//By Rodina
	void Set_Frosted();//By Rodina
	void FreezingAmount(double ice); //By Rodina
	void DecreaseHealth(double d);   // Mariam 
	SuperSoldiers* getSuperSolider();
	void Act_Castle_Fighters(Priority_queue<Fighter*>& Q_fighters, int N, Queue<Enemy*>& L_Killed, Stack<Healer*>& S_Healers, Queue<Freezer*>& Q_freezers, int TimeStep, bool THROWICE, Priority_queue<Enemy*>& Q_froozen);//omar	~Castle();
	~Castle();
	

//
	// TODO: Add More Member Functions As Needed
	//

};

