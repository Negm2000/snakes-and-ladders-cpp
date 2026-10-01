#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	bool Check_Parameters = true;
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_startPos;
	CellPosition Temp_endPos;
	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	Temp_startPos = pIn->GetCellClicked();

	if (Temp_startPos.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		Check_Parameters = false;
	}
	else {
		// Read the endPos parameter
		pOut->PrintMessage("New Ladder: Click on its End Cell ...");
		Temp_endPos = pIn->GetCellClicked();
		if (Temp_endPos.IsValidCell() == false) {
			pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
			Check_Parameters = false;
		}
	}

	if (Check_Parameters) {
		///TODO: Make the needed validations on the read parameters
		if (Temp_endPos.HCell() == Temp_startPos.HCell()) {
			if (Temp_startPos.VCell() <= Temp_endPos.VCell()) {
				pGrid->PrintErrorMessage("Error,the end positon must be larger than the start!, Click to continue.");
				Check_Parameters = false;
			}
		}
		else {
			pGrid->PrintErrorMessage("Error,the start and end postion must be vertically alligned!, Click to continue.");
			Check_Parameters = false;
		}

	}
	if (Check_Parameters) {
		startPos = Temp_startPos;
		endPos = Temp_endPos;
	}


	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user

	//Validation that the cells are valid
	if (startPos.IsValidCell() && endPos.IsValidCell()) {

		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pLadder);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

	}
}
