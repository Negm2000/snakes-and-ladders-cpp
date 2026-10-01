#include "RollDiceAction.h"

#include "Grid.h"
#include "Player.h"

#include <time.h> // used to in srand to generate random numbers with different seed

RollDiceAction::RollDiceAction(ApplicationManager *pApp) : Action(pApp)
{
}


void RollDiceAction::ReadActionParameters()
{
	// no parameters to read from user
}

void RollDiceAction::Execute()
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function 

	// 1- Check if the Game is ended (Use the GetEndGame() function of pGrid), if yes, make the appropriate action
	Grid* pGrid =  pManager->GetGrid();
	
	// -- If not ended, do the following --:
	if (!pGrid->GetEndGame()) {

		// 2- Generate a random number from 1 to 6 --> This step is done for you
		srand((int)time(NULL)); // time is for different seed each run
		int diceNumber = 1 + rand() % 6; // from 1 to 6 --> should change seed

		// 3- Get the "current" player from pGrid

		Player* current_player = pGrid->GetCurrentPlayer();


		// 4 - Output the diceNumber to the statusbar of the interface 
		pGrid->PrintErrorMessage("You rolled a " + to_string(diceNumber));

		if (current_player->poisonCheck(pGrid))
		{
			diceNumber--;
			pGrid->PrintErrorMessage("Poisoned, you get roll: " + to_string(diceNumber));

		}

		// 5- Move the currentPlayer using function Move of class player

		current_player->Move(pGrid, diceNumber);

		// 6- Advance the current player number of pGrid

		pGrid->AdvanceCurrentPlayer();

		// NOTE: the above guidelines are the main ones but not a complete set (You may need to add more steps).
	}
}

RollDiceAction::~RollDiceAction()
{
}
