#pragma once
#include "Card.h"

/**[CardSix] Summary:
 Instructs the player to go to a specific cell.
 If the destination cell contains a ladder, snake, or card, take it.
 Input data in design mode :
i.Cell to move to
*/
class CardSix :public Card
{
	CellPosition Cell_Move_To;
public:
	CardSix(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardSix which is: Cell to move to

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardSix on the passed Player								
	void Save(ofstream& OutFile, ObjectType Obj_t) override;
	void Load(ifstream& InFile) override;
	virtual ~CardSix()=default; // A Virtual Destructor
};


