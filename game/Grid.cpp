#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "Player.h"


Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


Player* Grid::GetNextPlayer() {

	CellPosition Current_Player_Position = PlayerList[currPlayerNumber]->GetCell()->GetCellPosition();
	int Minimum_Next_Player_Position_Num = 99;
	Player* Next_Player=NULL;

	for (int i = 0; i < 4; i++) {
		if (currPlayerNumber == i) {
			continue;
		}
		if (PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() > Current_Player_Position.GetCellNum() && PlayerList[i]->GetCell()->GetCellPosition().GetCellNum() < Minimum_Next_Player_Position_Num) {
			Next_Player = PlayerList[i];
		}
	}



	return Next_Player;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject* pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();

	Ladder* New_Ladder = dynamic_cast<Ladder*>(pNewObject);
	Snake* New_Snake = dynamic_cast<Snake*>(pNewObject);

	if (pos.IsValidCell()) // Check if valid position
	{
		// Get column of pos
		int col = pos.HCell();
		//Check for overlapping
		for (int row = 0; row < NumVerticalCells; row++) {
			if (New_Ladder) {
				if (CellList[row][col]->HasLadder()) {
					if (CellList[row][col]->HasLadder()->IsOverLapping(New_Ladder))
						return false;
				}
			}

			if (New_Snake) {
				if (CellList[row][col]->HasSnake()) {
					if (CellList[row][col]->HasSnake()->IsOverLapping(New_Snake))
						return false;
				}
			}
		}

		// Get the previous GameObject of the Cell
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		//

		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

bool Grid::IsThereAnObject(const CellPosition& pos) const {

	GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
	if (pPrevObject)  // the cell already contains a game object
		return false; // do NOT add and return false
	else
		return true;
}

GameObject* Grid::GetGameObject(const CellPosition& pos) const
{
	GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
	return pPrevObject;
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input* Grid::GetInput() const
{
	return pIn;
}

Output* Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card* pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card* Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
	if (endGame)
		PrintErrorMessage("Game Over! Player " + to_string(GetCurrentPlayer()->GetPlayerNumber()) + " Won!");
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::SetCurrPlayerNumber(int num)
{
	currPlayerNumber = num;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
	GetCurrentPlayer()->burnCheck(this);					    // Checks if the player is burning "deduct 20 coins"
	GetCurrentPlayer()->skipCheck(this);					    // Checks if the new current player should skip the turn 

	if (GetCurrentPlayer()->GetJailTime() > 0)
	{
		Player* CurrentPlayer = GetCurrentPlayer();
		CurrentPlayer->SetJailTime(CurrentPlayer->GetJailTime() - 1);
		PrintErrorMessage("You are in jail you will be released from jail in " + to_string(CurrentPlayer->GetJailTime()) + " turns. Click to continue.");
		AdvanceCurrentPlayer();
		return;
	}

	else if (GetCurrentPlayer()->GetTurnCount() == 2)				// On their wallet turn the player can choose to launch a special attack 
		GetCurrentPlayer()->AttackChoice(this);

}

// ========= Other Getters =========


Player* Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Player* Grid::GetPlayerOf(int num)const
{
	if (num < MaxPlayerCount)
		return PlayerList[num];
	else
		return NULL;
}

Ladder* Grid::GetNextLadder(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			if (CellList[i][j]->HasLadder()) 
				return dynamic_cast<Ladder*> (CellList[i][j]->GetGameObject());


		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}




// ========= User Interface Functions =========


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


void Grid::SaveAll(ofstream& file, ObjectType obj_t) {
	
	file << GetObjCount(obj_t) << endl; // Writes the number of objects of the given type
	// Calls each object's save function

	for (int row = 0; row < NumVerticalCells; row++)
		for (int col = 0; col < NumHorizontalCells; col++) {
			GameObject* obj = CellList[row][col]->GetGameObject();
			if (obj != nullptr) obj->Save(file, obj_t);
		}
}

int Grid::GetObjCount(ObjectType obj_t) const {
	int sum = 0;
	for (int row = 0; row < NumVerticalCells; row++) {
		for (int col = 0; col < NumHorizontalCells; col++) {
			switch (obj_t) {
			case LADDER_TYPE:
				if (CellList[row][col]->HasLadder()) sum++;
				break;
			case SNAKE_TYPE:
				if (CellList[row][col]->HasSnake()) sum++;
				break;
			case CARD_TYPE:
				if (CellList[row][col]->HasCard()) sum++;
				break;
			default:
				break;
			}
		}
	}
	return sum;
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}