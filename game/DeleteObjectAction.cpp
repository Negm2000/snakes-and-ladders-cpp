#include "DeleteObjectAction.h"
#include "Grid.h"


DeleteObjectAction::DeleteObjectAction(ApplicationManager* pApp) : Action(pApp) {}


void DeleteObjectAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_Cell;
	pOut->PrintMessage("Click on the object you want to delete, for snakes and ladders click on the starting cell");
	Temp_Cell = pIn->GetCellClicked();

	if (Temp_Cell.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		return;
	}
	CellToRemove = Temp_Cell;
	pOut->ClearStatusBar();
}

void DeleteObjectAction::Execute() {

	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (CellToRemove.IsValidCell()) {
		
		if (!pGrid->IsThereAnObject(CellToRemove))
			pGrid->RemoveObjectFromCell(CellToRemove);
	
		else pGrid->PrintErrorMessage("Cell has no objects. Click to continue.");
	}

}