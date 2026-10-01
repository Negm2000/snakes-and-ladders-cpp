#include "NewGameAction.h"
#include "Player.h"
#include "Grid.h"

NewGameAction::NewGameAction(ApplicationManager* pApp):Action(pApp) {};  // Constructor

void NewGameAction::ReadActionParameters(){}


//New Game: Restarts players' positions, wallets, and turn returns to player 0.
void NewGameAction::Execute() {

	Grid* pGrid = pManager->GetGrid();
	Player* pPlayer = nullptr;

	for (int i = 0; i < MaxPlayerCount; i++) {
		pGrid->SetCurrPlayerNumber(i);
		pPlayer = pGrid->GetCurrentPlayer();
		pPlayer->SetWallet(100);
		pPlayer->SetTurnCount(0);
		pPlayer->setTurnsToSkip(0);
		pPlayer->PowerUpReset();
		pGrid->UpdatePlayerCell(pPlayer, 1);
		pGrid->SetEndGame(false);
		pPlayer->SetJailTime(0);
	}

	pGrid->SetCurrPlayerNumber(0);

	
}

NewGameAction::~NewGameAction() {};  // Virtual Destructor