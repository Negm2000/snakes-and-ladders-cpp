#pragma once
#include "Action.h"
class CutCardAction :public Action
{
	CellPosition Cut_Pos;
	Card* Cut_Card;
public:
	CutCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads CutCardAction action parameters

	virtual void Execute(); 

	virtual ~CutCardAction(); // A Virtual Destructor
};

