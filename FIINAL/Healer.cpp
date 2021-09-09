#include "Healer.h"
#include<iostream>
using namespace std;
Healer::Healer(int id, int at, int d) : Enemy(id, at, d)
{
	
}
void Healer::Move() {
	if (Health >= 0.5 * originalHealth) {
		if (Backward == false) {
			if (Distance > 2) {
				Distance = Distance - Speed;
			}
			if (Distance <= 2) {
				Distance = 2;
				Backward = true;
			}

		}
		else {

			if (Backward == true) {
				Distance = Distance + Speed;
			}
			if (Distance >= 60) {
				Distance = 60;
				Backward = false;
			}
		}

	}
	else {
		if (Backward == false) {
			if (Distance > 2) {
				Distance = Distance - Speed * 0.5;
			}
			if (Distance <= 2) {
				Distance = 2;
				Backward = true;
			}

		}
		else {

			if (Backward == true) {
				Distance = Distance + Speed * 0.5;
			}
			if (Distance > 60) {
				Distance = 60;
				Backward = false;
			}
		}
	}
}

double Healer::Act() {
	return 0;

}
void Healer::increaseHealth(Queue<Enemy*>& CopyofActiveFormMove)
{
	Queue<Enemy*> TOHEAL;// queue containg pointers of enemies to be healed
	int n = CopyofActiveFormMove.getSize();//get the number of all activeenemies that would be used to heal
	for (int i = 0; i < n; i++)
	{
		Enemy* T;
		CopyofActiveFormMove.dequeue(T);
		if (this->Backward == true)
		{
			if ((this->Distance) - (T->GetDistance()) <= 0 && (this->Distance) - (T->GetDistance()) >= -2)//condition
			{
				TOHEAL.enqueue(T);
			}
		}
		if (this->Backward == false)
		{
			if ((T->GetDistance()) - (this->Distance) <= 0 && (T->GetDistance()) >= -2)
			{
				TOHEAL.enqueue(T);
			}

		}
	}
	// we now have an array of all enemies to heal, lets heal
	if (TOHEAL.isEmpty() != true)
	{
		int m = TOHEAL.getSize();
		Enemy* pE;
		for (int i = 0; i < m; i++)
		{
			TOHEAL.dequeue(pE);
			double HealthCalc = ((((this->Health) + (pE->Get_Health())) / (this->Distance)) * 20);
			if((HealthCalc + pE->Get_Health())< pE->Get_Original_Health())
			pE->Set_Health(HealthCalc+ pE->Get_Health());
			else
			{
				pE->Set_Health(pE->Get_Original_Health());
				
			}
				
		}

	}
}