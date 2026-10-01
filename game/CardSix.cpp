#include "CardSix.h"
CardSix::CardSix(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (1 here)
}

void CardSix::ReadCardParameters(Grid* pGrid)
{

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_Cell;
	// 2- Read an Cell_Move_To using getCellClicked
	//    Don't forget to first print to a descriptive message to the user like:"New CardSix: Select the Cell to Move to  ..."
	pOut->PrintMessage("New CardSix: Select the Cell to Move to  ...");
	Temp_Cell = pIn->GetCellClicked();

	while (Temp_Cell.IsValidCell()==false) {
		pOut->PrintMessage("Invalid Cell! Select again.");
		Temp_Cell = pIn->GetCellClicked();
	}	
	Cell_Move_To = Temp_Cell;

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}
void CardSix::Apply(Grid* pGrid, Player* pPlayer) {
	
		Card::Apply(pGrid, pPlayer);
		pGrid->PrintErrorMessage("Player will move to cell " + to_string(Cell_Move_To.GetCellNum()) + ".Click anywhere to Continue");
		pGrid->UpdatePlayerCell(pPlayer, Cell_Move_To);

		if (pPlayer->GetCell()->GetGameObject() != NULL) //check if the updated position has a snake or ladder or even a new card
			pPlayer->GetCell()->GetGameObject()->Apply(pGrid, pPlayer);
}

void CardSix::Save(ofstream& OutFile, ObjectType Obj_t)
{
	if (Obj_t == CARD_TYPE)
		OutFile << cardNumber << " " << position.GetCellNum()<<" " << Cell_Move_To.GetCellNum() << endl;
}

void CardSix::Load(ifstream& Infile)
{
	int pos, cellnum;
	Infile >> pos >> cellnum;
	position = CellPosition(pos);
	Cell_Move_To = CellPosition(cellnum);
}
