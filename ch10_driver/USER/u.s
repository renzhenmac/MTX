        .globl _main,_syscall,_exit
        .globl _getss,_getbp,_getcs,_getbx,_setbx,_getc,_geti,_getj,_divide_zero_handler
		
        call _main
	
! if ever return, exit(0)
	push  #0
	call  _exit

_getss:
        mov   ax, ss
        ret
		
_getcs:
        mov   ax, cs
        ret

_syscall:
        int    80
        ret
		
_getbx:
		mov   ax, bx
		ret
		
_getbp:
		mov		ax,bp
		ret
_geti:
		mov	ax,-6[bp]
		ret

_getj:
		mov	bx,-8[bp]
		ret
		
_setbx:
		push bp			
		mov  bp,sp		
		mov  bx,4[bp]
		pop  bp
		ret
		
_getc:
        xorb   ah,ah           ! clear ah
        int    0x16            ! call BIOS to get a char in AX
        ret 
		
_divide_zero_handler:
		push	bp
		mov 	bp,sp
		mov		bx,2[bp]
		add		bx,#2
		mov		2[bp],bx
		pop		bp
		ret
