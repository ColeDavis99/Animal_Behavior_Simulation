#ifndef AREA_H
#define AREA_H

#include "creature.h"
class Area
{
    public:
        //CONSTRUCTORS
        Area();                 //Declare default constructor;

        //MEMBER FUNCTIONS
        bool AddCreature(Creature *creatureAddr);   //Add a creature to a space. Returns 1 if succesful, 0 if space is full.
        void showCreatureIDs();                     //Cout the id's of each creature on this space (or say it's empty)

    private :
        //MEMBER VARIABLES
        short numCreatures;
        Creature* creaturePtr1;
        Creature* creaturePtr2;
};

#endif