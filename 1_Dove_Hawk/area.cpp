#include <iostream>
#include "area.h"
#include "creature.h"

using std::cerr;
using std::cout;
using std::endl;

//Define default constructor
Area::Area()
{
    numCreatures = 0;
    creaturePtr1 = nullptr;
    creaturePtr2 = nullptr;
}


//MEMBER FUNCTIONS
//Add a creature to a space. Returns 1 if succesful, 0 if space is full.
bool Area::AddCreature(Creature *creatureAddr)
{
    if(creaturePtr1 == nullptr)
    {
        creaturePtr1 = creatureAddr;
        numCreatures++;
        return 1;
    }
    
    if(creaturePtr2 == nullptr)
    {
        creaturePtr2 = creatureAddr;
        numCreatures++;
        return 1;
    }

    //Already two creature on this space
    else
    {
        cerr<<"This space is full. This should have been accounted for already with openPlayFieldIdx logic that holds 2 copies of each index."<<endl;
        return 0;
    }
}

//Cout the id's of each creature on this space (or say it's empty)
void Area::showCreatureIDs()
{
    if(creaturePtr1 == nullptr)
        cout<<"This space is empty"<<endl;
    else
    {
        if(creaturePtr1 != nullptr)
            cout<<"Creature 1: "<<creaturePtr1->Get_creatureID()<<endl; 

        if(creaturePtr2 != nullptr)
            cout << "Creature 2: " << creaturePtr2->Get_creatureID() << endl;
    }
}
