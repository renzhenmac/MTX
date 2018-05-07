#include "ext2.h"
#define BLK 1024

u16 NSEC = 2;
char buf0[BLK],buf2[BLK],buf3[BLK];
u16 iblk;

int prints(char *s){
	while(*s) putc(*s++);
}

int gets(char *s){
   while((*s = getc()) != '\r'){
	putc(*s++);
   }
   *s = 0; 
}

int getblk(u16 blk, char *buf){
   readfd(blk/18, ((2*blk)%36)/18, ((2*blk)%36)%18, buf);
}

INODE* search_dir(INODE *ip, char *name){
	int i; char c; DIR *dp;
	u16 found_inode_num;
	for(i=0; i<12; i++){
		if((u16)ip->i_block[i]){
			getblk((u16)ip->i_block[i], buf0);
			dp = (DIR *)buf0;
			while ((char*)dp < &buf0[BLK]){
				c = dp->name[dp->name_len];
				dp->name[dp->name_len] = 0;
				prints(dp->name);
				prints("\n\r");
				if (strcmp(dp->name,name) == 0){
					prints("found ");prints(dp->name);prints("\n\r");
					found_inode_num = (u16)dp->inode - 1;
					getblk(iblk+(found_inode_num/8),buf3);
					return((INODE *)buf3 + (found_inode_num%8));
				}	
				dp->name[dp->name_len] = c;
				dp = (char *)dp + dp->rec_len;
			}
		}
	}
}


main()
{
	char *name = "mtx";
	u16 ino,i,blk;
	u32 *up;
	INODE *root_inode, *boot_dir_inode, *mtx_inode;
	GD *gp;
	DIR *dp;
	getblk(2, buf0);
	gp = (GD *)buf0;
	iblk = (u16)gp->bg_inode_table;
	getblk(iblk, buf0);
	root_inode = (INODE *)buf0 + 1;
	boot_dir_inode = search_dir(root_inode,"boot");
	mtx_inode = search_dir(boot_dir_inode,"mtx");
	if((u16)mtx_inode->i_block[12]){
		getblk((u16)mtx_inode->i_block[12], buf2);
	}
	setes(0x1000);
	for (i=0;i<12;i++){
		getblk((u16)mtx_inode->i_block[i],0);
		inces();putc('*');
	}
	if ((u16)mtx_inode->i_block[12]){
		up = (u32 *)buf2;
		while(*up){
			getblk((u16)*up, 0);
			inces();putc('.');
			up++;
		}
	}
	prints("ready?");getc();
}
