#pragma once
#include "PowerUp.h"

class Ice :
    public PowerUp
{
    Player* AttackTarget;
public:
    Ice(Grid* pGr, Player* attacker);

    void SetAttackTarget();

    Player* getAttackTarget();

    virtual void Execute();
};

