#include "creature.h"

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
}




//MEMBER FUNCTION DEFINITIONS
long Creature::Get_creatureID(){ return creatureID; }

string Creature::Get_creatureType(){ return strategyNames[creatureType]; }

void Creature::Set_creatureType(Strategy strat){ creatureType = strat; }