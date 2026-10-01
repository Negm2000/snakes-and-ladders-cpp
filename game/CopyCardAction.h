#pragma once
#include "Action.h"
class CopyCardAction : public Action
{
	CellPosition CardPosition;
	Card* Copied_Card;
public:
	CopyCardAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~CopyCardAction();
};

