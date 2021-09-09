#include "Castle.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::SetPower(double P)
{
	if (P > 0)
		Power = P;
	else
		Power = 0; // killed
}

double Castle::GetPower() const
{
	return Power;
}

void Castle::SetMax_Enemy(int M)
{
	if (M > 0)
		Max_numofenemy = M;
	else
		Max_numofenemy = 0; // killed
}
int Castle::GetMax_Enemy() const
{
	return Max_numofenemy;
}

void Castle::DecreaseHealth(double d) {
	Health = Health - d;
	if (Health < 0)
		Health = 0;
}

Castle::Castle() {
	AmountOfice = 0;
	SuperSoldiers* s1 = new SuperSoldiers();
	SuperSoldiers* s2 = new SuperSoldiers();
	SuperSoldiers* s3 = new SuperSoldiers();
	QSuperS.enqueue(s1);
	QSuperS.enqueue(s2); 
	QSuperS.enqueue(s3);
	
}
Castle::~Castle() 
{
	SuperSoldiers* s1;
	if (QSuperS.isEmpty() != true) {
		while (QSuperS.isEmpty() != true)
			QSuperS.dequeue(s1);
		delete s1;
	}
}


SuperSoldiers* Castle::getSuperSolider() 
{
	SuperSoldiers* s1 = nullptr;
	if (QSuperS.isEmpty() == true)
		return nullptr;
	else if (QSuperS.isEmpty() == false) {
		QSuperS.dequeue(s1);
	}
	return s1;
}
void Castle::setOriginalHealth(double oh) {
	OriginalHealth = oh;
}
double Castle::getOriginalHealth() const {
	return OriginalHealth;
}

bool Castle::Get_Frosted() const
{
	return Frosted;
}

void Castle::Set_Frosted()
{
	if (Frosted == true)
		Frosted = false;

	else if (AmountOfice >= (Health / 2))
	{

		Frosted = true;
		AmountOfice = 0;
	}
	else
		Frosted = false;

}

void Castle::FreezingAmount(double ice)
{
	AmountOfice = AmountOfice + ice;

}

void Castle::Act_Castle_Fighters(Priority_queue<Fighter*>& Q_fighters, int N, Queue<Enemy*>& L_Killed, Stack<Healer*>& S_Healers, Queue<Freezer*>& Q_freezers, int TimeStep, bool THROWICE, Priority_queue<Enemy*>& Q_froozen)//return false if no one to kill
{
	if (Q_fighters.getSize() >= N)
	{
		int counter = 0;
		Queue<Fighter*> temp;
		Queue<Fighter*> tempICE;
		for (int i = 0; i < N; i++)
		{
			counter++;
			Fighter* fighter;
			Q_fighters.pop(fighter);

			double health = fighter->Get_Health();
			int pow = fighter->Get_Power();
			int distance = fighter->GetDistance();
			double damage;
			double k = 1;
			damage = pow / (k * distance);
			if (THROWICE && counter % 5 == 0)
			{
				fighter->Set_Frosted();
				tempICE.enqueue(fighter);
			}
			else
			{
				if (fighter->getTimeFirstShot() == -1)
				{
					fighter->setTimeFirstShot(TimeStep);
				}
				if ((health - damage) > 0)
				{
					fighter->Set_Health(health - damage);
					temp.enqueue(fighter);
				}
				else
				{
					fighter->setKillingTime(TimeStep);
					fighter->Set_Health(0);
					fighter->SetStatus(KILD);
					L_Killed.enqueue(fighter);
				}
			}
		}

		for (int i = 0; i < temp.getSize(); i++)
		{
			Fighter* tempfighter;
			temp.dequeue(tempfighter);
			double health_ = tempfighter->Get_Health();
			int power_ = tempfighter->Get_Power();
			int distance_ = tempfighter->GetDistance();
			double damage = power_ / (1 * distance_);
			double priority = damage - tempfighter->getTimeRemaning();
			Q_fighters.push(tempfighter, priority);
		}

		if (tempICE.getSize() != 0)
		{
			for (int i = 0; i < tempICE.getSize(); i++)
			{
				Fighter* Icedfighter;
				tempICE.dequeue(Icedfighter);
				Enemy* pointer = Icedfighter;
				if (pointer->IsFrosted())
				{
					double Icepriority = 1 / Icedfighter->GetIceAmount();
					Q_froozen.push(pointer, Icepriority);
				}
				else
				{
					double priorityfighter; ////// to eeeeeeddddiiiiitttttt
					Q_fighters.push(Icedfighter, 0);
				}
			}
		}


	}
	else if (Q_fighters.getSize() < N && (Q_fighters.getSize() + S_Healers.getSize()) >= N)
	{
		int counter = 0;
		Queue<Fighter*> temp;
		Queue<Fighter*> tempICE;
		for (int i = 0; i < Q_fighters.getSize(); i++)
		{
			counter++;
			Fighter* fighter;
			Q_fighters.pop(fighter);

			double health = fighter->Get_Health();
			int pow = fighter->Get_Power();
			int distance = fighter->GetDistance();
			double damage;
			double k = 1;
			damage = pow / (k * distance);
			if (THROWICE && counter % 5 == 0)
			{
				fighter->Set_Frosted();
				tempICE.enqueue(fighter);
			}
			else
			{
				if (fighter->getTimeFirstShot() == -1)
				{
					fighter->setTimeFirstShot(TimeStep);
				}
				if ((health - damage) > 0)
				{
					fighter->Set_Health(health - damage);

					temp.enqueue(fighter);
				}
				else
				{
					fighter->setKillingTime(TimeStep);
					fighter->Set_Health(0);
					fighter->SetStatus(KILD);
					L_Killed.enqueue(fighter);
				}
			}
		}

		// to return back the temp content again to the priorityqueue
		for (int i = 0; i < temp.getSize(); i++)
		{
			Fighter* tempfighter;
			temp.dequeue(tempfighter);
			double health_ = tempfighter->Get_Health();
			int power_ = tempfighter->Get_Power();
			int distance_ = tempfighter->GetDistance();
			double damage = power_ / (1 * distance_);
			double priority = damage - tempfighter->getTimeRemaning();
			Q_fighters.push(tempfighter, priority);
		}

		if (tempICE.getSize() != 0)
		{
			for (int i = 0; i < tempICE.getSize(); i++)
			{
				Fighter* Icedfighter;
				tempICE.dequeue(Icedfighter);
				Enemy* pointer = Icedfighter;
				if (pointer->IsFrosted())
				{
					double Icepriority = 1 / Icedfighter->GetIceAmount();
					Q_froozen.push(pointer, Icepriority);
				}
				else
				{
					double priorityfighter; ////// to eeeeeeddddiiiiitttttt

					// count necessary
					Q_fighters.push(Icedfighter, 0);
				}
			}
		}


		Stack<Healer*> temp2;
		Stack<Healer*> tempICE2;
		for (int j = 0; j < N - Q_fighters.getSize(); j++)
		{
			counter++;
			Healer* healer;
			S_Healers.Pop(healer);

			double health2 = healer->Get_Health();
			int pow2 = healer->Get_Power();
			int distance2 = healer->GetDistance();
			double damage2;
			double k2 = 2;
			damage2 = pow2 / (k2 * distance2);
			if (THROWICE && counter % 5 == 0)
			{
				healer->Set_Frosted();
				tempICE2.Push(healer);
			}
			else
			{
				if (healer->getTimeFirstShot() == -1)
				{
					healer->setTimeFirstShot(TimeStep);
				}
				if ((health2 - damage2) > 0)
				{
					healer->Set_Health(health2 - damage2);
					temp2.Push(healer);
				}
				else
				{
					healer->setKillingTime(TimeStep);
					healer->Set_Health(0);
					if (healer->GetDistance() <= 5)
					{
						double H = this->GetHealth();
						this->SetHealth(1.03 * H);
					}
					healer->SetStatus(KILD);
					L_Killed.enqueue(healer);
				}
			}

		}

		// to return back the temp2 content again to the stack
		for (int i = 0; i < temp2.getSize(); i++)
		{
			Healer* temphealer;
			temp2.Pop(temphealer);
			S_Healers.Push(temphealer);
		}

		if (tempICE2.getSize() != 0)
		{
			for (int i = 0; i < tempICE2.getSize(); i++)
			{
				Healer* Icedhealer;
				tempICE2.Pop(Icedhealer);
				Enemy* pointer2 = Icedhealer;
				if (pointer2->IsFrosted())
				{
					double Icepriority = 1 / Icedhealer->GetIceAmount();
					Q_froozen.push(pointer2, Icepriority);
				}
				else
				{
					S_Healers.Push(Icedhealer);
				}
			}
		}



	}
	else if ((Q_fighters.getSize() + S_Healers.getSize()) < N)
	{
		int counter = 0;
		Queue<Fighter*>temp;
		Queue<Fighter*> tempICE;
		for (int i = 0; i < Q_fighters.getSize(); i++)
		{
			counter++;
			Fighter* fighter;
			Q_fighters.pop(fighter);
			double health = fighter->Get_Health();
			int pow = fighter->Get_Power();
			int distance = fighter->GetDistance();
			double damage;
			double k = 1;
			damage = pow / (k * distance);
			if (THROWICE && counter % 5 == 0)
			{
				fighter->Set_Frosted();
				tempICE.enqueue(fighter);
			}
			else
			{
				if (fighter->getTimeFirstShot() == -1)
				{
					fighter->setTimeFirstShot(TimeStep);
				}
				if ((health - damage) > 0)
				{
					fighter->Set_Health(health - damage);
					temp.enqueue(fighter);
				}
				else
				{
					fighter->setKillingTime(TimeStep);
					fighter->Set_Health(0);
					fighter->SetStatus(KILD);
					L_Killed.enqueue(fighter);
				}
			}
		}


		// to return back the temp content again to the priorityqueue
		for (int i = 0; i < temp.getSize(); i++)
		{
			Fighter* tempfighter;
			temp.dequeue(tempfighter);
			double health_ = tempfighter->Get_Health();
			int power_ = tempfighter->Get_Power();
			int distance_ = tempfighter->GetDistance();
			double damage = power_ / (1 * distance_);
			double priority = damage - tempfighter->getTimeRemaning();
			Q_fighters.push(tempfighter, priority);
		}


		if (tempICE.getSize() != 0)
		{
			for (int i = 0; i < tempICE.getSize(); i++)
			{
				Fighter* Icedfighter;
				tempICE.dequeue(Icedfighter);
				Enemy* pointer = Icedfighter;
				if (pointer->IsFrosted())
				{
					double Icepriority = 1 / Icedfighter->GetIceAmount();
					Q_froozen.push(pointer, Icepriority);
				}
				else
				{
					double priorityfighter; ////// to eeeeeeddddiiiiitttttt
					Q_fighters.push(Icedfighter, 0);
				}
			}
		}


		Stack<Healer*> temp2;
		Stack<Healer*> tempICE2;
		for (int i = 0; i < S_Healers.getSize(); i++)
		{
			Healer* healer;
			S_Healers.Pop(healer);

			double health2 = healer->Get_Health();
			int pow2 = healer->Get_Power();
			int distance2 = healer->GetDistance();
			double damage2;
			double k2 = 2;
			damage2 = 50*pow2 / (k2 * distance2);  // modified

			if (THROWICE && counter % 5 == 0)
			{
				healer->Set_Frosted();
				tempICE2.Push(healer);
			}
			else
			{
				if (healer->getTimeFirstShot() == -1)
				{
					healer->setTimeFirstShot(TimeStep);
				}
				if ((health2 - damage2) > 0)
				{
					healer->Set_Health(health2 - damage2);
					temp2.Push(healer);
				}
				else
				{
					healer->setKillingTime(TimeStep);
					healer->Set_Health(0);
					if (healer->GetDistance() <= 5)
					{
						double H = this->GetHealth();
						this->SetHealth(1.03 * H);
					}
					healer->SetStatus(KILD);
					L_Killed.enqueue(healer);
				}
			}
		}

		// to return back the temp2 content again to the stack
		while (temp2.Isempty()!=true)
		{
			Healer* temphealer;
			temp2.Pop(temphealer);
			S_Healers.Push(temphealer);
		}


		if (tempICE2.getSize() != 0)
		{
			for (int i = 0; i < tempICE2.getSize(); i++)
			{	
				Healer* Icedhealer;
				tempICE2.Pop(Icedhealer);
				Enemy* pointer2 = Icedhealer;
				if (pointer2->IsFrosted())
				{
					double Icepriority = 1 / Icedhealer->GetIceAmount();
					Q_froozen.push(pointer2, Icepriority);
				}
				else
				{
					S_Healers.Push(Icedhealer);
				}
			}
		}


		if (N - (Q_fighters.getSize() + S_Healers.getSize()) < Q_freezers.getSize())
		{

			for (int i = 0; i < N - (Q_fighters.getSize() + S_Healers.getSize()); i++)
			{
				counter++;
				Freezer* freezer;
				Q_freezers.dequeue(freezer);

				double health3 = freezer->Get_Health();
				int pow3 = freezer->Get_Power();
				int distance3 = freezer->GetDistance();
				double damage3;
				double k3 = 1;
				damage3 = pow3 / (k3 * distance3);
				if (THROWICE && counter % 5 == 0)
				{
					freezer->Set_Frosted();
					Enemy* pointer3 = freezer;
					if (pointer3->IsFrosted())
					{
						double Icepriority = 1 / freezer->GetIceAmount();
						Q_froozen.push(pointer3, Icepriority);
					}
					else
					{
						Q_freezers.enqueue(freezer);
					}
				}
				else
				{
					if (freezer->getTimeFirstShot() == -1)
					{
						freezer->setTimeFirstShot(TimeStep);
					}
					if ((health3 - damage3) > 0)
					{
						freezer->Set_Health(health3 - damage3);
						Q_freezers.enqueue(freezer);

					}
					else
					{
						freezer->setKillingTime(TimeStep);
						freezer->Set_Health(0);
						freezer->SetStatus(KILD);
						L_Killed.enqueue(freezer);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < Q_freezers.getSize(); i++)
			{
				counter++;
				Freezer* freezer;
				Q_freezers.dequeue(freezer);

				double health3 = freezer->Get_Health();
				int pow3 = freezer->Get_Power();
				int distance3 = freezer->GetDistance();
				double damage3;
				double k3 = 1;
				damage3 = pow3 / (k3 * distance3);
				if (THROWICE && counter % 5 == 0)
				{
					freezer->Set_Frosted();
					Enemy* pointer3 = freezer;
					if (pointer3->IsFrosted())
					{
						double Icepriority = 1 / freezer->GetIceAmount();
						Q_froozen.push(pointer3, Icepriority);
					}
					else
					{
						Q_freezers.enqueue(freezer);
					}
				}
				else
				{
					if (freezer->getTimeFirstShot() == -1)
					{
						freezer->setTimeFirstShot(TimeStep);
					}
					if ((health3 - damage3) > 0)
					{
						freezer->Set_Health(health3 - damage3);
						Q_freezers.enqueue(freezer);
					}
					else
					{
						freezer->setKillingTime(TimeStep);
						freezer->Set_Health(0);
						freezer->SetStatus(KILD);
						L_Killed.enqueue(freezer);
					}
				}
			}
		}

	}

}