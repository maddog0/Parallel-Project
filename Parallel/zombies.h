#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
Author William Callanan 
writen for CSC 333 final project
*/

//tuple structure for storing location data
typedef struct{
	int xcoord; /*x location*/
	int ycoord; /*y location*/
	int isZombie; /*state (human (0) or zombie(1)*/
} player;

//prints the world
void PrintWorld(int *world, int worldsize);

//intates through all the zombies and determines what the proper moves
//Zombies will move one space in the world towards the closest human they can see
//Zombie sight is within 5 squares of the zombie
void MoveZombies(int *world, int worldsize, player *people, int players, int numThreads);

//Iterates through all the humans and determines the proper moves
//Humans will move one space directly away from the  closest zombie *NOTE BEHAVIOR CHANGE FROM ORIGINAL DESIGN
//we are assuming humans can't see in 360 at once, so if 2 zombies are 2 away on each side of human the approprate
//behavior will still be to run directly at the zombie behind
void MoveHumans(int *world, int worldsize, player *people, int players, int numThreads);

//Checks radius 1 around all zombies, if a human is found they are converted into a zombie
//this is checked before and after any move
void CheckTag(int *world, int worldsize, player *player, int players);

//Places all the players in the world before the simulation starts
//uses a random number generator to select locations, I will try to find a generator that
//won't use the same values twice, if there isn't one then I will preform a check to make sure a player isn't already
//in the selcted location, if there is a conflict the generator will select a new position
void PlacePlayers(int *world, int worldsize, player *people, int players);

//Called one time after the players have all been placed, uses a random number generator to select the
//original zombie/s
void ChooseZombie(int *world, int worldsize, player *people, int players);

//given a human convert it to a zombie
void TagHuman(player human);

//update the world
void updateWorld(int *world, int worldsize, player *people, int players);

//Movement functions
void MoveUp(player toBeMoved);

void MoveDown(player toBeMoved);

void MoveRight(player toBeMoved);

void MoveLeft(player toBeMoved);

void MoveDiagonalUpRight(player toBeMoved);

void MoveDiagonalUpLeft(player toBeMoved);

void MoveDiagonalDownRight(player toBeMoved);

void MoveDiagonalDownLeft(player toBeMoved);
