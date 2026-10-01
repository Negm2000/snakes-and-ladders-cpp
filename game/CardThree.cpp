#include "CardThree.h"


CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; //sets the inherited cardNumber data member with the card number
}


void CardThree::ReadCardParameters(Grid* pGrid)
{
	//No Parameters for CardThree
}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	// Printing a message showing the player the details of card three
	pGrid->PrintErrorMessage("This card gives you another dice roll. Click to continue...");

	//Getting the player number
	int player_num = pPlayer->GetPlayerNumber();

	int prev = pPlayer->GetPlayerNumber()-1 < 0 ? 3 : pPlayer->GetPlayerNumber()-1;

	// Advancing the player turn three times to get back to the same player
	pGrid->SetCurrPlayerNumber(prev);

	pGrid->PrintErrorMessage("Player " + to_string(player_num) + " Got an extra dice roll, Click to continue...");
}

