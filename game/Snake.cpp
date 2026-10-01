#include "Snake.h"
Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

bool  Snake::IsOverLapping(GameObject* pNew) const
{
	
	Snake* pNewSnake = dynamic_cast<Snake*>(pNew);
	if (pNewSnake)
	{
		int New_Start = pNewSnake->position.GetCellNum();
		int New_End = pNewSnake->endCellPos.GetCellNum();
		int This_Start = this->position.GetCellNum();
		int This_End = this->endCellPos.GetCellNum();
		if ( (New_Start > This_End && New_Start < This_Start) || (This_End < This_Start && New_Start > This_Start ) )
			return true;
	}
	return false;
}



void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");
	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}





// Handling save and load
void Snake::Save(ofstream& OutFile, ObjectType obj_t)	// Saves the Snake parameters to the file
{
	if (obj_t == SNAKE_TYPE)
		OutFile << GetPosition().GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}
void Snake::Load(ifstream& InFile)// loads the Snake parameters to the file
{
	int start, end;
	InFile >> start >> end;
	position = CellPosition::GetCellPositionFromNum(start);
	endCellPos = CellPosition::GetCellPositionFromNum(end);
}


CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}

Snake::~Snake()
{
}