#include "PowerUp.h"
#include "Grid.h"


PowerUp::PowerUp(Grid* pGr, Player* attacker) : pGrid(pGr), Attacker(attacker)
{
}

Player* PowerUp::getAttacker()
{
	return Attacker;
}

PowerUp::~PowerUp()
{
}