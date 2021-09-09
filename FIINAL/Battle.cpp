#include "Battle.h"
#include <time.h>
#include <fstream>
#include<iostream>

Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	EDrawCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;

	/////// by Rodina
	Frosted_Fighters = 0;
	Frosted_Healers = 0;
	Frosted_Freezers = 0;
	Killed_Fighters = 0;
	Killed_Healers = 0;
	Killed_Freezers = 0;
}
double Battle::DistMaxEnemy(Queue<Enemy*>& CopyofActiveFormMove)
{
	int counter = 0;
	int tempcounter = 0;
	double maxdistance = 0;
	double tempdistance = 0;
	Queue<Enemy*> enemykeeper;
	Queue<double> keeper;// full of distances
	Queue<double> keeper2;// full of distances
	Queue<double> Done;// enqueue done
	ActiveForMove.copyQueue(enemykeeper);
	int n = enemykeeper.getSize();
	Enemy* T;
	double D;
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
		{
			enemykeeper.dequeue(T);
			keeper.enqueue((T->GetDistance()));
		}
	}
	int x = keeper.getSize();
	for (int j = 0; j < x; j++)
	{
		for (int z = 0; z < keeper.getSize(); z++)
		{
			keeper.dequeue(D);
			if (maxdistance == D)
			{
				Done.enqueue(D);
				break;
			}
			if (tempcounter == 0)
			{
				tempdistance = D;
				tempcounter++;
				Done.enqueue(D);
			}
			else
			{
				if (D == tempdistance)
				{
					tempcounter++;
				}
				keeper2.enqueue(D);
			}

		}
		if (tempcounter > counter)
		{
			counter = tempcounter;
			maxdistance = tempdistance;
		}
		tempcounter = 0;
		tempdistance = 0;
		int keeper2size = keeper2.getSize();
		for (int u = 0; u < keeper2size; u++)
		{
			keeper2.dequeue(D);
			keeper.enqueue(D);

		}

	}
	int Donesize = Done.getSize();
	for (int s = 0; s < Donesize; s++)
	{
		Done.dequeue(D);
		keeper.enqueue(D);
	}
	cout << "This is the max distace " << maxdistance << " and this is the count " << counter;
	return maxdistance;


}
//--------------------------------------------getters------------------------------------------// added by Nour
int Battle::getCurrentTimeStep()const
{
	return CurrentTimeStep;
}
int Battle::getEDrawCount()
{
	return  EDrawCount;
}
bool Battle::getisModeSelected() const
{
	return isModeSelected;
}
int Battle::getEnemyCount() const
{
	return EnemyCount;
}

void Battle::setStateFrosted() {
	srand(time(0));
	int v=rand() % 200;
	if (v == CurrentTimeStep)
		Frosted = true;
	else
		Frosted = false;
}


//--------------------------------------------Setters------------------------------------------// added by Nour and Rodina
void  Battle::Set_Frosted_num()
{
	Frosted_Fighters = 0;
	Frosted_Healers = 0;
	Frosted_Freezers = 0;
	Priority_queue<Enemy*> temp;
	Q_froozen.copyPrioQueue(temp);
	for (int i = 0; i < Q_froozen.getSize(); i++)
	{
		Enemy* pE;
		temp.pop(pE);
		Fighter* Fi = dynamic_cast<Fighter*>(pE);
		Healer* He = dynamic_cast<Healer*>(pE);
		Freezer* Fr = dynamic_cast<Freezer*>(pE);
		if (Fi != nullptr)
		{
			Frosted_Fighters++;
		}
		else if (He != nullptr)
		{
			Frosted_Healers++;
		}
		else if (Fr != nullptr)
		{
			Frosted_Freezers++;
		}

	}
}
void  Battle::Set_Killed_num()
{
	Killed_Fighters = 0;
	Killed_Healers = 0;
	Killed_Freezers = 0;
	Queue<Enemy*> temp;
	L_Killed.copyQueue(temp);
	for (int i = 0; i < L_Killed.getSize(); i++)
	{
		Enemy* pE;
		temp.dequeue(pE);
		Fighter* Fi = dynamic_cast<Fighter*>(pE);
		Healer* He = dynamic_cast<Healer*>(pE);
		Freezer* Fr = dynamic_cast<Freezer*>(pE);
		if (Fi != nullptr)
		{
			Killed_Fighters++;
		}
		else if (He != nullptr)
		{
			Killed_Healers++;
		}
		else if (Fr != nullptr)
		{
			Killed_Freezers++;
		}

	}
}


void  Battle::Set_Active()
{
	ActiveCount = Q_fighters.getSize() + S_Healers.getSize() + Q_freezers.getSize();
}


//void  Battle::increment_Frosted_Healers(int frostedCount)
//{
//	Frosted_Healers = Frosted_Healers + frostedCount;
//}
//void  Battle::increment_Frosted_Freezers(int frostedCount)
//{
//	Frosted_Freezers = Frosted_Freezers + frostedCount;
//}
//void  Battle::increment_Killed_Fighters(int KilledCount)
//{
//	Killed_Fighters = Killed_Fighters + KilledCount;
//}
//void  Battle::increment_Killed_Healers(int KilledCount)
//{
//	Killed_Healers = Killed_Healers + KilledCount;
//}
//void  Battle::increment_Killed_Freezers(int KilledCount)
//{
//	Killed_Freezers = Killed_Freezers + KilledCount;
//}
//void  Battle::increment_ActiveCount(int Active)
//{
//	ActiveCount + Active;
//}
void Battle::setisModeSelected(bool cond)
{
	isModeSelected = cond;
}
void Battle::setCurrentTimetep(int step)
{
	CurrentTimeStep = step;
}
void Battle::setEnemyCount(int count)
{
	EnemyCount = count;
}
//---------------------------------------------------------------------------------------------//
void Battle::DrawEnemies(GUI* pGUI)
{
	//pGUI->DrawAllItems(BEnemiesForDraw, EnemyCount);
}
//---------------------------------------------------------------------------------------------//
void Battle::Parsing()
{
	string filename ="";
	ifstream finput;
	while (filename == "")
	{
		filename = OpenWindow("Choose the input text file: ");
	}

	finput.open(filename);

	//ifstream finput("text - Copy.txt");
	char* pch;
	char* context = nullptr;
	const int size = 300;
	char line[size];

	if (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, " ", &context);
		if (pch != NULL)
		{
			if (pch != NULL)
			{
				int CH = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetHealth(CH);
				BCastle.setOriginalHealth(CH);
			}
			if (pch != NULL)
			{
				int N = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetMax_Enemy(N);
			}
			if (pch != NULL)
			{
				int CP = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				BCastle.SetPower(CP);
			}
		}
	}

	if (finput.getline(line, size)) //read file line by line
	{ //parse the line
		pch = strtok_s(line, " ", &context);
		if (pch != NULL)
		{
			EnemyCount = stoi(pch);

		}
	}

	for (int i = 0; i < EnemyCount; i++)
	{
		//Enemy enemy1(1,2,3);
		if (finput.getline(line, size))
		{
			int ID{};
			int AT{};
			int POW{}, RLD{}, SPD{};
			double H{};
			int TYP1;
			pch = strtok_s(line, " ", &context);
			if (pch != NULL)
			{
				ID = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << ID << " ";
			}

			if (pch != NULL)
			{
				TYP1 = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << TYP << " ";
			}

			if (pch != NULL)
			{
				AT = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//cout << AT << " ";
			}

			if (pch != NULL)
			{
				H = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Health(H);
				//enemy1->Set_Original_Health(H);
			}

			if (pch != NULL)
			{
				POW = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Power(POW);
			}

			if (pch != NULL)
			{
				RLD = stoi(pch);
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Reload(RLD);
			}

			if (pch != NULL)
			{
				SPD = stoi(pch);;
				pch = strtok_s(NULL, " ", &context);
				//enemy1->Set_Speed(SPD);
			} //torevise 
			//Q_Inactive.enqueue(enemy1);



			
			if (TYP1 == 0)
			{
				//Fighter* Fi = dynamic_cast<Fighter*>(pE);
				Fighter* fighter = new Fighter(ID, AT, MaxDistance);
				fighter->SetStatus(INAC);
				fighter->Set_Health(H);
				fighter->Set_Original_Health(H);
				fighter->Set_Power(POW);
				fighter->Set_Reload(RLD);
				fighter->Set_Speed(SPD);
				Q_Inactive.enqueue(fighter);
			}
			else if (TYP1 == 1)
			{
				Healer* healer = new Healer(ID, AT, MaxDistance);
				healer->SetStatus(INAC);
				healer->Set_Health(H);
				healer->Set_Original_Health(H);
				healer->Set_Power(POW);
				healer->Set_Reload(RLD);
				healer->Set_Speed(SPD);
				Q_Inactive.enqueue(healer);
			}
			else if (TYP1 == 2)
			{
				Freezer* freezer = new Freezer(ID, AT, MaxDistance);
				freezer->SetStatus(INAC);
				freezer->Set_Health(H);
				freezer->Set_Original_Health(H);
				freezer->Set_Power(POW);
				freezer->Set_Reload(RLD);
				freezer->Set_Speed(SPD);
				Q_Inactive.enqueue(freezer);
			}
		}
	}
}
bool Battle::Is_All_Killed()
{
	// we could simply replace it with
	//if(L_Killed.getSize() == EnemyCount)
	if (Q_Inactive.getSize() == 0 && S_Healers.getSize() == 0 && Q_freezers.getSize() && Q_fighters.getSize() == 0 && Q_froozen.getSize() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Battle::Manger_Battle()
{
	if (!Is_All_Killed())
	{
		if (BCastle.Get_Frosted())
		{
			Queue<Fighter*> temp;
			for (int i=0 ; i <Q_fighters.getSize(); i++)
			{
				Fighter* fighter;
				Q_fighters.pop(fighter);
				fighter->Act();
				temp.enqueue(fighter);
			}
		}
		else
		{
			bool THROWICE = false;
			srand(time(0));
			if ((rand() % 10) - (rand() % 3) == 0)
			{
				THROWICE = true;
			}
			else
			{
				THROWICE = false;
			}
			BCastle.Act_Castle_Fighters(Q_fighters, EnemyCount, L_Killed, S_Healers, Q_freezers, CurrentTimeStep, THROWICE, Q_froozen);
		}
	}
}

void Battle::Unfreezing()
{
	if (Q_froozen.getSize() != 0)
	{
		bool Continue_ = true;
		while (Continue_)
		{
			Enemy* parentpointer;
			Q_froozen.pop(parentpointer);
			double iceamount = parentpointer->GetIceAmount();
			double threshold = parentpointer->Get_Thershold();
			if (iceamount < threshold)
			{
				Fighter* Fi = dynamic_cast<Fighter*>(parentpointer);
				Healer* He = dynamic_cast<Healer*>(parentpointer);
				Freezer* Fr = dynamic_cast<Freezer*>(parentpointer);

				if (Fi != nullptr)
				{
					int priorityfighter;
					Frosted_Fighters--;
					ActiveCount++;
					Q_fighters.push(Fi, 0);
				}
				else if (He != nullptr)
				{
					Frosted_Healers--;
					ActiveCount++;
					S_Healers.Push(He);
				}
				else if (Fr != nullptr)
				{
					Frosted_Freezers--;
					ActiveCount++;
					Q_freezers.enqueue(Fr);
				}
				Continue_ = true;  // you can delete if you want
			}
			else
			{
				// to return to the
				double Icepriority = 1 / parentpointer->GetIceAmount();
				Q_froozen.push(parentpointer, Icepriority);
				Continue_ = false;
			}
		}
	}
}


string Battle::OpenWindow(const string& Message) 
{
	const int BUFSIZE = 512;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.lpstrFilter = "Text Files\0*.txt\0";
	ofns.nMaxFile = BUFSIZE;
	ofns.lpstrTitle = Message.c_str();
	GetOpenFileName(&ofns);
	return buffer;
}


void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}
void Battle::AddtoBEnemiesForDraw(Enemy* Ptr)//added by Nour
{
	if (EnemyCount < MaxEnemyCount)
	{
		BEnemiesForDraw[EDrawCount++] = Ptr;

	}
}


Castle* Battle::GetCastle()
{
	return & BCastle;
}


void Battle::RunSimulation()//starting the battle
{
	//bool flag = true;// added by Nour
	Parsing();
	pGUI = new GUI;//create a new GUI with pGUI pointing to it
	PROG_MODE	mode = pGUI->getGUIMode();
	//while (flag == true)//added by Nour
	//{
		//-------------------------------Added by Nour----------------------------------------//
	keytype key = pGUI->GetPress();

	//if (key != 2)
	//{
	//	//cout << "Lets Play" << endl; //for debugging 
	//	#pragma comment(lib,"winmm.lib")
	//	PlaySound("jujutsukaisen.wav", NULL, SND_ASYNC);
	//}
	//else { PlaySound("pszSound", NULL, SND_ASYNC); }
	////------------------------------------------------------------------------------------//
	setisModeSelected(false);
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		setisModeSelected(true);//added by Nour
		InteractiveMode();//added by Nour
		break;
	case MODE_STEP:
		setisModeSelected(true);//added by Nour
		StepMode();//added by nour
		break;
	case MODE_SLNT:
		SilentMode();//added by nour
		break;
	case MODE_DEMO://to be removed "nour"
		//Just_A_Demo();
		break;
	}
	delete pGUI;//deletes the interface 
}




void Battle::InteractiveMode()//added by nour
{
	state = CONT;
	bool flag = false;
	
	setCurrentTimetep(0);
	KilledCount = 0;
	pGUI->UpdateInterface(CurrentTimeStep);

	pGUI->FlushForClick();//Needed to change pWind to public because of flushing issues 

	CheckGameStatus();
	while (state==CONT)	//as long as some enemies are alive (should be updated in next phases)//by Nour
	{

		pGUI->waitForClick();	//check if click is inside the yellow box//by Nour
		CurrentTimeStep++;//by Nour
		//pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive//by Nour
		

		ActivateEnemies();//by Nour
		
		
	
		ActivateSuperSolidiers(CurrentTimeStep);
		
		Manger_Battle();

		Set_Frosted_num();
		Set_Killed_num();
		///////////Update Battle Info/////////////// by Rodina
		pGUI->Set_Active_Healers(S_Healers.getSize());
		pGUI->Set_Active_Freezers(Q_freezers.getSize());
		pGUI->Set_Active_Fighters(Q_fighters.getSize());


		pGUI->Set_Frosted_Healers(Frosted_Healers);
		pGUI->Set_Frosted_Freezers(Frosted_Freezers);
		pGUI->Set_Frosted_Fighters(Frosted_Fighters);


		pGUI->Set_Killed_Healers(Killed_Healers);
		pGUI->Set_Killed_Freezers(Killed_Freezers);
		pGUI->Set_Killed_Fighters(Killed_Fighters);


		///////////////Update_castle_Info/////////// by Rodina
		pGUI->Set_Castle_Health(BCastle.GetHealth());
		pGUI->Set_Castle_Status(BCastle.Get_Frosted());

		Unfreezing();
		UpdateEnemies();//by Nour
		ActiveForMove.copyQueue(CopyofActive);//Nour
		ActOnAllHealers(S_Healers);//Nour
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->AddSSToDrawingList(currSS);
		pGUI->UpdateInterface(CurrentTimeStep);

		BCastle.Set_Frosted();
		CheckGameStatus();
	
	}

	OutputFile();

	


}
void Battle::SilentMode()//added by nour
{

}

void  Battle::CheckGameStatus()
{
	if (Q_fighters.isEmpty() && S_Healers.Isempty() && Q_freezers.isEmpty() && BCastle.GetHealth() != BCastle.getOriginalHealth() && Q_Inactive.isEmpty())
		state = WIN;
	else if (BCastle.GetHealth() == 0)
		state = LOSS;
	else  if (BCastle.GetHealth() == 0 && CurrentTimeStep == 300)
		state = DRAWN;
	else
		state = CONT;
}


void Battle::StepMode()//added by nour
{
	//char c = NULL;
	//keytype key = pGUI->pWind->GetKeyPress(c);
	//CurrentTimeStep = 0;

	bool flag = false;

	setCurrentTimetep(0);
	KilledCount = 0;
	pGUI->UpdateInterface(CurrentTimeStep);


	
	while (state == CONT)	//as long as some enemies are alive (should be updated in next phases)//by Nour
	{
		CurrentTimeStep++;
		Sleep(1000);
		pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
	
		ActivateEnemies();//by Nour
		UpdateEnemies();//by Nour

		//Freezing2ActiveEnemies(); 
		//Defreezing2ActiveEnemies();

		ActivateSuperSolidiers(CurrentTimeStep);
		BCastle.Act_Castle_Fighters(Q_fighters, EnemyCount, L_Killed, S_Healers, Q_freezers, CurrentTimeStep, true, Q_froozen);
		pGUI->UpdateInterface(CurrentTimeStep);//by Nour
		///////////Update Battle Info/////////////// by Rodina
		pGUI->Set_Active_Healers(S_Healers.getSize());
		pGUI->Set_Active_Freezers(Q_freezers.getSize());
		pGUI->Set_Active_Fighters(Q_fighters.getSize());


		pGUI->Set_Frosted_Healers(Frosted_Healers);
		pGUI->Set_Frosted_Freezers(Frosted_Freezers);
		pGUI->Set_Frosted_Fighters(Frosted_Fighters);


		pGUI->Set_Killed_Healers(Killed_Healers);
		pGUI->Set_Killed_Freezers(Killed_Freezers);
		pGUI->Set_Killed_Fighters(Killed_Fighters);


		///////////////Update_castle_Info/////////// by Rodina
		pGUI->Set_Castle_Health(BCastle.GetHealth());
		pGUI->Set_Castle_Status(BCastle.Get_Frosted());

		/// ///////
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
	
		pGUI->UpdateInterface(CurrentTimeStep);


		//kill 1 enemy added by Nour
		if (S_Healers.getSize() != 0 && Killed_Healers != 1 && ActiveCount != 1 && flag == false)
		{
			Healer* killed = nullptr;
			//Enemy* PE = killed;
			S_Healers.Pop(killed);
			killed->SetStatus(KILD);//edited by Nour
			L_Killed.enqueue(killed);
			Killed_Healers++;

		}
		Unfreezing();

		UpdateEnemies();

		ActiveForMove.copyQueue(CopyofActive);//Nour
		ActOnAllHealers(S_Healers);//Nour


		pGUI->ResetDrawingList();//by Nour
		AddAllListsToDrawingList();//by Nour
		pGUI->AddSSToDrawingList(currSS);
		
		pGUI->UpdateInterface(CurrentTimeStep);//by Nour
	
		

		BCastle.Set_Frosted();
		CheckGameStatus();


    }

	OutputFile();
}





//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//-------------------------------added by Nour-------------------------------------//
	int KilledCount;
	Enemy* const* KilledList = L_Killed.toArray(KilledCount);
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(KilledList[i]);
	
	int FrostedCount;
	Enemy* const* FrostedList = Q_froozen.toArray(FrostedCount);
	for (int i = 0; i < FrostedCount; i++)
		pGUI->AddToDrawingList(FrostedList[i]);

	


	int HealersCount;
	Healer* const* HealersList = S_Healers.toArray(HealersCount);
	for (int i = 0; i < HealersCount; i++)
	{
		pGUI->AddToDrawingList(HealersList[i]);

	}

	int FighterCount;
	Fighter* const* FighterList = Q_fighters.toArray(FighterCount);
	for (int i = 0; i < FighterCount; i++)
		pGUI->AddToDrawingList(FighterList[i]);

	int FreezersCount;
	Freezer* const* FreezersList = Q_freezers.toArray(FreezersCount);
	for (int i = 0; i < FreezersCount; i++)
	{
		pGUI->AddToDrawingList(FreezersList[i]);
	}

}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy* pE;

	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;
		else if (pE->GetArrvTime() == CurrentTimeStep)
		{
			ActiveCount++;
			Q_Inactive.dequeue(pE);	      //remove enemy from the queue
			ActiveForMove.enqueue(pE);
			pE->SetStatus(ACTV);	     //make status active

			Fighter* Fi = dynamic_cast<Fighter*>(pE);
			Healer* He = dynamic_cast<Healer*>(pE);
			Freezer* Fr = dynamic_cast<Freezer*>(pE);



			if (Fi != NULL)
			{
				double priority;
				double dis = (double)Fi->GetDistance();
				if (Fi->Get_Health() > Fi->Get_Original_Health() / 2)
					priority = (1 / (dis)*Fi->Get_Power()) - Fi->getTimeRemaning();
				else {
					priority = (0.5 / dis) * Fi->Get_Power() - Fi->getTimeRemaning();
				}
				Q_fighters.push(Fi, priority);

				Fi->SetStatus(ACTV);
			}
			else if (He != NULL)
			{
				S_Healers.Push(He);
				He->SetStatus(ACTV);
			}
			else if (Fr != NULL)
			{
				Q_freezers.enqueue(Fr);
				Fr->SetStatus(ACTV);
			}

		}
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}
}
void Battle::UpdateEnemies()
{
	Enemy* pE;
	double health = 0;
	double ice = 0;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < ActiveCount; i++)
	{
		
		//pE = BEnemiesForDraw[i];
		if (ActiveCount != 0)
		{
			ActiveForMove.dequeue(pE);
			if (pE->GetStatus() == ACTV)
			{
				ActiveForMove.enqueue(pE);
			}
			Fighter* Fi = dynamic_cast<Fighter*>(pE);
			Healer* HE = dynamic_cast<Healer*>(pE);
			Freezer* Fr = dynamic_cast<Freezer*>(pE);


			if (pE->GetStatus() == ACTV)
			{
				if (Fi != nullptr) {
					Fi->Move();
					double Damage = Fi->Act();
					Fi->DecreaseTimeRemaning();
					BCastle.DecreaseHealth(Damage);

					health = Fi->Get_Health();
					cout<<"Fighter ID "<<Fi->GetID() <<" Health: "<< health << endl;
					

				}

				else if (HE != nullptr)
				{
					HE->Move();
					HE->Get_Health();
					health = HE->Get_Health();

					cout << "Healer ID " << HE->GetID() << " Health: " << health << endl;

				}


				else if (Fr != nullptr) {
					Fr->Move();
					ice = Fr->Act();
					Fr->DecreaseTimeRemaning();
					BCastle.FreezingAmount(ice);
					health = Fr->Get_Health();
					cout << "Freezer ID " << Fr->GetID() << " Health: " << health << endl;

				}
			}

		}
	}
}

void Battle::ActivateSuperSolidiers(int currTimeStep) {
	double currHealth = BCastle.GetHealth();
	double origHealth = BCastle.getOriginalHealth();
	Priority_queue<Fighter*> temp;
	Stack<Healer*> temps;
	Queue<Freezer*> ftemp;
	Q_fighters.copyPrioQueue(temp);
	Q_freezers.copyQueue(ftemp);
	S_Healers.copyStack(temps);

	Fighter* f;
	Healer* H;
	Freezer* fr;
	int count = 0;
	if (currHealth > (origHealth / 3))
		return;

	///  Castle Helath behind threshold  

	if (waitingTofSS % 5 == 0 && Achieve == true) {
		currSS = BCastle.getSuperSolider();
		Achieve = false;
		placeOfMaxNE = DistMaxEnemy(ActiveForMove);
	}
	if (currSS != nullptr && currSS->getDistance() != placeOfMaxNE) {
		currSS->Move(placeOfMaxNE);
		Achieve = false;
		return;
	}
	if (currSS != nullptr && currSS->getDistance() == placeOfMaxNE) {
		Achieve = true;
		while (temp.isEmpty() != true && count != 3) {
			temp.pop(f);
			currSS->Act(f, currTimeStep);
			++count;
		}
		if (count != 3) {
			while (ftemp.isEmpty() != true && count != 3) {
				ftemp.dequeue(fr);
				currSS->Act(fr, currTimeStep);
				++count;
			}
		}
		if (count != 3) {
			while (temps.Isempty() != true && count != 3) {
				temps.Pop(H);
				currSS->Act(H, currTimeStep);
				++count;
			}
		}
		++waitingTofSS;
	}

}

void  Battle::setplaceOfMaxNE(int d) {
	placeOfMaxNE = d;
}
int Battle::getplaceOfMaxNE() const {
	return placeOfMaxNE;
}

void Battle::ActOnAllHealers(Stack<Healer*>& Healers)
{
	int n; //No.of Active healers

	Stack<Healer*> temp;
	Healer* T;
	n = Healers.getSize();
	for (int i = 0; i < n; i++)
	{
		Healers.Pop(T);
		T->increaseHealth(CopyofActive);
		temp.Push(T);
	}
	for (int i = 0; i < n; i++)
	{
		temp.Pop(T);
		Healers.Push(T);
	}
}


void Battle::OutputFile() {
	Enemy* e;
	ofstream output;
	int countOfKilled = 0;
	double sumFSD = 0;
	double sumKillDelay=0;
	output.open("OutputFile.txt");
	if (!output) {
		cout << "Could not open output file";
			return ;
	}
	if (state == WIN)
		output << "GAME IS WIN" << endl;
	else if (state == LOSS)
		output << "GAME IS LOSS" << endl;
	else if (state == DRAWN)
		output << "GAME IS DRAWN"<<endl;
	
	while (L_Killed.isEmpty() != true) {
		L_Killed.dequeue(e);
		output << e->getKillingTime() << " " << e->GetID() << " " << e->getFirstShotDelay() << " " << e->getKilldelay() << " " << e->getLifeTime() << endl;
		countOfKilled++;
		sumFSD = sumFSD + e->getFirstShotDelay();
		sumKillDelay = sumKillDelay + e->getKilldelay();
	}

	double averageFSD = sumFSD / ((double)countOfKilled);
	double averageKD = sumKillDelay / ((double)countOfKilled);
	output << "Castle Total Damage = " << BCastle.getOriginalHealth() - BCastle.GetHealth() << endl;
	if (state == WIN) {
		output << "Total Enemies = " << countOfKilled << endl;
		output << "Average First-Shot Delay = " << averageFSD << endl;
		output << "Average Kill Delay = " << averageKD << endl;
	}
	else {
		output << "Total Killed = " << countOfKilled << endl;
		output << "Average First-Shot Delay = " << averageFSD << endl;
		output << "Average Kill Delay = " << averageKD << endl;
	}



	output.close();
}


/*void Battle::Freezing2ActiveEnemies() //by Rodina
{

	Freezer* F_E = nullptr;
	Healer* H_E = nullptr;
	Fighter* FIG_E = nullptr;

	if (Q_freezers.getSize() >= 2)
	{
		Q_freezers.dequeue(F_E);
		F_E->SetStatus(FRST);

		Q_froozen.enqueue(F_E);
		Frosted_Freezers++;
		FrostedCount++;
		ActiveCount--;


		Q_freezers.dequeue(F_E);
		F_E->SetStatus(FRST);

		Q_froozen.enqueue(F_E);
		Frosted_Freezers++;
		FrostedCount++;
		ActiveCount--;

	}
	if (S_Healers.getSize() >= 2)
	{
		S_Healers.Pop(H_E);
		H_E->SetStatus(FRST);
		Q_froozen.enqueue(H_E);
		FrostedCount++;
		Frosted_Healers++;
		ActiveCount--;

		S_Healers.Pop(H_E);
		H_E->SetStatus(FRST);
		Q_froozen.enqueue(H_E);
		FrostedCount++;
		Frosted_Healers++;
		ActiveCount--;

	}
	if (Q_fighters.getSize() >= 2)
	{

		Q_fighters.pop(FIG_E);
		FIG_E->SetStatus(FRST);
		Q_froozen.enqueue(FIG_E);
		FrostedCount++;
		Frosted_Fighters++;
		ActiveCount--;

		Q_fighters.pop(FIG_E);
		FIG_E->SetStatus(FRST);
		Q_froozen.enqueue(FIG_E);
		FrostedCount++;
		Frosted_Fighters++;
		ActiveCount--;

	}


}*/
/*void Battle::Defreezing2ActiveEnemies() //by Rodina
{
	Enemy* enemy;
	Freezer* Fr = nullptr;
	Healer* HE = nullptr;
	Fighter* Fi = nullptr;

	if (Q_froozen.peekFront(enemy) != false && Q_froozen.getSize() >= 2)
	{
		Fi = dynamic_cast<Fighter*>(enemy);
		HE = dynamic_cast<Healer*>(enemy);
		Fr = dynamic_cast<Freezer*>(enemy);



		if (Fr != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_freezers.enqueue(Fr);
			ActiveCount++;
			Frosted_Freezers--;
			FrostedCount--;


			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_freezers.enqueue(Fr);
			ActiveCount++;
			Frosted_Freezers--;
			FrostedCount--;


		}
		else if (HE != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			S_Healers.Push(HE);
			ActiveCount++;
			Frosted_Healers--;
			FrostedCount--;

			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			S_Healers.Push(HE);
			ActiveCount++;
			Frosted_Healers--;
			FrostedCount--;


		}
		else if (Fi != nullptr)
		{
			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_fighters.push(Fi, ActiveCount);
			ActiveCount++;
			Frosted_Fighters--;
			FrostedCount--;



			Q_froozen.dequeue(enemy);
			enemy->SetStatus(ACTV);
			Q_fighters.push(Fi, ActiveCount);
			ActiveCount++;
			Frosted_Fighters--;
			FrostedCount--;



		}

	}

}*/



