#pragma once
#include "Action.h"

class InputDiceAction : public Action
{

// Input dice number
	int diceNumber; 

public:
	InputDiceAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceAction();
};

