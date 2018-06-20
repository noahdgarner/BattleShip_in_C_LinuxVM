//Noah D Garner
//email: noahguy16@gmail.com
#ifndef SHIPS
#define SHIPS
//base ship struct for ships.c
struct ship
{
	char type;
	int size;
	int health;
	int xcoord;
	int ycoord;
	int isVertical;
};

//prototypes
struct ship someShip(char** shipArray,char type,char isVert,int x,int y,int size, int sSize,int hp);
struct ship randomShip(struct ship aShip,int size,char** shipArray);
_Bool checkSpaces(struct ship someShip, char** shipArray, int size);
struct ship frigate(char** shipArray, int size);
struct ship battle(char** shipArray, int size);
struct ship carrier(char** shipArray, int size);
int checkInput(char* c);
char** createArray(int rows, int cols);
void fillArray(char** myArray, int rows, int cols);
void printArray(char** myArray, int rows, int cols);
void deleteArray(char** myArray, int rows);

#endif	
