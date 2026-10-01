#include "CardNine.h"
#include "Player.h"
#include "Card.h"


int CardNine::Price = -1;
int CardNine::Fees = -1;
bool CardNine::Set = false;
bool CardNine::Saved = false;
Player* CardNine::Owner = nullptr;


bool CardNine::IsSet(){
	if (Set == 0) {
		Set = true;
		return false;
	}
	return true;
}

bool CardNine::IsSaved(){
	if (Saved == 0) {
		Saved = true;
		return false;
	}
	return true;
}


CardNine::CardNine(const CellPosition& Pos) : Card(Pos)
{
	cardNumber = 9;
}

CardNine::CardNine(const CellPosition& Pos, int price, int fee) : Card(Pos)
{
	cardNumber = 9;
	Price = price;
	Fees = fee;
}


void CardNine::ReadCardParameters(Grid* pGrid)
{
	if (!IsSet()) {
		Input* pIn = pGrid->GetInput();
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("Enter Card Price: ");
		Price = pIn->GetInteger(pOut);
		pOut->PrintMessage("Enter Card Fees: ");
		Fees = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
	}
}


void CardNine::SetOwner(Player* owner)
{
	Owner = owner;
}

Player* CardNine::GetOwner()
{
	return Owner;
}

int CardNine::GetPrice()
{
	return Price;
}


void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (Owner == NULL)
	{
		pOut->PrintMessage("Do you want to buy this card for "+ to_string(Price)+ " (Y/N)?");
		string s = pIn->GetSrting(pOut);
		for (unsigned int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);

		if (s == "YES" || s == "Y")
		{
			pGrid->PrintErrorMessage("Card " + to_string(cardNumber) + " bought by player " + to_string(pPlayer->GetPlayerNumber())
			+". Click to continue.");
			if (pPlayer->GetWallet() >= Price)
			{
				pPlayer->SetWallet(pPlayer->GetWallet() - Price);
				Owner = pPlayer;
				return;
			}
			else
			{
				pOut->PrintMessage("You don't have enough coins");
				return;
			}
		}
	}
	else if (pPlayer != Owner)
	{
		pGrid->PrintErrorMessage("Card owned by player " + to_string(Owner->GetPlayerNumber()) + ", you will pay " + to_string(Fees) + ". Click to continue.");
		pPlayer->SetWallet(pPlayer->GetWallet() - Fees);
		Owner->SetWallet(Owner->GetWallet() + Fees);
	}
}


void CardNine::Save(ofstream& OutFile, ObjectType obj_t) {
	if (obj_t == CARD_TYPE) {
		if (!IsSaved())
			OutFile << cardNumber << " " << position.GetCellNum() << " " << Price << " " << Fees << endl;
		else
			Card::Save(OutFile, obj_t);
	}
}
void CardNine::Load(ifstream& InFile) {
	Card::Load(InFile);
	if (Price < 0 || Fees < 0) InFile >> Price >> Fees;
}
