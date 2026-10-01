#include "ToDesignModeAction.h"
#include "Grid.h"

ToDesignModeAction::ToDesignModeAction(ApplicationManager* pApp): Action(pApp){}

 void ToDesignModeAction::ReadActionParameters(){}

 void ToDesignModeAction::Execute() {
	 pManager->ExecuteAction(NEW_GAME); // Reset match
	 pManager->GetGrid()->GetOutput()->CreateDesignModeToolBar();
 }

 ToDesignModeAction::~ToDesignModeAction() = default;