#include "ucode.c"

int main(void){
	printf("Yo, inside u2\n");
	ps();
	printf("sleep for 3 seconds\n");
	itimer(3);	
	printf("Yo, wake up now\n");
	return 0;
}