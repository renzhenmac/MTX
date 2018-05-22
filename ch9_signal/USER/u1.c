#include "ucode.c"
main( ) {
	int u2, pid, status;
	char tmp[2];
	u2 = fork();
	printf("Umode: forked u2 as %d\n",u2);
//	ps();
	if (u2) { // P1 runs in a while(1) loop
		while(1) {
			printf("u1 goto sleep\n");
//			ps();
			pid = wait(&status); // wait for ANY child to die
			printf("u1 woke up, got child pid: %d\n",pid);
			if (pid == u2) {
				printf("u1: %d exit, fork another u2\n", u2);
				u2 = fork();
				if(u2)	printf("u1: new u2 pid: %d\n",u2);
				else	exec("/bin/u2");
				printf("P1: press ENTER to continue the loop\n");
				gets(tmp);
				continue;
			}
			printf("P1: I just buried an orphan %d\n", pid);
		}
	} else {
		exec("/bin/u2"); // child of P1 runs u2
	}
}
