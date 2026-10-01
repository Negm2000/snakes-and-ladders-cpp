#include "OpenAction.h"
#include "Ladder.h"
#include "Grid.h"
#include "Snake.h"
#include <fstream>
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"


#include <algorithm>


OpenAction::OpenAction(ApplicationManager* pApp) : Action(pApp) {}

void OpenAction::ReadActionParameters() {
	Input* pIn = pManager->GetGrid()->GetInput();
	Output* pOut = pManager->GetGrid()->GetOutput();
	do {
		// 2- Display “Ask user for a file name”
		pOut->PrintMessage("Enter a name for your save file, only alpha-numeric characters allowed: ");

		// 3- Read a valid string from the user
		file_name = pIn->GetSrting(pOut);
		// 4- Clear status bar
		pOut->ClearStatusBar();

	} while (!all_of(file_name.begin(), file_name.end(), isalnum));

}
void OpenAction::Execute() {

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();

	ReadActionParameters();
	ifstream load_file{ "../Sample_Grids/" + file_name + ".txt" };
	// Check if open failed
	if (!load_file) {
		pGrid->PrintErrorMessage("Can't open file");
		return;
	}


	// Load ladders
	int count;
	load_file >> count;

	for (int i = 0; i < count; i++) {
		Ladder* pLadder = new Ladder(-1, -1);
		pLadder->Load(load_file);
		pGrid->AddObjectToCell(pLadder);
	}

	//Load snakes
	load_file >> count;
	for (int i = 0; i < count; i++) {
		Snake* pSnake = new Snake(-1, -1);
		pSnake->Load(load_file);
		pGrid->AddObjectToCell(pSnake);
	}

	//Load cards
	load_file >> count;
	for (int i = 0; i < count; i++) {
		int CardNum;
		load_file >> CardNum;
		Card* pCard = nullptr;
		switch (CardNum) {

		case 1:
			pCard = new CardOne(-1);
			break;

		case 2:
			pCard = new CardTwo(-1);
			break;


		case 3:
			pCard = new CardThree(-1);
			break;

		case 4:
			pCard = new CardFour(-1);
			break;

		case 5:
			pCard = new CardFive(-1);
			break;

		case 6:
			pCard = new CardSix(-1);
			break;

		case 7:
			pCard = new CardSeven(-1);
			break;

		case 8:
			pCard = new CardEight(-1);
			break;

		case 9:
			pCard = new CardNine(-1);
			break;
	
		case 10:
			pCard = new CardTen(-1);
			break;

		case 11:
			pCard = new CardEleven(-1);
			break;

		case 12:
			pCard = new CardTwelve(-1);
			break;

		default:
			pCard = new Card(-1);
			break;
		}
			pCard->Load(load_file);
			pGrid->AddObjectToCell(pCard);
		
	}
}