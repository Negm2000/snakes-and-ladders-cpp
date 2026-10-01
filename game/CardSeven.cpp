#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number
}

CardSeven::~CardSeven(void)
{
}


void CardSeven::Apply(Grid* pGrid, Player* pPlayer) {

	Card::Apply(pGrid,pPlayer);
	//0- Get cureent player location
	CellPosition Current_Player_Position = pPlayer->GetCell()->GetCellPosition(); //getting the player position after rolling the dice and advancing
	//1- Check the next player
	Player* Next_Player=pGrid->GetNextPlayer();
	//2- Return him to the start position
	if (Next_Player == NULL) {
		pGrid->PrintErrorMessage("No other players to return to start. Click anywhere to Continue");
		return;
	}
	pGrid->UpdatePlayerCell(Next_Player, 1); //Updates the Player cell with the new position
	pGrid->PrintErrorMessage("Player" +to_string(Next_Player->GetPlayerNumber()) + " will move to the start. Click anywhere to Continue");
}






