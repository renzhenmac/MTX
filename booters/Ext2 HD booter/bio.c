#define MAXLEN 128
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

char *gets(char s[ ]) // caller must provide REAL memory s[MAXLEN]
{
	char c, *t = s; int len=0;
	while((c=getc()) != '\r' && len < MAXLEN-1){
		*t++ = c; putc(c); len++;
	}
	*t = 0; return s;
}

char *ctable = "0123456789ABCDEF";
u16 BASE = 10; // for decimal numbers
u32 BASE32 = 10;
int rpu(u16 x){
	char c;
	if (x){
		c = ctable[x % BASE];
		rpu(x / BASE);
		putc(c);
	}
}

int rpu32(u32 x){
        char c;
        if (x){
                c = ctable[x % BASE32];
                rpu32(x / BASE32);
                putc(c);
        }
}


int printu(u16 x){
	BASE = 10;
	(x==0)?putc('0'):rpu(x);
	putc(' ');
}

int printd(u16 x){
	BASE = 10;
	(x==0)?putc('0'):rpu(x);
	putc(' ');
}

int prints(u16 x){
	char *c = (char *)x;
	while(*c){
		putc(*c);
		c++; 
	}
}

int printx(u16 x){
	BASE = 16;
	(x==0)?putc('0'):rpu(x);
	putc(' ');

}

int printl(u32 x){
	BASE32 = 10;
	(x==0)?putc('0'):rpu32(x);
	putc(' ');
}

int printX(u32 x){
        BASE32 = 16;
        (x==0)?putc('0'):rpu32(x);
        putc(' ');
}


int printf(char *fmt, ...) // some C compiler requires the three dots
{
	char *cp = fmt; // cp points to the fmt string
	u16 *ip = (u16 *)&fmt + 1; // ip points to first item
	u32 *up; // for accessing long parameters on stack
	while (*cp){ // scan the format string
		if (*cp != '%'){ // spit out ordinary chars
			putc(*cp);
			if (*cp=='\n') // for each ‘\n’
				putc('\r'); // print a ‘\r’
			cp++; continue;
		}
		cp++; // print item by %FORMAT symbol
		switch(*cp){
			case 'c' : putc(*ip); break;
			case 's' : prints(*ip); break;
			case 'u' : printu(*ip); break;
			case 'd' : printd(*ip); break;
			case 'x' : printx(*ip); break;
			case 'l' : 
				up = (u32 *)ip;
				printl(*up);
				ip++;
				break;
			case 'X' :
				up = (u32 *)ip;
				printX(*up);
				ip++;
				break;
		}
		cp++; ip++; // advance pointers
	}
}
