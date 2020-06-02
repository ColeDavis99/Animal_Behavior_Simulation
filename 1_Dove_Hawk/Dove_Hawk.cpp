/*======================================================
Cole Davis
5/27/20

Evolution of Aggression Simulator (Exploring Game Theory)
Inspired by Primer's YouTube Video: https://www.youtube.com/watch?v=YNMkADpvO4w
=======================================================*/

#include "headerFile.h"
#include "creature.h"
#include "area.h"
#include <string>

using namespace std;

int main()
{
    //SIMULATION CONSTANTS
    const long DOVE_SPAWN_NUM = 1;                      //Number of doves to start simulation with
    const long HAWK_SPAWN_NUM = 1;                      //Number of hawks to start simulation with
    
    const long EXTRA_SPACE = 2000;
    const long PLAYFIELD_SIZE = DOVE_SPAWN_NUM + HAWK_SPAWN_NUM + EXTRA_SPACE;            //Must be at least                    
    const long NUM_CREATURES_MAX = PLAYFIELD_SIZE * 2;                                    //Cap the number of creatures in the simulation, else we'll eventually have 3 per area which is undefined.
    const long NUM_SIMULATION_DAYS = 80;


    const float DOVE_WITH_HAWK_SURVIVAL_PROB = 0.5;     //Survival probability of a dove when it meets a hawk
    const float HAWK_WITH_HAWK_SURVIVAL_PROB = 0.0;     //Survival probability of both hawks when they meet eachother

    const float HAWK_WITH_DOVE_REPRO_PROB = 0.5;        //Reproduction chance of hawk when dove is met


    //General Variables
    long preNumAliveCreatures = 0;
    long postNumAliveCreatures = 0;
    long numDoves = 0;
    long numHawks = 0;
    string visualizer = "";

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

    //Initial output
    cout << "========================================== DAY " << 0 << " ==========================================" << endl;
    cout << "Num doves: " << DOVE_SPAWN_NUM << endl;
    cout << "Num hawks: " << HAWK_SPAWN_NUM << endl;
    cout << "Total creatures: " << aliveCreatures.size() << endl;

    /*==============================
       MAIN SIMULATION LOOP BELOW
    ===============================*/

    //Now we need to spawn the creatures into the playfield and have them reproduce and kill eachother and whatnot
    for(int i=0; i<NUM_SIMULATION_DAYS; i++)
    {
        //Shuffle our openIndex values
        std::random_shuffle(openPlayFieldIdx.begin(), openPlayFieldIdx.end());

        //Assign every alive creature a spot somewhere in the playField (two creatures per spot maximum)
        cout<<endl;
        preNumAliveCreatures = aliveCreatures.size();
        for(long q=0; q<preNumAliveCreatures; q++)
        {
            //cout<<"Adding "<<aliveCreatures[q].Get_creatureType()<<" "<<aliveCreatures[q].Get_creatureID()<<" at space "<<openPlayFieldIdx[q]<<"   "<<&aliveCreatures[q]<<endl;
            playField[openPlayFieldIdx[q]].AddCreature(new Creature(aliveCreatures[q]));
        }


        //Look at each placed creature and their situation, and alter values according to the situation.
        //THIS WOULD BE COOL TO MULTITHREAD
        for(long r=0; r<preNumAliveCreatures; r++)
        {

            // //DEBUG show aliveCreatures
            // cout<<"ALIVE CREATURES: ";
            // for(long i=0; i<aliveCreatures.size(); i++)
            // {
            //     cout<<aliveCreatures[i].Get_creatureID()<<", ";
            // }
            // cout<<endl<<endl;


            // //DEBUG print out entire playfield
            // cout<<"playField "<<endl<<"["<<endl;
            // for(long t=0; t<PLAYFIELD_SIZE; t++)
            // {
            //     cout<<t<<":"<<endl;
            //     playField[t].ShowCreatureIDs();
            //     cout<<endl;
            // }
            // cout<<"]"<<endl<<endl;


            if(playField[openPlayFieldIdx[r]].Get_beenProcessed() == false) //Prevents double CreatureAction when there's two creatures per space.
            {

                //cout<<"looking at playField's index "<<openPlayFieldIdx[r]<<endl;
                //playField[openPlayFieldIdx[r]].ShowCreatureTypes();
                playField[openPlayFieldIdx[r]].CreatureAction(aliveCreatures, deadCreatures, NUM_CREATURES_MAX, DOVE_WITH_HAWK_SURVIVAL_PROB, HAWK_WITH_HAWK_SURVIVAL_PROB, HAWK_WITH_DOVE_REPRO_PROB);
                playField[openPlayFieldIdx[r]].Set_beenProcessed(true);

            }
        }

        //Remove the extra creatures in aliveCreatures if NUM_CREATURES_MAX is exceeded
        if(aliveCreatures.size() > NUM_CREATURES_MAX)
        {
            //cout<<"Removing extras:--------------------------------------------------------------------------------------- "<<aliveCreatures.size()<<endl;
            while(aliveCreatures.size() > NUM_CREATURES_MAX)
            {
                //cout<<"Removing creature "<<aliveCreatures.back().Get_creatureID()<<endl;
                aliveCreatures.pop_back();
            }
        }

        //Reset the playfield
        for(long i=0; i<preNumAliveCreatures; i++)
        {
            playField[openPlayFieldIdx[i]].Clear();
            //playField[openPlayFieldIdx[i]].ShowCreatureMemoryAddrs();
            //playField[openPlayFieldIdx[i]].ShowCreatureMemoryAddrs();
            //cout<<endl;

            //Reset beenProcessed flag on each space
            playField[openPlayFieldIdx[i]].Set_beenProcessed(0);
        }

        if(aliveCreatures.size() == 0)
        {
            cout<<"Everything is dead. Ending simulation."<<endl;

            break;
        }


        //TODO: Output the number of hawks and doves
        postNumAliveCreatures = aliveCreatures.size();
        for(long i=0; i<postNumAliveCreatures; i++)
        {
            if(aliveCreatures[i].Get_creatureType() == "dove")
                numDoves++;
            if(aliveCreatures[i].Get_creatureType() == "hawk")
                numHawks++;
        }


        //Summary
        cout << "========================================== DAY " << i+1 << " ==========================================" << endl;
        cout<<"Num doves: "<<numDoves<<endl;
        cout<<"Num hawks: "<<numHawks<<endl;
        cout<<"Total creatures: "<<aliveCreatures.size()<<endl;

        for(long i=0; i<numDoves; i++)
        {
            if(i%3 == 0)
                visualizer.append("o");
        }
        visualizer.append("\n");

        for(long q = 0; q < numHawks; q++)
        {
            if(q%3 == 0)
                visualizer.append("|");
        }
        visualizer.append("\n\n");

        numHawks = 0;
        numDoves = 0;
    }

    //cout<<visualizer<<endl;

    return 0;
}