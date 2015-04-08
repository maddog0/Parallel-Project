#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "zombies.h"

//Written by William Callanan for CSC 333 final project


//prints the world
void PrintWorld(int *world, int worldsize){
	for (int i = 0; i < worldsize; i++){
		for (int j = 0; j < worldsize; j++){
			printf("%d ", world[i*worldsize + j]);
		}
		printf("\n");
	}
	printf("\n");
}

//intates through all the zombies and determines what the proper moves
//Zombies will move one space in the world towards the closest human they can see
//Zombie sight is within 5 squares of the zombie
void MoveZombies(int *world, int worldsize, player *people, int players){
	for (int i = 0; i < players; i++){
		if (people[i].isZombie == 1){
			for (int j = 0; j < 5; j++){
				if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord)] == 1){
					people[i].xcoord += 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord)] == 1){
					people[i].xcoord -= 1;
				}
				else if (world[(people[i].xcoord) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].ycoord += 1;
				}
				else if (world[(people[i].xcoord) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].ycoord -= 1;
				}
				else if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].xcoord += 1;
					people[i].ycoord += 1;
				}
				else if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].xcoord += 1;
					people[i].ycoord -= 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].xcoord -= 1;
					people[i].ycoord -= 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].xcoord -= 1;
					people[i].ycoord += 1;
				}
			}
		}
	}
	
}

//Iterates through all the humans and determines the proper moves
//Humans will move one space directly away from the  closest zombie *NOTE BEHAVIOR CHANGE FROM ORIGINAL DESIGN
//we are assuming humans can't see in 360 at once, so if 2 zombies are 2 away on each side of human the approprate
//behavior will still be to run directly at the zombie behind
void MoveHumans(int *world, int worldsize, player *people, int players){
	for (int i = 0; i < players; i++){
		if (people[i].isZombie == 0){
			for (int j = 0; j < 5; j++){
				if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord)] == 1){
					people[i].xcoord -= 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord)] == 1){
					people[i].xcoord += 1;
				}
				else if (world[(people[i].xcoord) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].ycoord -= 1;
				}
				else if (world[(people[i].xcoord) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].ycoord += 1;
				}
				else if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].xcoord -= 1;
					people[i].ycoord -= 1;
				}
				else if (world[(people[i].xcoord + 1) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].xcoord -= 1;
					people[i].ycoord += 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord - 1)] == 1){
					people[i].xcoord += 1;
					people[i].ycoord += 1;
				}
				else if (world[(people[i].xcoord - 1) * worldsize + (people[i].ycoord + 1)] == 1){
					people[i].xcoord -= 1;
					people[i].ycoord += 1;
				}
			}
		}
	}
}

//Checks radius 1 around all zombies, if a human is found they are converted into a zombie
//this is checked before and after any move
void CheckTag(int *world, int worldsize, player *player, int players){
	for (int i = 0; i < players; i++){
		if (player[i].isZombie == 1){
			for (int j = 0; j < players; j++){
				if (player[j].isZombie == 0){
					if (player[i].xcoord - player[j].xcoord == 1 || player[i].ycoord - player[j].ycoord == 1){
						TagHuman(player[j]);
					}
				}
			}
		}
	}
}

//Places all the players in the world before the simulation starts
//uses a random number generator to select locations, I will try to find a generator that
//won't use the same values twice, if there isn't one then I will preform a check to make sure a player isn't already
//in the selcted location, if there is a conflict the generator will select a new position
void PlacePlayers(int *world, int worldsize, player *people, int players){
	for (int i = 0; i < players; i++){
		int x = rand() % players;
		int y = rand() % players;
		while (world[x * worldsize + y == 1]){
			x = rand() % players;
			y = rand() % players;
		}
		people[i].xcoord = x;
		people[i].ycoord = y;
	}
}

//Called one time after the players have all been placed, uses a random number generator to select the
//original zombie/s
void ChooseZombie(int *world, int worldsize, player *people, int players){
	int i;
	time_t t;
	i = rand() % players;
	TagHuman(people[i]);
}

//given a human turn it into a zombie
void TagHuman(player human){
	human.isZombie = 1;
}

//updates the world with the new locations 
void updateWorld(int *world, int worldsize, player *people, int players){
	for (int i = 0; i < players; i++){
		if (people[i].isZombie == 0){
			world[people[i].xcoord *worldsize + people[i].ycoord] = 1;
		}
		else{
			world[people[i].xcoord *worldsize + people[i].ycoord] = 2;
		}
	}
}

//Movement functions

void MoveUp(player toBeMoved){
	toBeMoved.xcoord += 1;
}

void MoveDown(player toBeMoved){
	toBeMoved.xcoord -= 1;
}

void MoveRight(player toBeMoved){
	toBeMoved.ycoord += 1;
}

void MoveLeft(player toBeMoved){
	toBeMoved.ycoord -= 1;
}

void MoveDiagonalUpRight(player toBeMoved){
	toBeMoved.xcoord += 1;
	toBeMoved.ycoord += 1;
}

void MoveDiagonalUpLeft(player toBeMoved){
	toBeMoved.xcoord += 1; 
	toBeMoved.ycoord -= 1;
}

void MoveDiagonalDownRight(player toBeMoved){
	toBeMoved.xcoord -= 1;
	toBeMoved . ycoord += 1;
}

void MoveDiagonalDownLeft(player toBeMoved){
	toBeMoved.xcoord -= 1;
	toBeMoved.ycoord -= 1;
}
