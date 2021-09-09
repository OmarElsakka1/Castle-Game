#include "GUI.h"
#include <time.h>
#include<iostream>
#include <cstdlib>


//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	DrawingItemsCount = 0;
	pWind = new window(WindWidth + 15, WindHeight, 0, 0);
	pWind->ChangeTitle("The Castle ");

	BackgroundClr = WHITE;	//Background color
	StatusBarClr = POWDERBLUE;	//Status bar color

	//Set color for each enemy type
	DrawingColors[FIGHTER] = BLUE;		//fighter-enemy color
	DrawingColors[FREEZER] = ORANGE;		//Frosted-enemy color
	DrawingColors[HEALER] = RED;		//healer-enemy color	
	

	RegionsLabels[INAC] = "INAC";
	RegionsLabels[ACTV] = "ACTV";
	RegionsLabels[FRST] = "FRST";
	RegionsLabels[KILD] = "KILD";

	ClearStatusBar();
	ClearDrawingArea();
	DrawCastleArea();
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
void GUI::FlushForClick() const
{
	pWind->FlushMouseQueue();	//Flush mouse click //added by Nour
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;

		PrintMessage(Label);
	}
	
}
//////////////////////////////////////////////////////////////////////////////////////////
keytype GUI::GetPress() const
{
	char c = NULL;
	keytype key = pWind->GetKeyPress(c);
	key = pWind->GetKeyPress(c);
	cout << "key" << key << endl;
	return key;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const //Prints a message on status bar
{
	ClearStatusBar(); //First clear the status bar

	pWind->SetPen(WHITE);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(150, WindHeight - (int)(StatusBarHeight / 1.1), msg); // You may need to change these coordinates later
																		 // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(WHITE);
	pWind->SetFont(18, BOLD, BY_NAME, "Arial");
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(StatusBarClr, 3);
	pWind->SetBrush(StatusBarClr);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(BackgroundClr, 3);
	pWind->SetBrush(BackgroundClr);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastleArea() const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the Castle
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth / 2, MenuBarHeight, WindWidth / 2, WindHeight - StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the Castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth / 2, YHalfDrawingArea - CastleWidth / 2, WindWidth / 2, YHalfDrawingArea + CastleWidth / 2);
	pWind->DrawLine(WindWidth / 2 - CastleWidth / 2, YHalfDrawingArea, WindWidth / 2 + CastleWidth / 2, YHalfDrawingArea);

	// 5- Writing regions labels
	pWind->SetPen(WHITE);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + (int)(0.1 * L), CastleStartY + 5 * L / 12, RegionsLabels[INAC]);

	pWind->DrawString(WindWidth / 2 + (int)(0.1 * L), CastleStartY + 5 * L / 12, RegionsLabels[ACTV]);

	pWind->DrawString(WindWidth / 2 + (int)(0.1 * L), YHalfDrawingArea + 5 * L / 12, RegionsLabels[FRST]);

	pWind->DrawString(CastleStartX + (int)(0.1 * L), YHalfDrawingArea + 5 * L / 12, RegionsLabels[KILD]);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the passed item in its region
//region count in the numbers of items drawn so far in that item's region
void GUI::DrawSingleEnemy(const DrawingItem* pDitem, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionEnemyCount)
		return; //no more items can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if (RegionCount >= MaxHorizEnemies)	//max no. of enemies to draw in one line
	{
		DrawDistance = (RegionCount - 1) % MaxHorizEnemies + 1;
		YPos = (RegionCount - 1) / MaxHorizEnemies + 1;
	}

	GUI_REGION Region = pDitem->region;

	color pixelClr = BackgroundClr;
	int VertCount;	//Verical enemy count at same distance

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case INAC_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfDrawingArea - EnemyHeight; //
		x = refX - DrawDistance * EnemyWidth - DrawDistance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos
		break;
	case ACTV_REG:
		DrawDistance = pDitem->distance;
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfDrawingArea - EnemyWidth - 1; //
		x = refX + (DrawDistance - 1) * EnemyWidth + DrawDistance; //(Distance)
		y = refY - YPos * EnemyHeight - YPos; // YPos


		pixelClr = pWind->GetColor(x + 1, y + 1);
		VertCount = 0;
		while (pixelClr != BackgroundClr && VertCount < MaxVerticalEnemies)
		{
			y -= (EnemyHeight + 1);
			VertCount++;
			pixelClr = pWind->GetColor(x + 1, y + 1);
		}
		if (VertCount == MaxVerticalEnemies)	//max enemies that can be drawn at same distance exceeded
			return;		//don't draw this enemy

		break;
	case FRST_REG:
		DrawDistance = pDitem->distance;
		refX = (WindWidth / 2 + CastleWidth / 2);
		refY = YHalfDrawingArea + EnemyHeight; //
		x = refX + (DrawDistance - 1) * EnemyWidth + DrawDistance; //(Distance)
		y = refY + (YPos - 1) * EnemyHeight + YPos; // YPos

		pixelClr = pWind->GetColor(x + 1, y + 1);
		VertCount = 0;
		while (pixelClr != BackgroundClr && VertCount < MaxVerticalEnemies)
		{
			y += (EnemyHeight + 1);
			VertCount++;
			pixelClr = pWind->GetColor(x + 1, y + 1);
		}
		if (VertCount == MaxVerticalEnemies)	//max enemies that can be drawn at same distance exceeded
			return;		//don't draw this enemy

		break;
	case KILD_REG:
		refX = (WindWidth / 2 - CastleWidth / 2);
		refY = YHalfDrawingArea + EnemyHeight; //
		x = refX - DrawDistance * EnemyWidth - DrawDistance; //(Distance)
		y = refY + (YPos - 1) * EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the item
	pWind->SetPen(pDitem->clr);
	pWind->SetBrush(pDitem->clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);

}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw all items in DrawingList and ensure there is no overflow in the drawing*/
void GUI::DrawAllItems()
{
	//Prepare counter for each region
	int RegionsCounts[REG_CNT] = { 0 };	//initlaize all counters to zero

	DrawingItem* pDitem;
	for (int i = 0; i < DrawingItemsCount; i++)
	{
		pDitem = DrawingList[i];
		RegionsCounts[pDitem->region]++;
		DrawSingleEnemy(DrawingList[i], RegionsCounts[pDitem->region]);
	}
}


//prints info on status bar. 
//Info includes timestep and other enemies info as illustrated in project doc
void GUI::UpdateStatusBar(int CurrentTimeStep)
{
	string castle_Status;

	//print current timestep
	char strTimestep[10];
	itoa(CurrentTimeStep, strTimestep, 10);
	PrintMessage(strTimestep);

	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.1), "Current Timestep: ");
	pWind->DrawString(15, WindHeight - (int)(StatusBarHeight / 1.3), "Active Enemies ");
	pWind->DrawString(15, WindHeight - (int)(StatusBarHeight / 1.6), "No.of Fighters: " + to_string(Active_Fighters));
	pWind->DrawString(15, WindHeight - (int)(StatusBarHeight / 2), "No.of Healers: " + to_string(Active_Healers));
	pWind->DrawString(15, WindHeight - (int)(StatusBarHeight / 2.6), "No.of Freezers: " + to_string(Active_Freezers));
	pWind->DrawString(14, WindHeight - (int)(StatusBarHeight / 3.8), "Total Active Enemies: " + to_string(Active_Healers+ Active_Freezers+ Active_Fighters));


	pWind->DrawString(500, WindHeight - (int)(StatusBarHeight / 1.1), "Castle Health: " + to_string(Castle_Health));
	pWind->DrawString(500, WindHeight - (int)(StatusBarHeight / 1.3), "Killed Enemies ");
	pWind->DrawString(500, WindHeight - (int)(StatusBarHeight / 1.6), "No.of Fighters: " + to_string(Killed_Fighters));
	pWind->DrawString(500, WindHeight - (int)(StatusBarHeight / 2), "No.of Healers: " + to_string(Killed_Healers));
	pWind->DrawString(500, WindHeight - (int)(StatusBarHeight / 2.6), "No.of Freezers: " + to_string(Killed_Freezers));
	pWind->DrawString(499, WindHeight - (int)(StatusBarHeight / 3.8), "Total Killed Enemies: " + to_string(Killed_Healers+ Killed_Freezers+ Killed_Fighters));

	if (Castle_Status == true)
		castle_Status = "Yes!";
	else
	{
		castle_Status = "No";
	}

	pWind->DrawString(900, WindHeight - (int)(StatusBarHeight / 1.1), "Is Castle Frosted?: " + castle_Status);
	pWind->DrawString(900, WindHeight - (int)(StatusBarHeight / 1.3), "Frosted Enemies ");
	pWind->DrawString(900, WindHeight - (int)(StatusBarHeight / 1.6), "No.of Fighters: " + to_string(Frosted_Fighters));
	pWind->DrawString(900, WindHeight - (int)(StatusBarHeight / 2), "No.of Healers: " + to_string(Frosted_Healers));
	pWind->DrawString(900, WindHeight - (int)(StatusBarHeight / 2.6), "No.of Freezers: " + to_string(Frosted_Freezers));
	pWind->DrawString(888, WindHeight - (int)(StatusBarHeight / 3.8), "Total Frosted Enemies: " + to_string(Frosted_Fighters+ Frosted_Healers+ Frosted_Freezers));

	pWind->DrawLine((WindWidth + 450) / 2, (YHalfDrawingArea + 320) - CastleWidth / 2, (WindWidth + 450) / 2, (YHalfDrawingArea + 320) + CastleWidth / 2);
	pWind->DrawLine((WindWidth - 500) / 2, (YHalfDrawingArea + 320) - CastleWidth / 2, (WindWidth - 500) / 2, (YHalfDrawingArea + 320) + CastleWidth / 2);
}

void GUI::UpdateInterface(int CurrentTimeStep)
{
	ClearDrawingArea();
	UpdateStatusBar(CurrentTimeStep);
	DrawCastleArea();
	DrawAllItems();
	//Draw Enemies aat their new postion Nour
}

/*
	AddOrderForDrawing: Adds a new item related to the passed Enemy to the drawing list
*/

void GUI::AddToDrawingList(const Enemy* pE)
{
	DrawingItem* pDitem = new DrawingItem;
	pDitem->ID = pE->GetID();
	pDitem->distance = pE->GetDistance();
	pDitem->region = (GUI_REGION)(pE->GetStatus());	//map status to drawing region	
	int eType = 0;
	// IMPORTANT [TO DO]

	Fighter const* Fi = dynamic_cast<const Fighter*>(pE);
	Healer const* He = dynamic_cast<const Healer*>(pE);
	Freezer const* Fr = dynamic_cast<const Freezer*>(pE);


	if (Fi !=NULL)
	{
		eType = 0;
	}
	else if (He != NULL)
	{
		eType = 1;
	}
	else if (Fr != NULL)
	{
		eType = 2;
	}
	// enemy type has been generated randomly here because enemy classes are not written yet
	// in next phases, to know enemy type, you should apply dynamic_cast to pE pointer
	 //pDitem->ID % ENMY_TYPE_CNT;
	pDitem->clr = DrawingColors[eType];
	/////////////
	/////////////

	DrawingList[DrawingItemsCount++] = pDitem;	//add item to the list
}


void GUI::ResetDrawingList()
{
	for (int i = 0; i < DrawingItemsCount; i++) {
		delete DrawingList[i];
		DrawingList[i] = nullptr;
	}

	DrawingItemsCount = 0;
}
//void GUI::DrawAllEnemies(Enemy* enemies[], int size) const
//{
//
//}

bool GUI::InDrawingArea(int y)
{
	if ((y > StatusBarHeight) && (y < DrawingAreaHeight))
	{
		return true;
	}
	else return false;
}
int GUI::getDrawingItemsCount() const
{
	return DrawingItemsCount;
}
//////////////////////////////////
void GUI::Set_Active_Fighters(int fighters)
{
	Active_Fighters = fighters;
}
void GUI::Set_Active_Freezers(int Freezers)
{
	Active_Freezers = Freezers;
}
void GUI::Set_Active_Healers(int Healers)
{
	Active_Healers = Healers;
}



void GUI::Set_Frosted_Fighters(int Frozen_Fighters)
{
	Frosted_Fighters = Frozen_Fighters;
}
void GUI::Set_Frosted_Freezers(int Frozen_Freezers)
{
	Frosted_Freezers = Frozen_Freezers;
}
void GUI::Set_Frosted_Healers(int Frozen_Healers)
{
	Frosted_Healers = Frozen_Healers;
}

void GUI::Set_Killed_Fighters(int Fighters)
{
	Killed_Fighters = Fighters;
}
void GUI::Set_Killed_Freezers(int Freezers)
{
	Killed_Freezers = Freezers;
}
void GUI::Set_Killed_Healers(int Healers)
{
	Killed_Healers = Healers;
}


void GUI::Set_Castle_Health(double health)
{
	Castle_Health = health;
}
void GUI::Set_Castle_Status(bool state)
{
	Castle_Status = state;
}
PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("Please select GUI mode: (1)Interactive, (2)StepByStep, (3)Silent, (4)DEMO... ");
		string S = GetString();
		Mode = (PROG_MODE)(atoi(S.c_str()) - 1);
	} 	while (Mode < 0 || Mode >= MODE_CNT);
	return Mode;
}

void GUI::AddSSToDrawingList(const SuperSoldiers* pE)
{
	if (pE != nullptr) {
		DrawingItem* pDitem = new DrawingItem;
		pDitem->ID = 0;
		pDitem->distance = pE->getDistance();
		pDitem->region = (GUI_REGION)(pE->getStatus());	//map status to drawing region	
		int eType = 0;

		pDitem->clr = OLIVEDRAB;


		DrawingList[DrawingItemsCount++] = pDitem;	//add item to the list
	}
}
