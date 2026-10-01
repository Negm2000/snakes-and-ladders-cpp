#include "CardEight.h"
CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (1 here)
}

CardEight::~CardEight(void)
{
}

void CardEight::ReadCardParameters(Grid* pGrid)
{

	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	int Temp_int;
	// 2- Read an Cell_Move_To using getCellClicked
	//    Don't forget to first print to a descriptive message to the user like:"New CardEight: Enter the amount to pay ..."
	pOut->PrintMessage("New CardEight: Enter the amount to pay ...");
	Temp_int = pIn->GetInteger(pOut);

	while (Temp_int<=0) {
		pOut->PrintMessage("Invalid Value! Enter a number again.");
		Temp_int = pIn->GetInteger(pOut);
	}
	Amount_To_Pay = Temp_int;

	// 3- Clear the status bar
	pOut->ClearStatusBar();

}
void CardEight::Apply(Grid* pGrid, Player* pPlayer) {

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	string Choice;
	Card::Apply(pGrid, pPlayer);
	pOut->PrintMessage("Pay " + to_string(Amount_To_Pay) + " Or stay in prison? (Y/N)");
	Choice = pIn->GetSrting(pOut);
	for (int i = 0; i < Choice.length(); i++) {
		Choice[i] = toupper(Choice[i]);
	}

	while (Choice != "Y" && Choice != "YES" && Choice != "N" && Choice != "NO") {
		pOut->PrintMessage("Wrong Entry! Pay " + to_string(Amount_To_Pay) + " ? (Y/N)");
		Choice = pIn->GetSrting(pOut);
	}

	if (Choice == "N" || Choice == "NO") {
		// Prison Action here
		pPlayer->SetJailTime(3);
		pGrid->PrintErrorMessage("Stay in prison for 3 rounds. Click to continue.");
	}
	else {
		pPlayer->SetWallet(pPlayer->GetWallet() - Amount_To_Pay);
		pGrid->PrintErrorMessage("You have chose to pay "+ to_string(Amount_To_Pay) + ". Click to continue.");
	}
}

void CardEight::Save(ofstream& OutFile, ObjectType Obj_t)
{
	if (Obj_t == CARD_TYPE)
		OutFile << cardNumber << " " << position.GetCellNum() << " " << Amount_To_Pay << endl;
}

void CardEight::Load(ifstream& Infile)
{
	int pos, amount;
	Infile >> pos >> amount;
	position = CellPosition(pos);
	Amount_To_Pay = amount;
}





