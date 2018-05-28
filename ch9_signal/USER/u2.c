#include "ucode.c"

// It works and I DON"T KNOW WHY
// the divide-zero's assembly code is "idiv bx"
// the "right" way is write an assembly function divide_zero_handler, and change bx into something not zero by yourself.
void divide_zero_handler(int i){
	printf("Umode: divide by zero handler is running...\n");
	printf("signum is %d\n", i);
}

int main(void){
	int i = 9, j = 0, k;
	printf("----- U2 Umode: handler address is %d -----\n", divide_zero_handler);
	printf("u2 pss is %d\n", getss());
	install_handler(8, (int)divide_zero_handler);
	printf("Umode: going to divide zero\n");
	k = i / j;
	printf("Umode: line after divided zero, should not see me ;-)\n");
	printf("Umode: k is %d, which is meaningless \n", k);
	printf("Umode: U2 calling exit(0) byebye \n");	
	exit(0);
}
