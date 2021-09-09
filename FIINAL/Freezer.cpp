#include "Freezer.h"
Freezer::Freezer(int id, int at, int d) : Enemy(id, at, d)
{
	;
}
void Freezer::Move() {
	if (Health > 0.5 * originalHealth) {
		if (Distance > 2 + Speed)
			Distance -= Speed;
		else if (Distance <= 2 + Speed)
			Distance = 2;
	}
	else {
		if (Distance > 2 + Speed * 0.5)
			Distance -= Speed * 0.5;
		else if (Distance <= 2 + Speed * 0.5)
			Distance = 2;

	}
}

double Freezer::Act() {

	double Amount_of_ice=0; //Thrown on the castle

	if (tRemain != 0)
		return 0;

	if(Health <  (originalHealth / 2))
   Amount_of_ice = ((Power + Health) * 40) / Distance;

	else if (Health >= (originalHealth / 2))
   Amount_of_ice = ((Power + Health) * 60) / Distance;

	tRemain = Reload_Period + 1;
	return Amount_of_ice;
}