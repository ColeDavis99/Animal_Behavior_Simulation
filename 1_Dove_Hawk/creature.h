#ifndef CREATURE_H
#define CREATURE_H

#include <string>
using std::string;

class Creature
{
    public:
        //ENUM
        enum Strategy { hawk, dove };       //Only allow these play styles when creating a creature
        static string strategyNames[2];     //Declare array where we "map" enum values to their strings                    
        
        //CONSTRUCTORS
        Creature();                   //Default constructor declaration
        Creature(Strategy strat);     //Creature type constructor declaration

        //MEMBER FUNCTIONS
        long Get_creatureID();
        string Get_creatureType();
        
        void Set_creatureType(Strategy strat);

    private: 
        //MEMBER VARIABLES
        static long id;
        long creatureID;
        Strategy creatureType;
    
};

#endif