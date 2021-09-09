#pragma once

#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "Generic_DS\Stack.h"
#include"Freezer.h"
#include"Healer.h"
#include"Fighter.h"
#include"LinkedList.h"
#include"Priority_queue.h"
#include "GUI\GUI.h"
#include<time.h>
#include<cstdlib>
// it is the controller of the project
class Battle
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int Frosted_Fighters; int Frosted_Healers; int Frosted_Freezers; // by Rodina
	int Killed_Fighters; int Killed_Healers; int Killed_Freezers;
	int CurrentTimeStep;
	int EDrawCount; //count of enemies to be drawn. added by Nour
	int waitingTofSS = 5;
	int placeOfMaxNE=60;     // Place (distance ) of maximum number of enmies intially = 60
	SuperSoldiers* currSS=nullptr; //Current Super solider in the battle'\;
	bool Achieve = true;
	bool Castle_Status=false;
	bool Frosted = false;
	GAME_STATUS state;

	Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
											// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	bool isModeSelected = false;//added by nour

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	Stack<Healer*> S_Healers;
	Queue<Freezer*> Q_freezers;
	Priority_queue<Fighter*> Q_fighters;   
	Priority_queue<Enemy*> Q_froozen;
	Queue<Enemy*> L_Killed;
	Queue<Enemy*>CopyofActive;//Nour
	////////////////////////
	Queue<Enemy*>ActiveForMove;
	

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>


	

public:

	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle* GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	void Parsing();
	string OpenWindow(const string& Message); //Omar Adding
	/////////////////////////////////////////////////////////////////
	void  Set_Frosted_num();
	void  Set_Killed_num();
	void  Set_Active();
	void   setStateFrosted();
	/*void  increment_Frosted_Healers(int frostedCount);
	void  increment_Frosted_Freezers(int frostedCount);
	void  increment_Killed_Fighters(int KilledCount);
	void  increment_Killed_Healers(int KilledCount);
	void  increment_Killed_Freezers(int KilledCount);
	void  increment_ActiveCount(int Active);*/
	/////////////////////////////////////////////////////////////////
	//void Freezing2ActiveEnemies();
	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)

	void AddtoBEnemiesForDraw(Enemy* Ptr);	//added by Nour
	void UpdateEnemies();//added by Nour
	//--------------------------------------Modes---------------------------------------//
	void InteractiveMode();//added by nour
	void SilentMode();//added by Nour
	void StepMode();//added by nour
	void ActOnAllHealers(Stack<Healer*>& Healers);

	//////phase 1/////
	//void Freezing2ActiveEnemies(); 
	//void Defreezing2ActiveEnemies();
	

	//-------------------------------------getters--------------------------------------//
	int getCurrentTimeStep() const;//added by Nour--->get the current time step	
	int getEDrawCount();//added by nour --->get enemies to be drawn count 
	int getEnemyCount() const;//added by Nour
	bool getisModeSelected() const;//added by Nour to get if mode is selected 

	//-------------------------------------setters--------------------------------------//
	void setCurrentTimetep(int step);//added by Nour
	void setisModeSelected(bool cond);//added by Nour
	void DrawEnemies(GUI* pGUI); //added by Nour
	void setEnemyCount(int count);//added by Nour
	double DistMaxEnemy(Queue<Enemy*>& CopyofActiveFormMove);

	//demo
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)
	//--------------------------------- Super Soliders -----------------------------------------//
	void ActivateSuperSolidiers(int currTimeStep);
	void setplaceOfMaxNE(int d);   //mariam
	int getplaceOfMaxNE() const;   //mariam
	void CheckGameStatus();
	void OutputFile();
	//------------------------------------------------------------------------------------------//
	void Unfreezing();
	void Manger_Battle();
	bool Is_All_Killed();

};

