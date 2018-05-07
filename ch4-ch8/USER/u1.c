#include "ucode.c"
main( ) {
	int u2, pid, status;
	char tmp[2];
	u2 = fork();
	printf("Umode: forked u2 as %d\n",u2);
	if (u2) { // P1 runs in a while(1) loop
		printf("--- u1: ---\n");
		ps();
		while(1) {
			printf("u1: press to swtich\n");
			gets(tmp);
			kswitch();			
		}
	} else {
		exec("/bin/u2"); // child of P1 runs u2
	}
}
