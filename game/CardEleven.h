#pragma once
#include "Card.h"

class CardEleven : public Card
{

public:
	CardEleven(const CellPosition& Pos);
	CardEleven(const CellPosition& Pos, int price, int fee);

	virtual void ReadCardParameters(Grid* pGrid);
	void Apply(Grid* pGrid, Player* pPlayer);
	static void SetOwner(Player* owner);
	static Player* GetOwner();
	static int GetPrice();
	bool IsSet();
	bool IsSaved();
	void Save(ofstream& OutFile, ObjectType obj_t) override;
	void Load(ifstream& InFile) override;
	~CardEleven() = default;
private:
	static int Price;
	static int Fees;
	static Player* Owner;
	static bool Set;
	static bool Saved;
};
