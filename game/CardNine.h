#pragma once
#include "Card.h"

class CardNine : public Card
{

public:
	CardNine(const CellPosition& Pos);
	CardNine(const CellPosition& Pos, int price, int fee);

	virtual void ReadCardParameters(Grid* pGrid);
	void Apply(Grid* pGrid, Player* pPlayer);
	static void SetOwner(Player* owner);
	static Player* GetOwner();
	static int GetPrice();
	bool IsSet();
	~CardNine() = default;
	bool IsSaved();
	void Save(ofstream& OutFile, ObjectType obj_t) override;
	void Load(ifstream& InFile) override;

private:
	static int Price;
	static int Fees;
	static Player* Owner;
	static bool Set;
	static bool Saved;
};
