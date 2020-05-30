#include <iostream>
#include <vector>
#include <cstdlib>
#include "area.h"
#include "creature.h"
#include "stdlib.h"

using std::cerr;
using std::cout;
using std::endl;

//Define default constructor
Area::Area()
{
    numCreatures = 0;
    beenProcessed = false;
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
        cerr<<"This space is full. This should have been accounted for already with openPlayFieldIdx logic that holds 2 copies of each index: "<<Get_numCreatures()<<endl;
        return 0;
    }
}



//Cout the id's of each creature on this space (or say it's empty)
void Area::ShowCreatureIDs()
{
    if(creaturePtr1 == nullptr)
        cout<<"This space is empty"<<endl;
    else
    {
        if(creaturePtr1 != nullptr)
        {
            cout<<"ptr1: "<<creaturePtr1->Get_creatureType()<<" "<< creaturePtr1->Get_creatureID()<<endl; 
        }

        if(creaturePtr2 != nullptr)
        {
            cout << "ptr2: " << creaturePtr2->Get_creatureType() << " " << creaturePtr2->Get_creatureID() << endl;
        }
    }
}



//Cout the type of each creature on this space (or say it's empty)
void Area::ShowCreatureTypes()
{
    if (creaturePtr1 == nullptr)
        cout << "This space is empty" << endl;
    else
    {
        if (creaturePtr1 != nullptr)
            cout << "Creature 1: " << creaturePtr1->Get_creatureType() << endl;

        if (creaturePtr2 != nullptr)
            cout << "Creature 2: " << creaturePtr2->Get_creatureType() << endl;
    }
}

//Shows the memory addresses of each creature on this space.
void Area::ShowCreatureMemoryAddrs()
{
    cout<<"Creature1: "<<creaturePtr1<<endl;
    cout<<"Creature2: "<<creaturePtr2<<endl;
}

//Evaluate the creatures on this space, and update values accordingly.
//We know there will always be at least one creature, due to the duplicate openPlayFieldIdx values and how we're looping in main.
void Area::CreatureAction(std::vector<Creature> &aliveCreatures, std::vector<Creature> &deadCreatures, const long NUM_CREATURES_MAX, const float DOVE_WITH_HAWK_SURVIVAL_PROB, const float HAWK_WITH_HAWK_SURVIVAL_PROB, const float HAWK_WITH_DOVE_REPRO_PROB)
{

    long aliveCreatureIndex = 0; //Used for finding a killed creature's index in aliveCreatures
    float randomProb = 0.0;

    //Single Dove
    if(creaturePtr1->Get_creatureType() == "dove" && creaturePtr2 == nullptr)
    {
        aliveCreatures.push_back(Creature(Creature::Strategy::dove));
    }

    //Single Hawk
    else if(creaturePtr1->Get_creatureType() == "hawk" && creaturePtr2 == nullptr)
    {
        aliveCreatures.push_back(Creature(Creature::Strategy::hawk));
    }

    //Two Doves
    else if(creaturePtr1->Get_creatureType() == "dove" && creaturePtr2->Get_creatureType() == "dove")
    {
        ;// Do nothing, the two doves survive until the next turn.
    }

    //Two Hawks
    else if(creaturePtr1->Get_creatureType() == "hawk" && creaturePtr2->Get_creatureType() == "hawk")
    {
        cout<<endl<<endl<<"TWO HAWKS-----------------------------"<<endl;
        //See if hawk 1 dies with the prob
        randomProb = static_cast<float> (rand()) / static_cast<float> (RAND_MAX);
        if(randomProb >= HAWK_WITH_HAWK_SURVIVAL_PROB)
        {
            //Update alive and dead vectors with hawk1
            cout<<"Hawk "<<creaturePtr1->Get_creatureID()<<" killed."<<endl;
            aliveCreatureIndex = ReturnCreatureIndex(aliveCreatures, creaturePtr1->Get_creatureID());
            deadCreatures.push_back(aliveCreatures[aliveCreatureIndex]);
            aliveCreatures.erase(aliveCreatures.begin() + aliveCreatureIndex);
        }

        //See if hawk 2 dies with the prob
        randomProb = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (randomProb >= HAWK_WITH_HAWK_SURVIVAL_PROB)
        {
            //Update alive and dead vectors with hawk1
            cout << "Hawk " << creaturePtr2->Get_creatureID() << " killed." << endl;
            aliveCreatureIndex = ReturnCreatureIndex(aliveCreatures, creaturePtr2->Get_creatureID());
            deadCreatures.push_back(aliveCreatures[aliveCreatureIndex]);
            aliveCreatures.erase(aliveCreatures.begin() + aliveCreatureIndex);
        }
    }

    //One Hawk and One Dove (swip swap || statement)
    else if( (creaturePtr1->Get_creatureType() == "hawk" && creaturePtr2->Get_creatureType() == "dove") || (creaturePtr1->Get_creatureType() == "dove" && creaturePtr2->Get_creatureType() == "hawk") )
    {
        //See if dove dies with the prob
        randomProb = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (randomProb >= DOVE_WITH_HAWK_SURVIVAL_PROB)
        {
            //Figure out if the dead dove was creaturePtr1 or 2
            if(creaturePtr1->Get_creatureType() == "dove")
            {
                //Update alive and dead vectors with dead dove
                cout<<"Dove "<<creaturePtr1->Get_creatureID()<<" killed."<<endl;
                aliveCreatureIndex = ReturnCreatureIndex(aliveCreatures, creaturePtr1->Get_creatureID());
                deadCreatures.push_back(aliveCreatures[aliveCreatureIndex]);
                aliveCreatures.erase(aliveCreatures.begin() + aliveCreatureIndex);
            }
            else
            {
                //Update alive and dead vectors with dead dove
                cout << "Dove " << creaturePtr2->Get_creatureID() << " killed." << endl;
                aliveCreatureIndex = ReturnCreatureIndex(aliveCreatures, creaturePtr2->Get_creatureID());
                deadCreatures.push_back(aliveCreatures[aliveCreatureIndex]);
                aliveCreatures.erase(aliveCreatures.begin() + aliveCreatureIndex);
            }
        }

        //See if hawk reproduces with the prob
        randomProb = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (randomProb >= HAWK_WITH_HAWK_SURVIVAL_PROB)
        {
            aliveCreatures.push_back(Creature(Creature::Strategy::hawk));
        }
    }
}

//Returns a creature's position within some vector
long Area::ReturnCreatureIndex(std::vector<Creature> &creatureVec, long creatureID)
{
    cout<<"This is the creatureID: "<<creatureID<<endl;

    long ctr = 0;
    long numElements = creatureVec.size();

    while(ctr < numElements)
    {
        if(creatureVec[ctr].Get_creatureID() == creatureID)
            return ctr;
        ctr++;
    }

    cout<<"CreatureID "<<creatureID<<" not found in this vector!------------------------------------------"<<endl;
    return -1;
}


void Area::Clear()
{
    numCreatures = 0;
    creaturePtr1 = nullptr;
    creaturePtr2 = nullptr;
}



//Getters
short Area::Get_numCreatures(){return numCreatures;}
bool Area::Get_beenProcessed(){return beenProcessed;}

//Setters
void Area::Set_beenProcessed(bool visited) {beenProcessed = visited;}