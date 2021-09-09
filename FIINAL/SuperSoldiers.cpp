#include "SuperSoldiers.h"


int SuperSoldiers::getArrvTime() const {
	return ArrvTime;
}
void SuperSoldiers::setArrvTime(int t) {
	ArrvTime = t;

}
int SuperSoldiers::getDistance() const {
	return Distance;
}
void SuperSoldiers::setDistance(int t) {
	Distance = t;
}
void SuperSoldiers::Move(int placeOfMaxNumbOfEnemies) {
	if (Distance == placeOfMaxNumbOfEnemies)
		return;
	if (Distance >= placeOfMaxNumbOfEnemies) {
		Distance = placeOfMaxNumbOfEnemies;
		return;
	}

		Distance = Distance + speed;
}
void SuperSoldiers::Act(Enemy* enemy , int currTimeStep) const {
	if (enemy == nullptr)
		return;
	int Edis = enemy->GetDistance();
	if ((Edis - Distance) > 2 || (Edis - Distance) < -2)
		return;
	else {
		enemy->SetStatus(KILD);
		enemy->setKillingTime(currTimeStep);
		enemy->Set_Health(0);
		
	}
}

void SuperSoldiers::setStatus(ENMY_STATUS s) {
	status = s;
}
ENMY_STATUS SuperSoldiers::getStatus()const {
	return status;
}



void SuperSoldiers::setHealth(double h) {
	Health = h;
}
void SuperSoldiers::DecreaseHeath(double h) {
	Health = Health - h;
}