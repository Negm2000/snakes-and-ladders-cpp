#pragma once
#include "Action.h"
#include "Card.h"

class PasteCardAction : public Action
{
	CellPosition pos2;
public:
	PasteCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();


	virtual ~PasteCardAction(); // A Virtual Destructor
};

