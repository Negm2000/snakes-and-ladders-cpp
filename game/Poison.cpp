#include "Poison.h"

Poison::Poison(Grid* pGr, Player* attacker) : PowerUp(pGr, attacker)
{
	AttackTarget = NULL;
}

void Poison::ReadAttackTarget()
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	while (AttackTarget == NULL)
	{
		pOut->PrintMessage("Enter the number of the player you want to attack (from 0 to " + to_string(MaxPlayerCount - 1) + ")");
		int targetNum = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();

		// get the player pointer with the num the user has entered
		Player* targetPlayer = pGrid->GetPlayerOf(targetNum);
		if (targetPlayer != NULL)
		{
			if (targetPlayer != Attacker)
				AttackTarget = targetPlayer;
			else
				pGrid->PrintErrorMessage("You can't attack yourself! click to continue...");
		}
		else
		{
			pGrid->PrintErrorMessage("Invalid player number! click to continue...");
		}
	}
}

Player* Poison::getAttackTarget()
{
	return AttackTarget;
}

void Poison::Execute()
{
	ReadAttackTarget();
	
	AttackTarget->setPoisoned(5); // Poisoned for 5 turns

	pGrid->UpdateInterface();
}