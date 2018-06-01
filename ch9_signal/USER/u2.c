#include "ucode.c"

// i is changed because it's in uPS+13 in the umode stack, where sig# is inserted as Figure 9.2 shows in the book
// see the README.txt
extern void divide_zero_handler();

int main(void){
	int i = 9, j = 0, k;
	printf("----- U2 Umode: handler address is %d -----\n", divide_zero_handler);
	printf("u2 pss is %d\n", getss());
	install_handler(8, (int)divide_zero_handler);
	printf("Umode: going to divide zero\n");
	k = i / j;
	printf("Umode: line after divided zero, should not see me ;-)\n");
	printf("Umode: i is %d now \n", i);
	printf("Umode: U2 calling exit(0) byebye \n");	
	exit(0);
}
