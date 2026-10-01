#pragma once
#include "GameObject.h"
class Snake : public GameObject
{
	// Note: the "position" data member inherited from the GameObject class is used as the Snake's "Start Cell Position"

	CellPosition endCellPos; // here is the Snake's End Cell Position

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member

	void Save(ofstream& OutFile, ObjectType ObjType) override;	// Saves the GameObject parameters to the file
	void Load(ifstream& InFile) override;	// Loads the GameObject parameters from the file
	virtual ~Snake(); // Virtual destructor

	virtual bool  IsOverLapping(GameObject* newObj) const; // Check on overlapping


};

