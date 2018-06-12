#include "signal.h"

extern void idiv();

int check_sig() {
	int i;
	for (i=1; i<NSIG; i++) {
		if (running->signal & (1 << i)) {
			printf("check_sig: got signal %d\n", i);
			running->signal &= ~(1 << i);
			return i;
		}
	}
//	printf("check_sig: got no signal, return 0\n");
	return 0;
}

int psig() {
	int n, *us;
	u16 uSEG, uSP, uPC;
//	printf("psig: starting...\n");
	while(n = check_sig()) {
		running->signal &= ~(1 << n);
		if (running->sig[n] == 1){
			printf("psig: ignoring sig %d, continue\n", n);
			continue;
		}
		if (running->sig[n] == 0) {
			printf("psig: sig %d handler is 0, calling kexit byebye...\n", n);
			kexit(n<<8);
		}

		// change the return Ustack		
		uSEG = running->uss;
		uSP = running->usp;	
		uPC = get_word(uSEG, uSP + 2*9);
		
		printf("psig: -==--!!!! uPC is %x!!!!--==-\n", uPC);
		printf("psig: and the byte code in addr %x is %x\n", uPC, get_word(uSEG,uPC));
		printf("psig: the idiv command in hex is %x\n", *(u16 *)idiv);
//		printf("psig: and the byte code in addr before is %x\n", get_byte(uSEG, uPC - 1));
		
		printf("+++++ psig: write 9 to addr %x\n", uSP + 2*13);
		put_word(n, uSEG, uSP + 2*13);
		put_word(get_word(uSEG, uSP + 2*9), uSEG, uSP + 2*12);
		put_word(running->sig[n], uSEG, uSP + 2*9);
	}
//	printf("psig: exiting, goUmode next...\n");
	return 0;
}

int kdivide() {
	printf("kdivde: divide-by-zero triggered int0...\n");
	running->signal |= (1 << 9);
//	printf("kdvide: byebye...\n");
}



