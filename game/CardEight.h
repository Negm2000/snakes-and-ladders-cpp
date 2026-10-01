#pragma once
#include "Card.h"
/**Card8:
 This card is a prison.
Programming Techniques Project Requirements
5/10
 When a player stops at a Card8 cell, the player should choose either to pay specific
amount of coins to go out of the prison, or stay in prison and not playing for 3 turns.
 Input data in design mode:
i. The amount of coins needed to go out of the prison
*/
class CardEight :public Card
{
	int Amount_To_Pay;

public:
	CardEight(const CellPosition& pos);

	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardEight which is: Amount to pay

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardEight on the passed Player
													  
	void Save(ofstream& OutFile, ObjectType Obj_t) override;
	void Load(ifstream& InFile) override;
	virtual ~CardEight(); // A Virtual Destructor
};

