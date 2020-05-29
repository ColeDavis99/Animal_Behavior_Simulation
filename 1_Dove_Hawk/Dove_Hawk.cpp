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
    const long PLAYFIELD_SIZE = 20;
    const long NUM_CREATURES_MAX = PLAYFIELD_SIZE * 2;  //Cap the number of creatures in the simulation, else we'll eventually have 3 per area which is undefined.
    const long NUM_SIMULATION_DAYS = 1;

    const long DOVE_SPAWN_NUM = 5;                      //Number of doves to start simulation with
    const long HAWK_SPAWN_NUM = 5;                      //Number of hawks to start simulation with

    const float DOVE_WITH_HAWK_SURVIVAL_PROB = 0.5;     //Survival probability of a dove when it meets a hawk
    const float HAWK_WITH_HAWK_SURVIVAL_PROB = 0.0;     //Survival probability of both hawks when they meet eachother

    const float HAWK_WITH_DOVE_REPRO_PROB = 0.5;        //Reproduction chance of hawk when dove is met


    //General Variables
    long numAliveCreatures = 0;

    Area playField[PLAYFIELD_SIZE];         //Where creatures will spawn each simulation turn
    std::vector<long> openPlayFieldIdx;     //Vector that holds shuffled list of playField indeces [0, PLAYFIELD_SIZE -1] where each value appears twice. Used in assigning creatures to spaces efficiently.
    std::vector<Creature> aliveCreatures;   //Holds all alive creatures
    std::vector<Creature> deadCreatures;    //Holds all dead creatures

    //Seed
    srand(time(NULL));

    //Initial dove creation
    for(int i=0; i<DOVE_SPAWN_NUM; i++)
        aliveCreatures.push_back(Creature(Creature::Strategy::dove)); //Creature constructor passed an enum value

    //Initial hawk creation
    for(int i=0; i<HAWK_SPAWN_NUM; i++)
        aliveCreatures.push_back(Creature(Creature::Strategy::hawk)); //Creature Constructor passed an enum value


    //Initialize openPlayField with two copies of every playField index. It's two copies since a max of two creature can occupy the same space. We'll iterate down the list of indeces to assign the creatures their spots.
    for(int i=0; i<2; i++){
        for(long q=0; q<PLAYFIELD_SIZE; q++){
            openPlayFieldIdx.push_back(q);
        }
    }

    //Shuffle our openIndex values
    std::random_shuffle(openPlayFieldIdx.begin(), openPlayFieldIdx.end());




    /*==============================
       MAIN SIMULATION LOOP BELOW
    ===============================*/


    //Now we need to spawn the creatures into the playfield and have them reproduce and kill eachother and whatnot
    for(int i=0; i<NUM_SIMULATION_DAYS; i++)
    {
        //Have each alive creature randomly get assigned an open spot somewhere in the playField
        numAliveCreatures = aliveCreatures.size();
        for(long q=0; q<numAliveCreatures; q++)
        {
           playField[openPlayFieldIdx[q]].AddCreature(&aliveCreatures[q]);
        }

        //Display all creatureID's in their spot
        for(long r = 0; r<PLAYFIELD_SIZE; r++)
        {
            playField[r].showCreatureIDs();
            cout<<endl;
        }

        //Look at each placed creature and their situation, and alter values accordingly to the situation.

    }




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