#include "Battle.h"
#include "GUI\GUI.h"

int main()
{
	
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	
	delete pGameBattle;
	
	return 0;
}
