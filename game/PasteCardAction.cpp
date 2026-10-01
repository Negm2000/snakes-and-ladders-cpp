#include "PasteCardAction.h"
#include "Grid.h"
#include "Card.h"
#include "AddCardAction.h"
#include "Action.h"
#include "ApplicationManager.h"
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



PasteCardAction::PasteCardAction(ApplicationManager* pApp) :Action(pApp)
{

}

void PasteCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	CellPosition Temp_Cell;
	pOut->PrintMessage("Click to paste the card on a certain cell");
	Temp_Cell = pIn->GetCellClicked();

	if (Temp_Cell.IsValidCell() == false) {
		pGrid->PrintErrorMessage("Invalid Cell, Click to continue.");
		return;
	}
	pos2 = Temp_Cell;
	pOut->ClearStatusBar();
}

void PasteCardAction::Execute()
{
	if (pManager->GetGrid()->GetClipboard() == NULL)
	{
		pManager->GetGrid()->PrintErrorMessage("No card is copied, Click to contiune.");
		return;
	}
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Card* Pasted_Card = pGrid->GetClipboard();
	Card* pCard = NULL;

	switch (Pasted_Card->GetCardNumber()){

	case 1:
		pCard = new CardOne(*dynamic_cast<CardOne*>(Pasted_Card));
		break;
	case 2:
		pCard = new CardTwo(*dynamic_cast<CardTwo*>(Pasted_Card));
		break;

	case 3:
		pCard = new CardThree(*dynamic_cast<CardThree*>(Pasted_Card));
		break;

	case 4:
		pCard = new CardFour(*dynamic_cast<CardFour*>(Pasted_Card));
		break;

	case 5:
		pCard = new CardFive(*dynamic_cast<CardFive*>(Pasted_Card));
		break;

	case 6:
		pCard = new CardSix(*dynamic_cast<CardSix*>(Pasted_Card));
		break;

	case 7:
		pCard = new CardSeven(*dynamic_cast<CardSeven*>(Pasted_Card));
		break;

	case 8:
		pCard = new CardEight(*dynamic_cast<CardEight*>(Pasted_Card));
		break;

	case 9:
		pCard = new CardNine(*dynamic_cast<CardNine*>(Pasted_Card));
		break;


	case 10:
		pCard = new CardTen(*dynamic_cast<CardTen*>(Pasted_Card));
		break;

	case 11:
		pCard = new CardEleven(*dynamic_cast<CardEleven*>(Pasted_Card));
		break;

	case 12:
		pCard = new CardTwelve(*dynamic_cast<CardTwelve*>(Pasted_Card));
		break;

	default:
		break;
	}

	
	pCard->SetPosition(pos2);

	bool Check_Object = pGrid->AddObjectToCell(pCard);
	// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
	if (Check_Object == false) {
		pGrid->PrintErrorMessage("Cell already has another object ! Click to continue.");
	}
	else {
		(pGrid->GetOutput())->PrintMessage("Card Added Successfully !");
	}
}

PasteCardAction::~PasteCardAction()
{
}