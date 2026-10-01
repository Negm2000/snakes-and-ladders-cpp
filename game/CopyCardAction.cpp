#include "CopyCardAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"
CopyCardAction::CopyCardAction(ApplicationManager* pApp) :Action(pApp)
{
}
void CopyCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_Cell;
	pOut->PrintMessage("Click on the card that you want to copy");
	Temp_Cell = pIn->GetCellClicked();

	if (Temp_Cell.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		return;
	}
	CardPosition = Temp_Cell;
	pOut->ClearStatusBar();
}

void CopyCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	if (CardPosition.IsValidCell()) {

		Copied_Card = dynamic_cast<Card*>(pGrid->GetGameObject(CardPosition));

		if (Copied_Card != NULL)
		{
			pGrid->SetClipboard(Copied_Card);
			pGrid->PrintErrorMessage("Card added to clipboard. Click to continue.");
		}
		else {
			pGrid->PrintErrorMessage("No card is present in the cell clicked ! Click to continue .");
		}
	}
}
CopyCardAction::~CopyCardAction()
{
}