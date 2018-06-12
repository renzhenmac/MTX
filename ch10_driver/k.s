	.globl _tswitch,_int80h,_tinth,_goUmode,_getds,_setds,_lock,_unlock,_in_byte,_out_byte,_divide,_getc,_putc,_idiv
    .globl _main,_running,_scheduler,_proc,_procSize,_kcinth,_thandler,_kdivide,_psig   ! IMPORT these

	jmpi start,0x1000

start:
        mov  ax,cs
        mov  ds,ax
        mov  ss,ax
        mov  es,ax
        mov  sp,#_proc
        add  sp,_procSize
        mov  ax,#0x0003     ! these will start in MONO display mode
        int  #0x10          ! needed by vid driver later
        call _main

_tswitch:
SAVE:
		cli
        push ax
        push bx
        push cx
        push dx
        push bp
        push si
        push di
        pushf
        mov  bx,_running
        mov  2[bx],sp
FIND:   call _scheduler
RESUME:
        mov  bx,_running
        mov  sp,2[bx]
        popf
        pop  di
        pop  si
        pop  bp
        pop  dx
        pop  cx
        pop  bx
        pop  ax
		sti
        ret

_lock:
		cli
		ret
_unlock:
		sti
		ret
		
		
USS = 4
USP = 6
INK = 8

! as86 macro: parameters are ?1 ?2, etc 
! as86 -m -l listing src (generates listing with macro expansion)

MACRO INTH
        push ax
        push bx
        push cx
        push dx
        push bp
        push si
        push di
        push es
        push ds
! ustack contains: |uflag,uCS,uPC|ax,bx,cx,dx,bp,si,di,ues,uds|
! 						           usp
! change DS to KDS in order to access data in Kernel space
		mov ax,cs 		! assume one-segment kernel, change DS to kDS
		mov ds,ax 		! let DS=CS = 0x1000 = kernel DS
		mov bx,_running   	! ready to access proc
        inc INK[bx]
        cmp INK[bx],#1
        jg   ?1

! was in Umode: save interrupted (SS,SP) into proc
        mov USS[bx],ss        ! save SS  in proc.USS
        mov USP[bx],sp        ! save SP  in proc.USP
		
! change ES,SS to Kernel segment 0x1000
		mov ax,ds 		! CPU must mov segments this way!
		mov es,ax
		mov ss,ax 		! SS is now KSS = 0x1000
! switch running proc stack from U space to K space.
		mov sp,bx 		! sp points at running PROC
		add sp,_procSize 	! sp -> HIGH END of running kstack

?1:     call  _?1             ! call handler in C
        br    _ireturn        ! return to interrupted point
MEND


_int80h: INTH kcinth
_tinth:  INTH thandler
_divide: INTH kdivide

!*===========================================================================*
!*		_ireturn  and  goUmode()       				     *
!*===========================================================================*
! ustack contains    flag,ucs,upc, ax,bx,cx,dx,bp,si,di,es,ds
! uSS and uSP are in proc

_ireturn:
		call _psig
!		test ax,ax
!		je _goUmode
	
_goUmode:
		cli
		mov bx,_running 	! bx points at running PROC
		dec INK[bx] 		! dec proc.inkmode by 1
		cmp INK[bx],#0 		! inkmode==0 means proc was in Umode
		jg xkmode 			! by pass return to Umode code
! return to Umode: restore uSS, uSP from running PROC.(uss,usp)
		mov ax,USS[bx]
		mov ss,ax 			! restore SS
		mov sp,USP[bx] 		! restore SP
xkmode: 
		pop ds
		pop es
		pop di
		pop si
		pop bp
		pop dx
		pop cx
		pop bx
		pop ax
		iret
		
_getds:
		push bp
		mov ax,ds
		pop bp
		ret
	
_setds:
		push bp			
		mov  bp,sp		
		mov  ds,4[bp]		! load ds with segment value
		pop  bp
		ret

_in_byte:
        push    bp
        mov     bp,sp
        mov     dx,4[bp]
		in      ax,dx			! input 1 byte
		subb	ah,ah			! unsign extend
        pop     bp
        ret

_out_byte:
        push    bp
        mov     bp,sp
        mov     dx,4[bp]
        mov     ax,6[bp]
		outb	dx,al		! output 1 byte
        pop     bp
        ret

_getc:
        xorb   ah,ah           ! clear ah
        int    0x16            ! call BIOS to get a char in AX
        ret 
_putc:           
        push   bp
		mov    bp,sp
	
        movb   al,4[bp]        ! get the char into aL
        movb   ah,#14          ! aH = 14
        movb   bl,#0x0A        ! bL = color 
        int    0x10            ! call BIOS to display the char

        pop    bp
		ret
		
_idiv:
		idiv bx
		ret

