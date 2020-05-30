#ifndef AREA_H
#define AREA_H

#include "creature.h"
using std::vector;


class Area
{
    public:
        //CONSTRUCTORS
        Area();                 //Declare default constructor;
        

        //MEMBER FUNCTIONS
        bool AddCreature(Creature *creatureAddr);   //Add a creature to a space. Returns 1 if succesful, 0 if space is full.
        void ShowCreatureIDs();                     //Cout the id's of each creature on this space (or say it's empty)
        void ShowCreatureTypes();                   //Cout the type of each creature on this space (or say it's empty)

        //Evaluate the two types of creatures this space, and update values accordingly.
        void CreatureAction(std::vector<Creature> &aliveCreatures, std::vector<Creature> &deadCreatures, const long NUM_CREATURES_MAX, const float DOVE_WITH_HAWK_SURVIVAL_PROB, const float HAWK_WITH_HAWK_SURVIVAL_PROB, const float HAWK_WITH_DOVE_REPRO_PROB);
        long ReturnCreatureIndex(std::vector<Creature> &creatureVec, long creatureID); //Returns a creature's position within some vector

        //Getters
        short Get_numCreatures();

    private :
        //MEMBER VARIABLES
        short numCreatures;
        Creature* creaturePtr1;
        Creature* creaturePtr2;
};

#endif