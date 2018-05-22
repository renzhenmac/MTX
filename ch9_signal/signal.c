#include "signal.h"

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
	u16 uSEG, uSP;
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
		put_word(n, uSEG, uSP + 2*13);
		put_word(get_word(uSEG, uSP + 2*9), uSEG, uSP + 2*12);
		put_word(running->sig[n], uSEG, uSP + 2*9);
	}
//	printf("psig: exiting...\n");
	return 0;
}

int kdivide() {
	printf("kdivde: seems divide-by-zero happened...\n");
	running->signal |= (1 << SIGFPE);
	printf("kdvide: byebye...\n");
}



