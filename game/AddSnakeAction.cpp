#include "AddSnakeAction.h"
#include "Input.h"
#include "Output.h"
#include "Snake.h"



AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	bool Check_Parameters = true;
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_startPos;
	CellPosition Temp_endPos;

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	Temp_startPos = pIn->GetCellClicked();

	if (Temp_startPos.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		Check_Parameters = false;
	}
	else {
		// Read the endPos parameter
		pOut->PrintMessage("New Snake: Click on its End Cell ...");
		Temp_endPos = pIn->GetCellClicked();
		if (Temp_endPos.IsValidCell() == false) {
			pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
			Check_Parameters = false;
		}
	}

	if (Check_Parameters) {
		///TODO: Make the needed validations on the read parameters
		if (Temp_startPos.HCell() == Temp_endPos.HCell()) {
			if (Temp_startPos.VCell() >= Temp_endPos.VCell()) {
				pGrid->PrintErrorMessage("Error,the end positon must be less than the start! Click to continue.");
				Check_Parameters = false;
			}

		}
		else {
			pGrid->PrintErrorMessage("Error,the start and end postion must be vertically aligned! Click to continue.");
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
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user

	//Validation that the cells are valid
	if (startPos.IsValidCell() && endPos.IsValidCell()) {

		Snake* pSnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pSnake);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction

	}
}
