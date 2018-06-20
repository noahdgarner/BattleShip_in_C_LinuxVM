//Noah D Garner
//email: noahguy16@gmail.com
#include <stdio.h>   // Allows printf, ...
#include <string.h>
#include <stdlib.h>  // Allows malloc, ...
#include <errno.h>   // Allows errno
#include "ships.h" //structure creating ships
#include <stdbool.h>
//main


int main(int argc, char *argv[]) {
	
  struct ship frigateA;
  struct ship frigateB;
  struct ship battleShip;
  struct ship carrierShip;
  int fail=0;
  int shells=0;
  int size=0;
  int xLoc=0;
  int yLoc=0;
  int sunkShips=0; //tells how many ships sunk, if = 4, game = over/win
  int gamesPlayed=0;
  int gamesWon=0;
  char** displayGame;
  char** logicGame;
  char userInput[100];
  char temp[100];
  //file i/o variables
  char shipType[5];
  char shipDirect[5];
  char fileXPos[5];
  char fileYPos[5];
  
  if (argc > 1){
	  FILE* fileInput = fopen(argv[1],"r");
	  char buffer[255];
      //need to store file text
      char string1[50];
      char string2[50];
      char string3[50];
      int fileLine = 0;
      if (fileInput == NULL) {
		  printf("Error! Missing File!\n");
		  return 1;
	  }
	  else {
		  while(fgets(buffer,sizeof(buffer), fileInput)){
			  if(*buffer=='#'){
				  //dont do anything if u see a commment character
				  continue;
			  }
			  sscanf(buffer,"%s %s %s \n", string1, string2, string3);
			  shipType[fileLine]=string1[0];
			  shipDirect[fileLine]=string2[0];
			  fileXPos[fileLine]=string3[0];
			  fileYPos[fileLine]=string3[1];
			  fileLine++;
		  }
	  }
	  fclose(fileInput);
  }
  
  do{

	  gamesPlayed++;
	  printf("Welcome to Frigate!\n\n");
	  printf("How large should I make the grid? ");
	  fgets(userInput,5,stdin);
	  sscanf(userInput,"%d",&size);
	  shells = (size*size)/2;
	  if(argc>1){
		 if(size<8){
			printf("The minimum grid size in demo mode is 8... I'll create one of that size.\n\n");
			size = 8;
	  }
	  }
	  else if(size < 5){
		 printf("The minimum grid size is 5... I'll create one of that size.\n\n");
		 size = 5;
	  }
	  else if(size > 20){
		 printf("The maximum grid size is 20... I'll create one of that size.\n\n");
		 size = 20;
	  }
	  else{
		printf("Creating a grid of that size now.\n\n");
	  }
	  
      //set up the game
	  displayGame = createArray(size, size);
	  logicGame = createArray(size, size);
	  
	  fillArray(logicGame, size, size);
	  fillArray(displayGame, size, size);
	  printArray(displayGame, size, size);
	  
	  
	  
	  if(argc>1){		  
		  
	  }
	  else{
		  carrierShip = carrier(logicGame, size);
		  battleShip = battle(logicGame, size);
		  frigateA = frigate(logicGame, size);
		  frigateB = frigate(logicGame, size);
	  }
	  //repeats until all ships are sunk or out of shells
	  do {
		  //did user enter a good location?
		  do{
			  fail=0;
			  do{
				  printf("Please enter the coordinate of your shot.(%i shell(s) remaining) ",shells);
				  fgets(userInput, sizeof userInput, stdin);
				  xLoc=userInput[0]-'A';
				  temp[0]=userInput[1];
				  temp[1]=userInput[2];
				  yLoc=atoi(temp);
			  }while(checkInput(userInput) == 1);
			 
			  if(userInput[2] != '\n'){
				  if(userInput[0]>='A' && userInput[0]<='Z'){
					  xLoc=userInput[0]-'A';
					  temp[0]=userInput[1];
					  temp[1]=userInput[2];
					  yLoc=atoi(temp);
				  }
				  else if(userInput[0]>='a' && userInput[0]<='z'){
					  xLoc=userInput[0]-'a';
					  temp[0]=userInput[1];
					  temp[1]=userInput[2];
					  yLoc=atoi(temp);
				  }
				  if(userInput[2]>='A' && userInput[2]<='Z'){
					  xLoc=userInput[2]-'A';
					  temp[0]=userInput[1];
					  temp[1]=userInput[2];
					  yLoc=atoi(temp);
				  }
				  else if(userInput[2]>='a' && userInput[2]<='z'){
					  xLoc=userInput[2]-'a';
					  temp[0]=userInput[1];
					  temp[1]=userInput[2];
					  yLoc=atoi(temp);
				  }
				  if(xLoc>=(size) || yLoc-1 > size){
					  printf("That coordinate is out of bounds.\n");
					  fail=1;
				  }
			  }
			  else if(userInput[2] == '\n'){
				  if(userInput[0]>='A' && userInput[0]<='Z'){
					  xLoc=userInput[0]-'A';  
				  }
				  else if(userInput[0]>='a' && userInput[0]<='z'){
					  xLoc=userInput[0]-'a';  
				  }
				  else if(userInput[0]>='0' && userInput[0]<='9'){
					  yLoc=userInput[0]-'0';  
				  }
				  
				  if(userInput[1]>='A' && userInput[1]<='Z'){
					  xLoc=userInput[1]-'A';  
				  }
				  else if(userInput[1]>='a' && userInput[1]<='z'){
					  xLoc=userInput[1]-'a';  
				  }
				  else if(userInput[1]>='0' && userInput[1]<='9'){
					  yLoc=userInput[1]-'0';  
				  }
				  if(xLoc>=(size) || yLoc-1 > size){
					  printf("That coordinate is out of bounds.\n");
					  fail=1;
				  }
			  }
			  if(displayGame[yLoc][xLoc] == 'h' || displayGame[yLoc][xLoc] == 'm'){
				  printf("You already shot that coordinate!\n");
				  fail=1;
			  }
		  }while(fail==1);
		  //rid newline character so user string prints
		  
		  //lets see if they got a hit or a miss, and update the display while we're at it
		  if(logicGame[yLoc][xLoc] != '-'){
	          displayGame[yLoc][xLoc]='h';
			  //which boat was hit from logic game
			  if(logicGame[yLoc][xLoc] == 'c'){
				carrierShip.health--;
				if(carrierShip.health==0){
					printf("You sunk a carrier ship!\n");
					sunkShips++;
				}
			  }
			  if(logicGame[yLoc][xLoc] == 'b'){
				battleShip.health--;
				if(battleShip.health==0){
					printf("You sunk a battle ship!\n");
					sunkShips++;
				}
			  }
			  if(logicGame[yLoc][xLoc] == 'f' && (frigateA.ycoord==yLoc && frigateA.xcoord == xLoc)){
				frigateA.health--;
				if(frigateA.health==0){
					printf("You a sunk frigate!\n");
					sunkShips++;
				}
			  }
			  if(logicGame[yLoc][xLoc] == 'f' && (frigateB.ycoord==yLoc && frigateB.xcoord == xLoc)){
				frigateB.health--;
				if(frigateB.health==0){
					printf("You a sunk frigate!\n");
					sunkShips++;
				}
			  }
			  char x = xLoc+'A';
			  printf("%c%d is a hit!\n\n",x,yLoc);
			  printArray(displayGame, size, size);
	      }
		  if(logicGame[yLoc][xLoc] == '-'){
			  char x = xLoc+'A';
			  displayGame[yLoc][xLoc]='m';
			  printf("%c%d is a miss.\n\n",x,yLoc);
			  printArray(displayGame, size, size);
		  }

		  //track shells
		  shells--;
	  }while((sunkShips < 4 && shells > 0));
	 
	  //did they sink them all or run out of shells
	  if(sunkShips == 4){
		 printf("\nYou sunk all ships. Congratulations!\n\n");
		 gamesWon++;
	  }
	  else if(shells == 0){
		 printf("\nYou do not have enough shells to sink the remaining ships.\n\n");
		 printf("Here are the original ship locations.\n\n");
		 printArray(logicGame,size,size);
	  }
	  
	  //get user input here for continue game, also validates
	  do{
		 printf("Play again (Y/N)? ");
		 fgets(userInput,5, stdin);
		 if(userInput[0] == 'n'|| userInput[0] == 'y'|| userInput[0] == 'N'|| userInput[0] == 'Y'){
			fail = 0;
		 }
		 else{
			printf("Error. Invalid input.\n");
			fail = 1;
		 }
	  }while(fail == 1);
  
  //outer while for starting new game
  }while (userInput[0] =='y'||userInput[0]=='Y');
 
  //game over
  printf("You won %i out of %i games.\n\nThanks for playing!\n\n",gamesWon,gamesPlayed); 
  deleteArray(displayGame, size);
  deleteArray(logicGame, size);
  return EXIT_SUCCESS;
}
