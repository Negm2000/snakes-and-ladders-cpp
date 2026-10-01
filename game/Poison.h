#pragma once
#include "PowerUp.h"

class Poison :
    public PowerUp
{
    Player* AttackTarget;
public:
    Poison(Grid* pGr, Player* attacker);

    void ReadAttackTarget();

    Player* getAttackTarget();

    virtual void Execute();
};

