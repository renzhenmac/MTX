#include "ucode.c"

int pd[2], n, i;
char line[256], tmp[2], *s="| 16 char data |";
int main() {
	printf("Press ENTER to show pipe?\n");
	gets(tmp);
	creat_pipe(pd); // create a pipe
	if (fork()) { // fork a child as READER, parent as WRITER
		printf("pipe stat: ");
		pipe_stat();
		printf("\n");
		close_pipe(pd[0]);
		while(i++ < 10) { // parent writes to pipe 10 times
//			printf("%d: parent %d writing pipe : %s | ", i, getpid(), s);
			write_pipe(pd[1], s, strlen(s));
		}
		close_pipe(pd[1]);
		kswitch();
	} else { // child as pipe READER
		printf("******child start*******\n");
		close_pipe(pd[1]);
		while(1) { // child read from pipe
			if ((n = read_pipe(pd[0], line, 128)) == 0){				
				printf("Child %d: no writer no data, exit...\n", getpid());
				close_pipe(pd[0]);
				exit(0);
			}
			line[n]=0;
//			printf("child %d got line: %s n=%d | ", getpid(), line, n);
		}
	}
}
