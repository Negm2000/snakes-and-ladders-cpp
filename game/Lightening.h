#pragma once
#include "PowerUp.h"

class Lightening :
    public PowerUp
{
public:
    Lightening(Grid* pGr, Player* attacker);

    virtual void Execute();
};

