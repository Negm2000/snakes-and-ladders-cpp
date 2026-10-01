#pragma once
#include "Card.h"
class CardTwo :public Card
{
	public:
		CardTwo(const CellPosition& pos);  
		virtual void Apply(Grid* pGrid, Player* pPlayer); 
		virtual ~CardTwo() = default; // A Virtual Destructor

};

