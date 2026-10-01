#include "Lightening.h"

Lightening::Lightening(Grid* pGr, Player* attacker) : PowerUp(pGr, attacker)
{
}

void Lightening::Execute() // All players lose 20 coins
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		if (i != Attacker->GetPlayerNumber())
		{
			Player* target = pGrid->GetPlayerOf(i);
			target->SetWallet(target->GetWallet() - 20);
		}
	}
	pGrid->UpdateInterface();


}