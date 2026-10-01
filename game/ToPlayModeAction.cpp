#include "ToPlayModeAction.h"

#include "Grid.h"


ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp) : Action(pApp) {}

void ToPlayModeAction::ReadActionParameters() {}

void ToPlayModeAction::Execute() {
	pManager->GetGrid()->GetOutput()->CreatePlayModeToolBar();
}

ToPlayModeAction::~ToPlayModeAction() {}