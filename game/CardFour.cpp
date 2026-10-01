#include "CardFour.h"

CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number
}

CardFour::~CardFour(void)
{
}

void CardFour::ReadCardParameters(Grid* pGrid)
{
	//This card has no parameters
}

Card* CardFour::CopyCard(CellPosition pos)
{
	CardFour* ptr = new CardFour(pos);
	return ptr;
}

void CardFour::Save(ofstream& OutFile, ObjectType obj_t) {
	Card::Save(OutFile, obj_t);
}
void CardFour::Load(ifstream& Infile) {
	Card::Load(Infile);
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Make the turnskip of the player who stood on the card = 1
	pGrid->PrintErrorMessage("You lose your next turn, click to continue...");
	pPlayer->setTurnsToSkip(1);
}
