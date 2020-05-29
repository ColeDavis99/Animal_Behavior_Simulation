#ifndef AREA_H
#define AREA_H

#include "creature.h"
class Area
{
    public:
        Area();  //Declare default constructor;

    private:
        short numCreatures;
        Creature* creaturePtr1;
        Creature* creaturePtr2;
};

#endif