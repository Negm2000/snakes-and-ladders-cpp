#include "InputDiceAction.h"
#include "Grid.h"
#include "Player.h"


InputDiceAction::InputDiceAction(ApplicationManager* pApp) : Action(pApp), diceNumber(0)
{
}

void InputDiceAction::ReadActionParameters()
{
	// TODO: Read valid diceNumber from the user and set it to the data member "diceNumber"

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	// 2- Display “please enter a dice value between 1-6”
	pOut->PrintMessage("Please enter a dice value between 1-6: ");

	// 3- Read a valid Integer from the user

	diceNumber = pIn->GetInteger(pOut);

	// 4- Validate the Integer (must be 1-6)

	while (diceNumber < 1 || diceNumber > 6) {
		pOut->PrintMessage("Please enter a valid dice value between 1-6");
		diceNumber = pIn->GetInteger(pOut);
	}

	// 5- Clear the status bar
	pOut->ClearStatusBar();



}

void InputDiceAction::Execute()
{
	// 1- The first line of any Action Execution is to read its parameter first

	ReadActionParameters();


	// 2- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid = pManager->GetGrid();

	// -- If not ended, do the following --:
	if (!pGrid->GetEndGame()) {


		// 3 Get the "current" player from pGrid


		Player* current_player = pGrid->GetCurrentPlayer();
		
		if (current_player->poisonCheck(pGrid))
		{
			diceNumber--;
			pGrid->PrintErrorMessage("Poisoned, you move " + to_string(diceNumber) + " slots");
		}

		// 4- Move the currentPlayer using function Move of class player

		current_player->Move(pGrid, diceNumber);

		// 5- Advance the current player number of pGrid

		pGrid->AdvanceCurrentPlayer();

		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
	}
}

InputDiceAction::~InputDiceAction()
{
}