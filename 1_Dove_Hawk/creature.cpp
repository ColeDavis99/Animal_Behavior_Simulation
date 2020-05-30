#include<iostream>
#include "creature.h"
using std::cout;
using std::endl;

//STATIC VARIABLES
long Creature::id = 0;                                   //Static variable counter
string Creature::strategyNames[2] = {"hawk", "dove"};    //Definition of our enum string "mapping"

//Define default constructor
Creature::Creature()
{
    id++; 
    creatureID = id;
}

//Creature type constructor declaration
Creature::Creature(Strategy strat)
{
    creatureType = strat;
    id++;
    creatureID = id;
    cout<<strategyNames[strat]<<" BORN WITH ID: "<<creatureID<<endl;
}


//Creature copy constructor
Creature::Creature(const Creature &creat)
{
    creatureType = creat.creatureType;
    creatureID = creat.creatureID;
}

//MEMBER FUNCTION DEFINITIONS
long Creature::Get_creatureID(){ return creatureID; }

string Creature::Get_creatureType(){ return strategyNames[creatureType];}

void Creature::Set_creatureType(Strategy strat){ creatureType = strat; }