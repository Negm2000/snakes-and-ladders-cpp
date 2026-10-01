#pragma once
#include "Card.h"
class CardTwelve : public Card
{
public:
	CardTwelve(const CellPosition& pos); // A Constructor takes card position


	virtual void Apply(Grid* pGrid, Player* pPlayer);
	Card* CopyCard(CellPosition);
	virtual ~CardTwelve()=default; // A Virtual Destructor
};

