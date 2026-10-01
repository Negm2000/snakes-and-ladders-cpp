#include "CutCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
CutCardAction::CutCardAction(ApplicationManager* pApp) :Action(pApp)
{
}
void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_Cell;
	pOut->PrintMessage("Click on the card that you want to cut");
	Temp_Cell = pIn->GetCellClicked();

	if (Temp_Cell.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		return;
	}
	Cut_Pos = Temp_Cell;
	pOut->ClearStatusBar();
}

void CutCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	if (Cut_Pos.IsValidCell()) {
		Cut_Card = dynamic_cast<Card*>(pGrid->GetGameObject(Cut_Pos));

		if (Cut_Card != NULL)
		{
			pGrid->SetClipboard(Cut_Card);
			pGrid->PrintErrorMessage("Card added to clipboard. Click to continue.");
			pGrid->RemoveObjectFromCell(Cut_Pos);
		}
		else {
			pGrid->PrintErrorMessage("No card is present in the cell clicked ! Click to continue .");
		}
	}
}
CutCardAction::~CutCardAction()
{
}