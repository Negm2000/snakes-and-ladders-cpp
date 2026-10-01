#pragma once
#include "Action.h"
class OpenAction : public Action
{
	string file_name;

	public:
	OpenAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~OpenAction() = default;
};

