#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (1 here)
}


void CardFive::Apply(Grid* pGrid, Player* pPlayer) {
	
	Card::Apply(pGrid,pPlayer); // Call the "you reached card"
	CellPosition Player_Position = pPlayer->GetCell()->GetCellPosition(); //getting the cplayer position after rolling the dice and advancing

	Player_Position.AddCellNum(pPlayer->GetRolledDice() * -2); //Moves double the advanced cells backward
	pGrid->PrintErrorMessage("Player will move back " + to_string(pPlayer->GetRolledDice()) + " steps. Click anywhere to Continue");

	pGrid->UpdatePlayerCell(pPlayer, Player_Position); //Updates the Player cell with the new position

	if (pPlayer->GetCell()->GetGameObject() != NULL) //check if the updated position has a snake or ladder or even a new card
		pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
}
