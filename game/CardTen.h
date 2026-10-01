#pragma once
#include "Card.h"

class CardTen : public Card
{

public:
	CardTen(const CellPosition& Pos);
	CardTen(const CellPosition& Pos, int price, int fee);

	virtual void ReadCardParameters(Grid* pGrid);
	void Apply(Grid* pGrid, Player* pPlayer);
	static void SetOwner(Player* owner);
	static Player* GetOwner();
	static int GetPrice();
	bool IsSet();
	bool IsSaved();
	~CardTen() = default;
	void Save(ofstream& OutFile, ObjectType obj_t) override;
	void Load(ifstream& InFile) override;

private:
	static int Price;
	static int Fees;
	static Player* Owner;
	static bool Set;
	static bool Saved;
};
