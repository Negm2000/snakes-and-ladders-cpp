#include "SaveGridAction.h"
#include "Grid.h"
#include <algorithm>
#include <fstream>


SaveGridAction::SaveGridAction(ApplicationManager* pApp): Action(pApp) {}

void SaveGridAction::ReadActionParameters() {

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	do {
		// 2- Display “Ask user for a file name”
		pOut->PrintMessage("Enter a name for your save file, only alpha-numeric characters allowed: ");

		// 3- Read a valid string from the user
		file_name = pIn->GetSrting(pOut);
		// 4- Clear status bar
		pOut->ClearStatusBar();

	} while (!all_of(file_name.begin(), file_name.end(),isalnum));


}

void SaveGridAction::Execute() {

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	//TODO:
	// 1.Reads action parameters(i.e.the filename):
	ReadActionParameters();
	// 2.Opens the file
	ofstream save_file{"../Sample_Grids/"+file_name + ".txt", ios::trunc};

	// Check if open failed
	if (!save_file) {
		pGrid->PrintErrorMessage("Can't save, close the file and try again");
		return;
	}

	//	 and calls Grid::SaveAll(&file, LaddersType) to save all ladders
	pGrid->SaveAll(save_file, LADDER_TYPE);
	//	 and calls Grid::SaveAll(&file, SnakesType) to same all snakes
	pGrid->SaveAll(save_file, SNAKE_TYPE);
	//	 and calls Grid::SaveAll(&file, CardsType) to same all snakes
	pGrid->SaveAll(save_file, CARD_TYPE);
	//		then closes the file

}

SaveGridAction::~SaveGridAction() {}