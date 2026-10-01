#include "CardEleven.h"
#include "Player.h"
#include "Card.h"


int CardEleven::Price = -1;
int CardEleven::Fees = -1;
bool CardEleven::Set = false;
bool CardEleven::Saved = false;
Player* CardEleven::Owner = nullptr;


bool CardEleven::IsSet() {
	if (Set == 0) {
		Set=true;
		return false;
	}
	return true;
}


bool CardEleven::IsSaved() {
	if (!Saved) {
		Saved = true;
		return false;
	}
	return true;
}



CardEleven::CardEleven(const CellPosition& Pos) : Card(Pos)
{
	cardNumber = 11;
}

CardEleven::CardEleven(const CellPosition& Pos, int price, int fee) : Card(Pos)
{
	cardNumber = 11;
	Price = price;
	Fees = fee;
}


void CardEleven::ReadCardParameters(Grid* pGrid)
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


void CardEleven::SetOwner(Player* owner)
{
	Owner = owner;
}

Player* CardEleven::GetOwner()
{
	return Owner;
}

int CardEleven::GetPrice()
{
	return Price;
}


void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (Owner == NULL)
	{
		pOut->PrintMessage("Do you want to buy this card for " + to_string(Price) + " (Y/N)?");
		string s = pIn->GetSrting(pOut);
		for (unsigned int i = 0; i < s.length(); i++) s[i] = toupper(s[i]);

		if (s == "YES" || s == "Y")
		{
			pGrid->PrintErrorMessage("Card " + to_string(cardNumber) + " bought by player " + to_string(pPlayer->GetPlayerNumber())
				+ ". Click to continue.");
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


void CardEleven::Save(ofstream& OutFile, ObjectType obj_t) {
	if (obj_t == CARD_TYPE) {
		if (!IsSaved())
			OutFile << cardNumber << " " << position.GetCellNum() << " " << Price << " " << Fees << endl;
		else
			Card::Save(OutFile, obj_t);
	}
}
void CardEleven::Load(ifstream& InFile) {
	Card::Load(InFile);
	if (Price < 0 || Fees < 0) InFile >> Price >> Fees;
}
