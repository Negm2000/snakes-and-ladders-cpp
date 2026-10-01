#include "Player.h"
#include "Input.h"
#include "GameObject.h"

#include "PowerUp.h"
#include "Ice.h"
#include "Fire.h"
#include "Poison.h"
#include "Lightening.h"


Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	turnsToSkip = 0;
	AttackCounter = 2;
	Am_I_Burning = 0;
	Am_I_Poisoned = 0;
	for (int i = 0; i < 4; i++)
	{
		SpecialAttacks[i] = 1;
	}
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetJailTime(int j)
{
	JailTime = j;
}
int Player::GetJailTime()
{
	return JailTime;
}

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}


Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	this->wallet = wallet > 0 ? wallet: 0 ;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
void Player::SetTurnCount(int num)
{
	turnCount = num;
}

void Player::turnIncrement()
{
	turnCount++;
	if (turnCount == 3)
		turnCount = 0;
}
int Player::GetJustRolledDiceNum() const
{
	return justRolledDiceNum;
}


// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);


	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);


}

// ====== Game Functions ======


void Player::Move(Grid* pGrid, int diceNumber)
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==


	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	turnCount++;

	// 2- Set the justRolledDiceNum with the passed diceNumber
	justRolledDiceNum = diceNumber;
	// 3- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3) {
		pGrid->PrintErrorMessage("Recharging wallet...Click to continue");
		turnCount = 0;
		wallet += 10 * justRolledDiceNum;
		return;
	}



	if (wallet > 0) //Validation if the player still has some coins in his wallet
	{
		CellPosition Pos = pCell->GetCellPosition();
		int CellNum;
		CellNum = Pos.GetCellNum();

		if ((CellNum + justRolledDiceNum) < 99)
		{
			Pos.AddCellNum(justRolledDiceNum);
			pGrid->UpdatePlayerCell(this, Pos);

			// 6- Apply() the game object of the reached cell (if any)

			if (pGrid->GetGameObject(Pos) != nullptr)
			{
				pGrid->GetGameObject(Pos)->Apply(pGrid, this);
			}

		}

		// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true
		else
		{
			Pos = CellPosition(99);
			pGrid->UpdatePlayerCell(this, Pos);
			pGrid->SetEndGame(true);

		}
	}
	else
	{
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": Must Have atleast One Coin to Move");
		return;
	}
}

int Player::GetPlayerNumber() const
{
	return playerNum;
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::setTurnsToSkip(int turns)
{
	if (turns > 0)
	{
		turnsToSkip = turns;
	}
}

void Player::skipCheck(Grid* pGrid)
{
	//This function checks if the player should skip this turn, and if that's the case, 
	//calls AdvanceCurrentPlayer() to give the turn to the next player

	if (turnsToSkip > 0)
	{
		turnsToSkip--;
		turnIncrement();
		pGrid->PrintErrorMessage("Player " + to_string(GetPlayerNumber()) + " skips the turn this round! click to continue...");
		pGrid->AdvanceCurrentPlayer();
	}
}

Player* Player::GetPlayerWithLeastMoney(Grid* pGrid)
{
	int min, index;
	min = pGrid->GetPlayerOf(0)->GetWallet();
	index = 0;
	for (int i = 1; i < MaxPlayerCount; i++)
	{
		if (min > pGrid->GetPlayerOf(i)->GetWallet())
		{
			min = pGrid->GetPlayerOf(i)->GetWallet();
			index = i;

		}
	}
	return pGrid->GetPlayerOf(index);
}

// ====== Power Up Functions ======

void Player::setBurning(int turns)
{
	if (turns > 0)
	{
		Am_I_Burning = turns;
	}
}

void Player::setPoisoned(int turns)
{
	if (turns > 0)
	{
		Am_I_Poisoned = turns;
	}
}

void Player::burnCheck(Grid* pGrid)
{
	if (Am_I_Burning > 0)
	{
		Am_I_Burning--;
		Output* pOut = pGrid->GetOutput();
		pOut->ClearStatusBar();
		pGrid->UpdateInterface();
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": You are burning, you lose 20 coins!");
		this->SetWallet(GetWallet() - 20);
		pGrid->UpdateInterface();
	}
}

bool Player::poisonCheck(Grid* pGrid)
{
	if (Am_I_Poisoned > 0)
	{
		Am_I_Poisoned--;
		Output* pOut = pGrid->GetOutput();
		pOut->ClearStatusBar();
		pGrid->UpdateInterface();
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": You are poisoned, you lose 1 from your dice roll!");
		return true;
	}
	return false;
}

void Player::AttackChoice(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pGrid->UpdateInterface();

	if (AttackCounter == 0)
	{
		pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": You already used your 2 special attacks for this game, click to continue...");
		return;
	}

	pOut->PrintMessage("Player " + to_string(playerNum) + ": Do you wish to launch a special attack instead of recharging? y/n");
	string choice = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	while (choice != "y" && choice != "Y" && choice != "N" && choice != "n")
	{
		pOut->PrintMessage("Player " + to_string(playerNum) + ": You entered an invalid Charcter: Do you wish to launch a special attack instead of recharging? y/n");
		choice = pIn->GetSrting(pOut);
		pOut->ClearStatusBar();
	}
	if (choice == "y" || choice == "Y")
	{
		pOut->PrintMessage("Player " + to_string(playerNum) + ": Choose the type of attack ('I'ce - 'F'ire - 'P'oison - 'L'ighting)");
		string type = pIn->GetSrting(pOut);
		pOut->ClearStatusBar();

		bool used = false;
		if (type == "i" || type == "I")
		{
			if (UseAttack(ice, pGrid))
				used = true;
		}
		else if (type == "f" || type == "F")
		{
			if (UseAttack(fire, pGrid))
				used = true;
		}
		else if (type == "p" || type == "P")
		{
			if (UseAttack(poison, pGrid))
				used = true;
		}
		else if (type == "l" || type == "L")
		{
			if (UseAttack(lightening, pGrid))
				used = true;
		}
		else
		{
			pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": Invalid input, click to continue...");
			AttackChoice(pGrid);

		}
		if (used)
			pGrid->AdvanceCurrentPlayer();
		if (used == false)
		{
			pGrid->PrintErrorMessage("Player " + to_string(playerNum) + ": You can use each special attack once per game, click to continue...");
			AttackChoice(pGrid);
		}
	}
}

bool Player::UseAttack(AttackType atk, Grid* pGrid)
{
	PowerUp* attack = NULL;
	if (atk == ice)
	{
		if (SpecialAttacks[ice] > 0)
		{
			SpecialAttacks[ice]--;
			attack = new Ice(pGrid, this);
		}
	}
	else if (atk == fire)
	{
		if (SpecialAttacks[fire] > 0)
		{
			SpecialAttacks[fire]--;
			attack = new Fire(pGrid, this);
		}
	}
	else if (atk == poison)
	{
		if (SpecialAttacks[poison] > 0)
		{
			SpecialAttacks[poison]--;
			attack = new Poison(pGrid, this);
		}
	}
	else if (atk == lightening)
	{
		if (SpecialAttacks[lightening] > 0)
		{
			SpecialAttacks[lightening]--;
			attack = new Lightening(pGrid, this);
			pGrid->PrintErrorMessage("All players except player " + to_string(playerNum) + " lose 20 coins!");
		}
	}
	if (attack != NULL)	
	{
		AttackCounter--;
		turnCount = 0;			
		attack->Execute();

		delete attack;
		attack = NULL;
		return true;
	}
	return false;
}
void Player::PowerUpReset()
{
	turnsToSkip = 0;
	AttackCounter = 2;
	Am_I_Burning = 0;
	Am_I_Poisoned = 0;
	for (int i = 0; i < 4; i++)
	{
		SpecialAttacks[i] = 1;
	}
}

int Player::GetRolledDice() const {
	return justRolledDiceNum;
}