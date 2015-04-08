//written by William Callanan


#include <stdlib.h>
#include <stdio.h>
#include "zombies.h"
//#include <mpi.h>

//does intial world setup
void setupWorld(int* world, int worldsize, player *people, int players){
	PlacePlayers(world, worldsize, people, players);
	ChooseZombie(world, worldsize, people, players);
}
//run simulation for 10000
void runSimulation(int *world, int worldsize, player *people, int players, int numSteps){
	for (int i = 0; i <  numSteps; i++){
		CheckTag(world, worldsize, people, players);
		MoveZombies(world, worldsize, people, players);
		updateWorld(world, worldsize, people, players);
		CheckTag(world, worldsize, people, players);
		MoveZombies(world, worldsize, people, players);
		updateWorld(world, worldsize, people, players);
		CheckTag(world, worldsize, people, players);
		MoveZombies(world, worldsize, people, players);
		updateWorld(world, worldsize, people, players);
		CheckTag(world, worldsize, people, players);
		MoveHumans(world, worldsize, people, players);
		updateWorld(world, worldsize, people, players);
		CheckTag(world, worldsize, people, players);
	}
}
int main(int argc, char** argv){
	int worldsize = 500;
	int players = 500;
	int numSteps = 10000;

	if (argc > 1){
		worldsize = (int)strtol(argv[1], NULL, 10);
	}
	if (argc > 2){
		players = (int)strtol(argv[2], NULL, 10);
		//check that the number of players can't exceed the size of the world 
		if (players > worldsize*worldsize){
			players = worldsize*worldsize;
		}
	}
	if (argc > 3){
		numSteps = (int)strtol(argv[3], NULL, 10);
	}
	int* world = calloc(worldsize*worldsize, sizeof(int));
	player* people;
	people = malloc(sizeof(player) * players);
	
	setupWorld(world, worldsize, people, players);
	runSimulation(world, worldsize, people, players, numSteps);
	

	free(world);
	free(people);
}
