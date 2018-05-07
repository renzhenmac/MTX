/********* ucode.c file: syscall interface fucntions *******/
int getpid() 		{
	return syscall(0,0,0,0);
}
int ps() 		{
	return syscall(1,0,0,0);
}
int chname(char *s) 	{
	return syscall(2,s,0,0);
}
int kfork() 		{
	return syscall(3,0,0,0);
}
int kswitch() 		{
	return syscall(4,0,0,0);
}
int wait(int *status) 	{
	return syscall(5,status,0,0);
}
int exit(int exitValue)	{
	return syscall(6,exitValue,0,0);
}
int fork()            	{
	return syscall(7,0,0,0);
}
int exec(char *s)	{
	return syscall(8,s,0,0);
}
int uvfork()		{
	return syscall(9,0,0,0);
}
int creat_pipe(int pd[2]) {
	return syscall(30,pd,0,0);
}
int read_pipe(int fd, char *buf, int n) {
	return syscall(31,fd,buf,n);
}
int write_pipe(int fd, char *buf, int n) {
	return syscall(32,fd,buf,n);
}
int close_pipe(int fd) {
	return syscall(33,fd,0,0);
}
int itimer(int time) {
	return syscall(34,time,0,0);
}
int pipe_stat() {
	return syscall(35,0,0,0);
}

/************* common code of Umode programs **************/
char *cmd[]= {"getpid","ps","chname","kfork","switch","wait","exit","fork","exec","vfork",0};
int show_menu() {
	printf("********************** Menu ************************\n");
	printf("* ps chname kfork switch wait exit fork exec vfork *\n");
	printf("****************************************************\n");
}
int find_cmd(char *name) { // convert cmd to an index
	int i=0;
	char *p=cmd[0];
	while (p) {
		if (!strcmp(p, name))
			return i;
		i++;
		p = cmd[i];
	}
	return -1;
}
/****************** Umode command functions *********************/
int ufork() {
	int pid = fork();
	if (pid) printf("in parent, pid: %d\n",getpid());
	else printf("in child, pid: %d\n",getpid());
}

int vfork() {
	int pid, status;
	char filename[64];
	pid = uvfork();
	if(pid) {
		printf("vfork parent %d waits\n", getpid());
		pid = wait(&status);
		printf("parent %d waited, dead child = %d\n",getpid(),pid);
	} else {
		printf("vforked child %d in segment %x\n",getpid(),getcs());
		printf("exec now! before parent wake up\n");
		printf("Input a file to exec, hurry: ");
		gets(filename);
		exec(filename);
		printf("exec failed! now child process in trouble\n");
		exit(1);
	}


}

int uexec() { // user exec command
	int r;
	char filename[64];
	printf("enter exec filename : ");
	gets(filename);
	printf("new name: %s\n",filename);
	r = exec(filename);
	if(!r)
		printf("exec failed\n");
}

int ukfork() {
	int pid;
	pid = kfork();
	if(pid > 0) printf("%d forked %d\n",getpid(),pid);
	else printf("fault: %d\n",pid);
}
int uswitch() {
	kswitch();
}
int uchname() {
	char s[32];
	printf("input new name : ");
	chname(gets(s)); // assume gets() return pointer to string
}
int uwait() {
	int child, status;
	child = wait(&status);
	printf("proc %d, dead child=%d\n", getpid(), child);
	if (child >= 0) // only if has child
		printf("status=%d\n", status);
}
int uexit() {
	char s[16];
	int exitValue;
	printf("enter exitValue : ");
	exitValue = atoi(gets(s));
	exit(exitValue);
}
