//Noah D Garner
//email: noahguy16@gmail.com
#include <stdio.h>   // Allows printf, ...
#include <string.h>
#include <stdlib.h>  // Allows malloc, ...
#include <errno.h>   // Allows errno
#include <stdbool.h>
#include <time.h>
#include "ships.h"
//intitializes a frigate ship struct



struct ship frigate(char** shipArray, int size) {
  struct ship frigate;
  frigate.type = 'f';
  frigate.size = 2;
  frigate.health = 2;
  randomShip(frigate,size,shipArray);
	
  return frigate;
}

//initializes a battle ship struct
struct ship battle(char** shipArray, int size) {
  struct ship battle;
  battle.type = 'b';
  battle.size = 4;
  battle.health = 3;
  randomShip(battle,size,shipArray);
	
  return battle;
}

//initializes a carrier ship struct
struct ship carrier(char** shipArray, int size) {
  struct ship carrier;
  carrier.type = 'c';
  carrier.size = 5;
  carrier.health = 4;
  randomShip(carrier,size, shipArray);
  
  return carrier;
}

//randomizes a selected carrier/battle/frigate and sends to check spaces function for placement
struct ship randomShip(struct ship aShip,int size,char** shipArray){
  do{
	  srand(time(NULL));
	  if(rand()%2 == 1){
		aShip.isVertical=1;
	  }
	  else{
	    aShip.isVertical=0;
	  }
	  aShip.xcoord = rand()%(size-1);
	  aShip.ycoord = rand()%(size-1);
   } while(!checkSpaces(aShip,shipArray,size));
   return aShip;
}
struct ship someShip(char** shipArray,char type,char isVert,int x,int y,int size,int sSize, int hp){
	struct ship aShip;
	aShip.type=type;
	aShip.xcoord=x;
	aShip.ycoord=y;
	if(isVert=='r'){
		aShip.isVertical=1;
	  }
	  else{
	    aShip.isVertical=0;
	  }
	aShip.health=hp;
	aShip.size=sSize;
	checkSpaces(aShip,shipArray,size);
	
	return aShip;
	
}
	
	
//checks availability on logic board. Returns false if out of bounds or something else is placed
_Bool checkSpaces(struct ship someShip, char** shipArray, int size) {
  if(someShip.isVertical == 1){
    if(someShip.ycoord + someShip.size > size){
      return false;
    }
    for(int i = 0;i<someShip.size;i++){
		if(shipArray[someShip.ycoord+i][someShip.xcoord] != '-'){
			return false;
		}
	}
    for(int i = 0;i<someShip.size;i++){
	  shipArray[someShip.ycoord+i][someShip.xcoord] = someShip.type;
	}
  }
  //if the ship is not vertical (ie horizontal)
  else {
	if(someShip.xcoord + someShip.size > size){
      return false;
    }
    for(int i = 0;i<someShip.size;i++){
		if(shipArray[someShip.ycoord][someShip.xcoord+i] != '-'){
			return false;
		}
	}
    for(int i = 0;i<someShip.size;i++){
	  shipArray[someShip.ycoord][someShip.xcoord+i] = someShip.type;
	}   
  }
  return true;
}
//user input checker
int checkInput(char* c){
  //first check if its 3 chars long, e.g. e15, 20D, etc, note 2AB will not work here
  if(c[2] != '\n'){
	  if((c[0]>= 'A' && c[1]>='A')||(c[0]>= 'A' && c[2]>='A')||(c[1]>= 'A' && c[2]>='A')||
		 (c[0] < 'A' && c[1] <'A' && c[2] < 'A')||c[0]>'z' || c[1] > 'z' || c[2] > 'z'){
		  printf("That coordinate is not on the board.\n");
		  return 1;
	  }
	  if(c[1]>='a'){
	      printf("Error. That coordinate does not exist.\n");
	      return 1;
	  }
	  if(c[3] !='\n') {
		  if(c[4] !='\n')
		  printf("You did not enter a real coordinate.\n");
		  return 1;
	  }
	  if(c[1] == '\n'){
		  printf("You did not enter a real coordinate.\n");
		  return 1;
	  }
  }
  //now two letters
  else if (c[2] == '\n'){
	  if((c[0]>='A' && c[1]>='A') || (c[0] < 'A' && c[1] < 'A') || c[0] > 'z' || c[1] > 'z'){
		  printf("You did not enter a real coordinate.\n");
	      return 1;  
	  }
	  if(c[0]>='A' && c[0]<='Z'){
		  return 0;
	  }
	  else if(c[0]>='a' && c[0]<='z'){
	      return 0;
	  }
	  else if(c[0]>='0' && c[0]<='9'){
	      return 0;
	  }
	  else{
		  printf("You did not enter a real coordinate.\n");
		  return 1;
	  }
	   
	  if(c[1]>='A' && c[1]<='Z'){
		  return 0;
	  }
	  else if(c[1]>='a' && c[1]<='z'){
		  return 0;
	  }
	  else if(c[1]>='0' && c[1]<='9'){
		  return 0;
	  }
	  else{
		  printf("You did not enter a real coordinate.\n");
		  return 1;
	  }
  }
  
}

//pregiven functions for dynamic allocaiton of 2D arrays
char** createArray(int rows, int cols) {
  char **myArray;
  
  // Allocate a 1xROWS array to hold pointers to more arrays
  myArray = calloc(rows, sizeof(int *));
  if (myArray == NULL) {
    printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  // Allocate each row in that column
  for (int i = 0; i < rows; i++) {
    myArray[i] = calloc(cols, sizeof(int));
    if (myArray[i] == NULL) {
      printf("FATAL ERROR: out of memory: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  
  return myArray;
}

void fillArray(char** myArray, int rows, int cols) {
  char c = '-';
  
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      myArray[i][j] = c;
    }
  }
  
  return;
}

void printArray(char** myArray, int rows, int cols) {
  char letterAcross='A';
  int numberDown=0;
  printf("     ");
  for(int i =0;i<rows;i++){
	printf("%c ",letterAcross);
	letterAcross++; 
  }
  printf("\n   +");
  for(int i =0;i<rows;i++){
	printf("--");
	letterAcross++; 
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
	  if(j == 0){
		if(numberDown>=10){
		  printf("%i | ",numberDown);
		  numberDown++; 
	    }
	    else{ 
		  printf("%i  | ",numberDown);
		  numberDown++;
	    }
	  }
      printf("%c ", myArray[i][j]);
    }
    printf("\n");
  }
}

void deleteArray(char** myArray, int rows) {
	for (int i = 0; i < rows; i++) {  
		free(myArray[i]);
    }
  free(myArray);
  
  return;
}
