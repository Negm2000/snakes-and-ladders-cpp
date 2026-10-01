#pragma once
#include "Player.h"
class PowerUp
{
protected:
	Player* Attacker;

	Grid* pGrid;
public:

	PowerUp(Grid* pGrid, Player* attacker);

	Player* getAttacker();

	virtual void Execute() = 0;

	virtual ~PowerUp();
};

