#include "CardTen.h"

#include "Player.h"
#include "Card.h"


int CardTen::Price = -1;
int CardTen::Fees = -1;
bool CardTen::Set = false;
bool CardTen::Saved = false;
Player* CardTen::Owner = nullptr;


bool CardTen::IsSet() {
	if (Set == 0) {
		Set++;
		return false;
	}
	return true;
}

bool CardTen::IsSaved() {
	if (!Saved) {
		Saved = true;
		return false;
	}
	return true;
}

CardTen::CardTen(const CellPosition& Pos) : Card(Pos)
{
	cardNumber = 10;
}

CardTen::CardTen(const CellPosition& Pos, int price, int fee) : Card(Pos)
{
	cardNumber = 10;
	Price = price;
	Fees = fee;
}


void CardTen::ReadCardParameters(Grid* pGrid)
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


void CardTen::SetOwner(Player* owner)
{
	Owner = owner;
}

Player* CardTen::GetOwner()
{
	return Owner;
}

int CardTen::GetPrice()
{
	return Price;
}


void CardTen::Apply(Grid* pGrid, Player* pPlayer)
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


void CardTen::Save(ofstream& OutFile, ObjectType obj_t) {
	if (obj_t == CARD_TYPE) {
		if (!IsSaved())
			OutFile << cardNumber << " " << position.GetCellNum() << " " << Price << " " << Fees << endl;
		else
			Card::Save(OutFile, obj_t);
	}
}
void CardTen::Load(ifstream& InFile) {
	Card::Load(InFile);
	if (Price < 0 || Fees < 0) InFile >> Price >> Fees;
}
