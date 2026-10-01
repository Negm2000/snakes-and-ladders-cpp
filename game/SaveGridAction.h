#pragma once
#include "Action.h"
class SaveGridAction :public Action
{
	string file_name;

	public:
		SaveGridAction(ApplicationManager* pApp);

		virtual void ReadActionParameters();

		virtual void Execute();

		virtual ~SaveGridAction();
};

