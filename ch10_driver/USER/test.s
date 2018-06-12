! 1 
! 1 # 1 "test.c"
! 1 void divide_zero_handler(i)
! 2 # 1 "test.c"
! 1 int i;
export	_divide_zero_handler
_divide_zero_handler:
!BCC_EOS
! 2 # 1 "test.c"
! 1 {
! 2 	printf("Umode handler: yo\n");}
push	bp
mov	bp,sp
push	di
push	si
! Debug: list * char = .1+0 (used reg = )
mov	bx,#.1
push	bx
! Debug: func () int = printf+0 (used reg = )
call	_printf
inc	sp
inc	sp
!BCC_EOS
pop	si
pop	di
pop	bp
ret
! 3 
! Register BX used in function divide_zero_handler
.data
.1:
.2:
.ascii	"Umode handler: yo"
.byte	$A
.byte	0
.bss

! 0 errors detected
