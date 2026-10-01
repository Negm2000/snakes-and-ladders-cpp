#include "CardTwo.h"
#include "Ladder.h"

CardTwo::CardTwo(const CellPosition& pos) : Card(pos)
{
	cardNumber = 2; //Setting the inherited cardnumber data member to 2
}


void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	CellPosition PlayerPos = pPlayer->GetCell()->GetCellPosition();
	Ladder* NextLadder = pGrid->GetNextLadder(PlayerPos);
	if (NextLadder)
	{
		CellPosition NextLadderPos = NextLadder->GetPosition();
		pGrid->UpdatePlayerCell(pPlayer, NextLadderPos);
		NextLadder->Apply(pGrid, pPlayer);
	}
}

