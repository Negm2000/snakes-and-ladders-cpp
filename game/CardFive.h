#pragma once

#include "Card.h"
//Description
class CardFive :public Card
{
	int Dice_Value;

public:
	CardFive(const CellPosition& pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardEight on the passed Player
	virtual ~CardFive()=default; // A Virtual Destructor
};






