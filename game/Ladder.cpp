#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
}

bool Ladder::IsOverLapping(GameObject* pNew) const
{
	// Should i add another dynamic cast to snake? as ,if a snake and a ladder overlapped together?
	Ladder* pNewLadder = dynamic_cast<Ladder*>(pNew);
	if (pNewLadder)
	{
		int New_Start = pNewLadder->position.GetCellNum();
		int New_End = pNewLadder->endCellPos.GetCellNum();
		int This_Start = this->position.GetCellNum();
		int This_End = this->endCellPos.GetCellNum();

		if ( (New_Start < This_Start && New_End > This_Start && New_End) || (New_Start < This_End && New_End > This_End) )
			return true;
	}
	return false;
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}



void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");
	
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	// Check if game has ended
	if (endCellPos.GetCellNum() == 99)
		pGrid->SetEndGame(true);
	
}

void Ladder::Save(ofstream& OutFile, ObjectType ObjType) {
	if (ObjType == LADDER_TYPE)
		OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

void Ladder::Load(ifstream& InFile) {
	int start, end;
	InFile >> start >> end;
	position = CellPosition::GetCellPositionFromNum(start);
	endCellPos = CellPosition::GetCellPositionFromNum(end);
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

Ladder::~Ladder()
{
}
