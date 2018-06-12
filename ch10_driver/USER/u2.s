! 1 
! 1 # 1 "u2.c"
! 1 # 1 "ucode.c"
! 1  
! 2 int getpid()
! 3 # 2 "ucode.c"
! 2 {
export	_getpid
_getpid:
! 3 	return syscall(0,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 4 }
! 5 int ps()
! 6 # 5 "ucode.c"
! 5 {
export	_ps
_ps:
! 6 	return syscall(1,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 1 (used reg = )
mov	ax,*1
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 7 }
! 8 int chname(s)
! 9 # 8 "ucode.c"
! 8 char *s;
export	_chname
_chname:
!BCC_EOS
! 9 # 8 "ucode.c"
! 8 {
! 9 	return syscall(2,s,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list * char s = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const 2 (used reg = )
mov	ax,*2
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 10 }
! 11 int kfork()
! 12 # 11 "ucode.c"
! 11 {
export	_kfork
_kfork:
! 12 	return syscall(3,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 3 (used reg = )
mov	ax,*3
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 13 }
! 14 int kswitch()
! 15 # 14 "ucode.c"
! 14 {
export	_kswitch
_kswitch:
! 15 	return syscall(4,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 4 (used reg = )
mov	ax,*4
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 16 }
! 17 int wait(status)
! 18 # 17 "ucode.c"
! 17 int *status;
export	_wait
_wait:
!BCC_EOS
! 18 # 17 "ucode.c"
! 17 {
! 18 	return syscall(5,status,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list * int status = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const 5 (used reg = )
mov	ax,*5
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 19 }
! 20 int exit(exitValue)
! 21 # 20 "ucode.c"
! 20 int exitValue;
export	_exit
_exit:
!BCC_EOS
! 21 # 20 "ucode.c"
! 20 {
! 21 	return syscall(6,exitValue,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int exitValue = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const 6 (used reg = )
mov	ax,*6
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 22 }
! 23 int fork()
! 24 # 23 "ucode.c"
! 23 {
export	_fork
_fork:
! 24 	return syscall(7,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 7 (used reg = )
mov	ax,*7
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 25 }
! 26 int exec(s)
! 27 # 26 "ucode.c"
! 26 char *s;
export	_exec
_exec:
!BCC_EOS
! 27 # 26 "ucode.c"
! 26 {
! 27 	return syscall(8,s,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list * char s = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const 8 (used reg = )
mov	ax,*8
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 28 }
! 29 int uvfork()
! 30 # 29 "ucode.c"
! 29 {
export	_uvfork
_uvfork:
! 30 	return syscall(9,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 9 (used reg = )
mov	ax,*9
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 31 }
! 32 int creat_pipe(pd)
! 33 # 32 "ucode.c"
! 32 int pd[2];
export	_creat_pipe
_creat_pipe:
!BCC_EOS
! 33 # 32 "ucode.c"
! 32 {
! 33 	return syscall(30,pd,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list * int pd = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $1E (used reg = )
mov	ax,*$1E
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 34 }
! 35 int read_pipe(fd,buf,n)
! 36 # 35 "ucode.c"
! 35 int fd;
export	_read_pipe
_read_pipe:
!BCC_EOS
! 36 # 35 "ucode.c"
! 35 char *buf;
!BCC_EOS
! 36 # 35 "ucode.c"
! 35 int n;
!BCC_EOS
! 36 # 35 "ucode.c"
! 35 {
! 36 	return syscall(31,fd,buf,n);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int n = [S+6+6] (used reg = )
push	8[bp]
! Debug: list * char buf = [S+8+4] (used reg = )
push	6[bp]
! Debug: list int fd = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $1F (used reg = )
mov	ax,*$1F
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 37 }
! 38 int write_pipe(fd,buf,n)
! 39 # 38 "ucode.c"
! 38 int fd;
export	_write_pipe
_write_pipe:
!BCC_EOS
! 39 # 38 "ucode.c"
! 38 char *buf;
!BCC_EOS
! 39 # 38 "ucode.c"
! 38 int n;
!BCC_EOS
! 39 # 38 "ucode.c"
! 38 {
! 39 	return syscall(32,fd,buf,n);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int n = [S+6+6] (used reg = )
push	8[bp]
! Debug: list * char buf = [S+8+4] (used reg = )
push	6[bp]
! Debug: list int fd = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $20 (used reg = )
mov	ax,*$20
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 40 }
! 41 int close_pipe(fd)
! 42 # 41 "ucode.c"
! 41 int fd;
export	_close_pipe
_close_pipe:
!BCC_EOS
! 42 # 41 "ucode.c"
! 41 {
! 42 	return syscall(33,fd,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int fd = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $21 (used reg = )
mov	ax,*$21
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 43 }
! 44 int itimer(time)
! 45 # 44 "ucode.c"
! 44 int time;
export	_itimer
_itimer:
!BCC_EOS
! 45 # 44 "ucode.c"
! 44 {
! 45 	return syscall(34,time,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int time = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $22 (used reg = )
mov	ax,*$22
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 46 }
! 47 int pipe_stat()
! 48 # 47 "ucode.c"
! 47 {
export	_pipe_stat
_pipe_stat:
! 48 	return syscall(35,0,0,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int = const $23 (used reg = )
mov	ax,*$23
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 49 }
! 50 int install_handler(sig,func)
! 51 # 50 "ucode.c"
! 50 int sig;
export	_install_handler
_install_handler:
!BCC_EOS
! 51 # 50 "ucode.c"
! 50 int func;
!BCC_EOS
! 51 # 50 "ucode.c"
! 50 {
! 51 	return syscall(36,sig,func,0);
push	bp
mov	bp,sp
push	di
push	si
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: list int func = [S+8+4] (used reg = )
push	6[bp]
! Debug: list int sig = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list int = const $24 (used reg = )
mov	ax,*$24
push	ax
! Debug: func () int = syscall+0 (used reg = )
call	_syscall
add	sp,*8
! Debug: cast int = const 0 to int = ax+0 (used reg = )
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 52 }
! 53 
! 54  
! 55 char *cmd[]= {"getpid","ps","chname","kfork","switch","wait","exit","fork","exec","vfork",0};
.data
export	_cmd
_cmd:
.word	.1+0
.word	.2+0
.word	.3+0
.word	.4+0
.word	.5+0
.word	.6+0
.word	.7+0
.word	.8+0
.word	.9+0
.word	.A+0
.word	0
!BCC_EOS
! 56 int show_menu()
! 57 # 56 "ucode.c"
! 56 {
.text
export	_show_menu
_show_menu:
! 57 	printf("********************** Menu ************************\n");
push	bp
mov	bp,sp
push	di
push	si
! Debug: list * char = .B+0 (used reg = )
mov	bx,#.B
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 58 	printf("* ps chname kfork switch wait exit fork exec vfork *\n");
! Debug: list * char = .C+0 (used reg = )
mov	bx,#.C
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 59 	printf("****************************************************\n");
! Debug: list * char = .D+0 (used reg = )
mov	bx,#.D
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 60 }
pop	si
pop	di
pop	bp
ret
! 61 int find_cmd(name)
! Register BX used in function show_menu
! 62 # 61 "ucode.c"
! 61 char *name;
export	_find_cmd
_find_cmd:
!BCC_EOS
! 62 # 61 "ucode.c"
! 61 { 
! 62 	int i=0;
push	bp
mov	bp,sp
push	di
push	si
dec	sp
dec	sp
! Debug: eq int = const 0 to int i = [S+8-8] (used reg = )
xor	ax,ax
mov	-6[bp],ax
!BCC_EOS
! 63 	char *p=cmd[0];
dec	sp
dec	sp
! Debug: eq * char = [cmd+0] to * char p = [S+$A-$A] (used reg = )
mov	bx,[_cmd]
mov	-8[bp],bx
!BCC_EOS
! 64 	while (p) {
jmp .F
.10:
! 65 		if (!strcmp(p,name))
! Debug: list * char name = [S+$A+2] (used reg = )
push	4[bp]
! Debug: list * char p = [S+$C-$A] (used reg = )
push	-8[bp]
! Debug: func () int = strcmp+0 (used reg = )
call	_strcmp
add	sp,*4
test	ax,ax
jne 	.11
.12:
! 66 			return i;
mov	ax,-6[bp]
add	sp,*4
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 67 		i++;
.11:
! Debug: postinc int i = [S+$A-8] (used reg = )
mov	ax,-6[bp]
inc	ax
mov	-6[bp],ax
!BCC_EOS
! 68 		p = cmd[i];
! Debug: ptradd int i = [S+$A-8] to [$B] * char = cmd+0 (used reg = )
mov	bx,-6[bp]
shl	bx,*1
! Debug: eq * char = [bx+_cmd+0] to * char p = [S+$A-$A] (used reg = )
mov	bx,_cmd[bx]
mov	-8[bp],bx
!BCC_EOS
! 69 	}
! 70 	return -1;
.F:
mov	ax,-8[bp]
test	ax,ax
jne	.10
.13:
.E:
mov	ax,*-1
add	sp,*4
pop	si
pop	di
pop	bp
ret
!BCC_EOS
! 71 }
! 72  
! 73 int ufork()
! Register BX used in function find_cmd
! 74 # 73 "ucode.c"
! 73 {
export	_ufork
_ufork:
! 74 	int pid = fork();
push	bp
mov	bp,sp
push	di
push	si
dec	sp
dec	sp
! Debug: func () int = fork+0 (used reg = )
call	_fork
! Debug: eq int = ax+0 to int pid = [S+8-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 75 	if (pi
! 75 d) printf("in parent, pid: %d\n",getpid());
mov	ax,-6[bp]
test	ax,ax
je  	.14
.15:
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .16+0 (used reg = )
mov	bx,#.16
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 76 	else printf("in child, pid: %d\n",getpid());
jmp .17
.14:
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .18+0 (used reg = )
mov	bx,#.18
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 77 }
.17:
inc	sp
inc	sp
pop	si
pop	di
pop	bp
ret
! 78 
! 79 int vfork()
! Register BX used in function ufork
! 80 # 79 "ucode.c"
! 79 {
export	_vfork
_vfork:
! 80 	int pid, status;
!BCC_EOS
! 81 	char filename[64];
!BCC_EOS
! 82 	pid = uvfork();
push	bp
mov	bp,sp
push	di
push	si
add	sp,*-$44
! Debug: func () int = uvfork+0 (used reg = )
call	_uvfork
! Debug: eq int = ax+0 to int pid = [S+$4A-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 83 	if(pid) {
mov	ax,-6[bp]
test	ax,ax
je  	.19
.1A:
! 84 		printf("vfork parent %d waits\n",getpid());
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .1B+0 (used reg = )
mov	bx,#.1B
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 85 		pid = wait(&status);
! Debug: list * int status = S+$4A-$A (used reg = )
lea	bx,-8[bp]
push	bx
! Debug: func () int = wait+0 (used reg = )
call	_wait
inc	sp
inc	sp
! Debug: eq int = ax+0 to int pid = [S+$4A-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 86 		printf("parent %d waited, dead child = %d\n",getpid(),pid);
! Debug: list int pid = [S+$4A-8] (used reg = )
push	-6[bp]
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .1C+0 (used reg = )
mov	bx,#.1C
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*6
!BCC_EOS
! 87 	} else {
jmp .1D
.19:
! 88 		printf("vforked child %d in segment %x\n",getpid(),getcs());
! Debug: func () int = getcs+0 (used reg = )
call	_getcs
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .1E+0 (used reg = )
mov	bx,#.1E
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*6
!BCC_EOS
! 89 		printf("exec now! before parent wake up\n");
! Debug: list * char = .1F+0 (used reg = )
mov	bx,#.1F
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 90 		printf("Input a file to exec, hurry: ");
! Debug: list * char = .20+0 (used reg = )
mov	bx,#.20
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 91 		gets(filename);
! Debug: list * char filename = S+$4A-$4A (used reg = )
lea	bx,-$48[bp]
push	bx
! Debug: func () int = gets+0 (used reg = )
call	_gets
inc	sp
inc	sp
!BCC_EOS
! 92 		exec(filename);
! Debug: list * char filename = S+$4A-$4A (used reg = )
lea	bx,-$48[bp]
push	bx
! Debug: func () int = exec+0 (used reg = )
call	_exec
inc	sp
inc	sp
!BCC_EOS
! 93 		printf("exec failed! now child process in trouble\n");
! Debug: list * char = .21+0 (used reg = )
mov	bx,#.21
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 94 		exit(1);
! Debug: list int = const 1 (used reg = )
mov	ax,*1
push	ax
! Debug: func () int = exit+0 (used reg = )
call	_exit
inc	sp
inc	sp
!BCC_EOS
! 95 	}
! 96 
! 97 
! 98 }
.1D:
add	sp,*$44
pop	si
pop	di
pop	bp
ret
! 99 
! 100 int uexec()
! Register BX used in function vfork
! 101 # 100 "ucode.c"
! 100 { 
export	_uexec
_uexec:
! 101 	int r;
!BCC_EOS
! 102 	char filename[64];
!BCC_EOS
! 103 	printf("enter exec filename : ");
push	bp
mov	bp,sp
push	di
push	si
add	sp,*-$42
! Debug: list * char = .22+0 (used reg = )
mov	bx,#.22
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 104 	gets(filename);
! Debug: list * char filename = S+$48-$48 (used reg = )
lea	bx,-$46[bp]
push	bx
! Debug: func () int = gets+0 (used reg = )
call	_gets
inc	sp
inc	sp
!BCC_EOS
! 105 	printf("new name: %s\n",filename);
! Debug: list * char filename = S+$48-$48 (used reg = )
lea	bx,-$46[bp]
push	bx
! Debug: list * char = .23+0 (used reg = )
mov	bx,#.23
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 106 	r = exec(filename);
! Debug: list * char filename = S+$48-$48 (used reg = )
lea	bx,-$46[bp]
push	bx
! Debug: func () int = exec+0 (used reg = )
call	_exec
inc	sp
inc	sp
! Debug: eq int = ax+0 to int r = [S+$48-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 107 	if(!r)
mov	ax,-6[bp]
test	ax,ax
jne 	.24
.25:
! 108 		printf("exec failed\n");
! Debug: list * char = .26+0 (used reg = )
mov	bx,#.26
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 109 }
.24:
add	sp,*$42
pop	si
pop	di
pop	bp
ret
! 110 
! 111 int ukfork()
! Register BX used in function uexec
! 112 # 111 "ucode.c"
! 111 {
export	_ukfork
_ukfork:
! 112 	int pid;
!BCC_EOS
! 113 	pid = kfork();
push	bp
mov	bp,sp
push	di
push	si
dec	sp
dec	sp
! Debug: func () int = kfork+0 (used reg = )
call	_kfork
! Debug: eq int = ax+0 to int pid = [S+8-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 114 	if(pid > 0) printf("%d forked %d\n",getpid(),pid);
! Debug: gt int = const 0 to int pid = [S+8-8] (used reg = )
mov	ax,-6[bp]
test	ax,ax
jle 	.27
.28:
! Debug: list int pid = [S+8-8] (used reg = )
push	-6[bp]
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .29+0 (used reg = )
mov	bx,#.29
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*6
!BCC_EOS
! 115 	else printf("fault: %d\n",pid);
jmp .2A
.27:
! Debug: list int pid = [S+8-8] (used reg = )
push	-6[bp]
! Debug: list * char = .2B+0 (used reg = )
mov	bx,#.2B
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 116 }
.2A:
inc	sp
inc	sp
pop	si
pop	di
pop	bp
ret
! 117 int uswitch()
! Register BX used in function ukfork
! 118 # 117 "ucode.c"
! 117 {
export	_uswitch
_uswitch:
! 118 	kswitch();
push	bp
mov	bp,sp
push	di
push	si
! Debug: func () int = kswitch+0 (used reg = )
call	_kswitch
!BCC_EOS
! 119 }
pop	si
pop	di
pop	bp
ret
! 120 int uchname()
! 121 # 120 "ucode.c"
! 120 {
export	_uchname
_uchname:
! 121 	char s[32];
!BCC_EOS
! 122 	printf("input new name : ");
push	bp
mov	bp,sp
push	di
push	si
add	sp,*-$20
! Debug: list * char = .2C+0 (used reg = )
mov	bx,#.2C
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 123 	chname(gets(s)); 
! Debug: list * char s = S+$26-$26 (used reg = )
lea	bx,-$24[bp]
push	bx
! Debug: func () int = gets+0 (used reg = )
call	_gets
inc	sp
inc	sp
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: func () int = chname+0 (used reg = )
call	_chname
inc	sp
inc	sp
!BCC_EOS
! 124 }
add	sp,*$20
pop	si
pop	di
pop	bp
ret
! 125 int uwait()
! Register BX used in function uchname
! 126 # 125 "ucode.c"
! 125 {
export	_uwait
_uwait:
! 126 	int child, status;
!BCC_EOS
! 127 	child = wait(&status);
push	bp
mov	bp,sp
push	di
push	si
add	sp,*-4
! Debug: list * int status = S+$A-$A (used reg = )
lea	bx,-8[bp]
push	bx
! Debug: func () int = wait+0 (used reg = )
call	_wait
inc	sp
inc	sp
! Debug: eq int = ax+0 to int child = [S+$A-8] (used reg = )
mov	-6[bp],ax
!BCC_EOS
! 128 	printf("proc %d, dead child=%d\n",getpid(),child);
! Debug: list int child = [S+$A-8] (used reg = )
push	-6[bp]
! Debug: func () int = getpid+0 (used reg = )
call	_getpid
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: list * char = .2D+0 (used reg = )
mov	bx,#.2D
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*6
!BCC_EOS
! 129 	if (child >= 0) 
! Debug: ge int = const 0 to int child = [S+$A-8] (used reg = )
mov	ax,-6[bp]
test	ax,ax
jl  	.2E
.2F:
! 130 		printf("status=%d\n",status);
! Debug: list int status = [S+$A-$A] (used reg = )
push	-8[bp]
! Debug: list * char = .30+0 (used reg = )
mov	bx,#.30
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*4
!BCC_EOS
! 131 }
.2E:
add	sp,*4
pop	si
pop	di
pop	bp
ret
! 132 int uexit()
! Register BX used in function uwait
! 133 # 132 "ucode.c"
! 132 {
export	_uexit
_uexit:
! 133 	char s[16];
!BCC_EOS
! 134 	int exitValue;
!BCC_EOS
! 135 	printf("enter exitValue : ");
push	bp
mov	bp,sp
push	di
push	si
add	sp,*-$12
! Debug: list * char = .31+0 (used reg = )
mov	bx,#.31
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 136 	exitValue = atoi(gets(s));
! Debug: list * char s = S+$18-$16 (used reg = )
lea	bx,-$14[bp]
push	bx
! Debug: func () int = gets+0 (used reg = )
call	_gets
inc	sp
inc	sp
! Debug: list int = ax+0 (used reg = )
push	ax
! Debug: func () int = atoi+0 (used reg = )
call	_atoi
inc	sp
inc	sp
! Debug: eq int = ax+0 to int exitValue = [S+$18-$18] (used reg = )
mov	-$16[bp],ax
!BCC_EOS
! 137 	exit(exitValue);
! Debug: list int exitValue = [S+$18-$18] (used reg = )
push	-$16[bp]
! Debug: func () int = exit+0 (used reg = )
call	_exit
inc	sp
inc	sp
!BCC_EOS
! 138 }
add	sp,*$12
pop	si
pop	di
pop	bp
ret
! 139 # 3 "u2.c"
! 3 extern void divide_zero_handler();
! Register BX used in function uexit
!BCC_EOS
! 4 # 16
! 16 int main()
! 17 # 16 "u2.c"
! 16 {
export	_main
_main:
! 17 	int i = 20, j = 0;
push	bp
mov	bp,sp
push	di
push	si
dec	sp
dec	sp
! Debug: eq int = const $14 to int i = [S+8-8] (used reg = )
mov	ax,*$14
mov	-6[bp],ax
dec	sp
dec	sp
! Debug: eq int = const 0 to int j = [S+$A-$A] (used reg = )
xor	ax,ax
mov	-8[bp],ax
!BCC_EOS
! 18 	install_handler(8,divide_zero_handler);
! Debug: cast * () void = const 0 to () void = divide_zero_handler+0 (used reg = )
! Debug: list * () void = divide_zero_handler+0 (used reg = )
mov	bx,#_divide_zero_handler
push	bx
! Debug: list int = const 8 (used reg = )
mov	ax,*8
push	ax
! Debug: func () int = install_handler+0 (used reg = )
call	_install_handler
add	sp,*4
!BCC_EOS
! 19 
! 20 	printf("Umode: going to divide zero\n");
! Debug: list * char = .32+0 (used reg = )
mov	bx,#.32
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 21 	i / j;
! Debug: div int j = [S+$A-$A] to int i = [S+$A-8] (used reg = )
mov	ax,-6[bp]
mov	bx,-8[bp]
cwd
idiv	bx
!BCC_EOS
! 22 	printf("Umode: line after divided zero, should not see me ;-)\n");
! Debug: list * char = .33+0 (used reg = )
mov	bx,#.33
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 23 	printf("Umode: i is %x and j is %x \n",i,j);
! Debug: list int j = [S+$A-$A] (used reg = )
push	-8[bp]
! Debug: list int i = [S+$C-8] (used reg = )
push	-6[bp]
! Debug: list * char = .34+0 (used reg = )
mov	bx,#.34
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
add	sp,*6
!BCC_EOS
! 24 	printf("Umode: U2 calling exit(0) byebye \n");
! Debug: list * char = .35+0 (used reg = )
mov	bx,#.35
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
! 25 
! 26 	exit(0);
! Debug: list int = const 0 (used reg = )
xor	ax,ax
push	ax
! Debug: func () int = exit+0 (used reg = )
call	_exit
inc	sp
inc	sp
!BCC_EOS
! 27 }
add	sp,*4
pop	si
pop	di
pop	bp
ret
! 28 
! Register BX used in function main
.data
.35:
.36:
.ascii	"Umode: U2 calling exit(0) byebye "
.byte	$A
.byte	0
.34:
.37:
.ascii	"Umode: i is %x and j is %x "
.byte	$A
.byte	0
.33:
.38:
.ascii	"Umode: line after divided zero, should n"
.ascii	"ot see me ;-)"
.byte	$A
.byte	0
.32:
.39:
.ascii	"Umode: going to divide zero"
.byte	$A
.byte	0
.31:
.3A:
.ascii	"enter exitValue : "
.byte	0
.30:
.3B:
.ascii	"status=%d"
.byte	$A
.byte	0
.2D:
.3C:
.ascii	"proc %d, dead child=%d"
.byte	$A
.byte	0
.2C:
.3D:
.ascii	"input new name : "
.byte	0
.2B:
.3E:
.ascii	"fault: %d"
.byte	$A
.byte	0
.29:
.3F:
.ascii	"%d forked %d"
.byte	$A
.byte	0
.26:
.40:
.ascii	"exec failed"
.byte	$A
.byte	0
.23:
.41:
.ascii	"new name: %s"
.byte	$A
.byte	0
.22:
.42:
.ascii	"enter exec filename : "
.byte	0
.21:
.43:
.ascii	"exec failed! now child process in troubl"
.ascii	"e"
.byte	$A
.byte	0
.20:
.44:
.ascii	"Input a file to exec, hurry: "
.byte	0
.1F:
.45:
.ascii	"exec now! before parent wake up"
.byte	$A
.byte	0
.1E:
.46:
.ascii	"vforked child %d in segment %x"
.byte	$A
.byte	0
.1C:
.47:
.ascii	"parent %d waited, dead child = %d"
.byte	$A
.byte	0
.1B:
.48:
.ascii	"vfork parent %d waits"
.byte	$A
.byte	0
.18:
.49:
.ascii	"in child, pid: %d"
.byte	$A
.byte	0
.16:
.4A:
.ascii	"in parent, pid: %d"
.byte	$A
.byte	0
.D:
.4B:
.ascii	"****************************************"
.ascii	"************"
.byte	$A
.byte	0
.C:
.4C:
.ascii	"* ps chname kfork switch wait exit fork "
.ascii	"exec vfork *"
.byte	$A
.byte	0
.B:
.4D:
.ascii	"********************** Menu ************"
.ascii	"************"
.byte	$A
.byte	0
.A:
.4E:
.ascii	"vfork"
.byte	0
.9:
.4F:
.ascii	"exec"
.byte	0
.8:
.50:
.ascii	"fork"
.byte	0
.7:
.51:
.ascii	"exit"
.byte	0
.6:
.52:
.ascii	"wait"
.byte	0
.5:
.53:
.ascii	"switch"
.byte	0
.4:
.54:
.ascii	"kfork"
.byte	0
.3:
.55:
.ascii	"chname"
.byte	0
.2:
.56:
.ascii	"ps"
.byte	0
.1:
.57:
.ascii	"getpid"
.byte	0
.bss

! 0 errors detected
