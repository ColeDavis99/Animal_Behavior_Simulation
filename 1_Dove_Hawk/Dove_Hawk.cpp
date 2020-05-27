/*======================================================
Cole Davis
5/27/20

Evolution of Agression Simulator (Exploring Game Theory)
Inspired by Primer's YouTube Video: https://www.youtube.com/watch?v=YNMkADpvO4w
=======================================================*/

#include "headerFile.h"
#include "creature.h"
#include "area.h"

using namespace std;

int main()
{
    //SIMULATION CONSTANTS
    const long PLAYFIELD_SIZE = 100;
    const long NUM_CREATURES_MAX = PLAYFIELD_SIZE * 2;  //Cap the number of creatures in the simulation, else we'll eventually have 3 per area which is undefined.

    const long DOVE_SPAWN_NUM = 5;                  //Number of doves to start simulation with
    const long HAWK_SPAWN_NUM = 5;                 //Number of hawks to start simulation with

    const float DOVE_WITH_HAWK_SURVIVAL_PROB = 0.5; //Death rate of doves when they meet a hawk
    const float HAWK_WITH_HAWK_SURVIVAL_PROB = 0.0; //Death rate of both hawks when they meet eachother

    const float HAWK_WITH_DOVE_REPRO_PROB = 0.5;    //Reproduction chance of hawk when dove is met



    //General Variables
    long spawnIndex = 0;

    //This is where creatures will spawn each simulation turn
    Area playField[PLAYFIELD_SIZE];
    std::vector<Creature> allCreatures;

    //Random seed
    srand(time(NULL));

    //Initial populating
    for(int i=0; i<DOVE_SPAWN_NUM; i++)
    {
        allCreatures.push_back(Creature(Creature::Strategy::dove)); //Creature constructor passed an enum value
    }

    for(int i=0; i<HAWK_SPAWN_NUM; i++)
    {
        allCreatures.push_back(Creature(Creature::Strategy::hawk)); //Creature Constructor passed an enum value
    }


    //Now we need to spawn the creatures into the playfield and have them reproduce and kill eachother and whatnot
    




    // Create a creature with default constructor and setters
    // Creature testCreature;
    // testCreature.Set_creatureType(Creature::Strategy::dove);
    // cout<<"TEST HERE"<<endl;
    // cout<<testCreature.Get_creatureType()<<endl;
    // cout<<"end test"<<endl<<endl;

    //View all hawks and doves ID's and types
    // for(int i=0; i<DOVE_SPAWN_NUM+HAWK_SPAWN_NUM; i++)
    // {
    //     cout<<allCreatures[i].Get_creatureID()<<endl;
    //     cout<<allCreatures[i].Get_creatureType()<<endl<<endl;
    // }
    return 0;
}