#pragma once
#include "Action.h"
class DeleteObjectAction : public Action
{
	CellPosition CellToRemove;
public:
	DeleteObjectAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~DeleteObjectAction() = default;
};
