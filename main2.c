#include <stdio.h>
int a = 53;
int b = 120;
int c = 36;
int g (int a){
	printf("4.%d\n",b);
	int c = b;
	int b = a+c;
	printf("5.%d\n",b);
	return b;
}

int f (int a){
	int b = a+5;
	printf("3.%d\n",b);
	
	return g(b);
}

int main() {
	
	printf("1.%d\n",b);
	int b = a;
	printf("2.%d\n",b);
	int c = f(b);
	printf("6.%d",c);
	return 0;
}
