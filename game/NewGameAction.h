#pragma once
#include "Action.h"
class NewGameAction : public Action
{

// No parameters for this action

public:

	NewGameAction(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters(); // Reads parameters required for action to execute 

	virtual void Execute();  // Executes action (code depends on action type so virtual)

	virtual ~NewGameAction();  // Virtual Destructor
};

