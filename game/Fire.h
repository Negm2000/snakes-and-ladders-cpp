#pragma once
#include "PowerUp.h"

class Fire :
    public PowerUp
{
    Player* AttackTarget;
public:
    Fire(Grid* pGr, Player* attacker);

    void SetAttackTarget();            // Read the attack target from the user

    Player* getAttackTarget();

    virtual void Execute();
};

