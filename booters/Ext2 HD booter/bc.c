// load ext2 file from hard disk with partitions
#include "ext2.h"
#define  GREEN  10         // color byte for putc()
#define  CYAN   11
#define  RED    12
#define  MAG    13
#define  YELLOW 14

#define  BLK    1024
char buf1[BLK],buf2[BLK],buf3[BLK],buf4[BLK];

struct partition {         // Partition table entry in MBR
       u8  drive;          // 0x80 - active 
       u8  head;	   // starting head 
       u8  sector;	   // starting sector 
       u8  cylinder;       // starting cylinder 
       u8  type;	   // partition type 
       u8  end_head;       // end head 
       u8  end_sector;	   // end sector 
       u8  end_cylinder;   // end cylinder 
       u32 start_sector;   // starting sector counting from 0 
       u32 nr_sectors;     // nr of sectors in partition 
};

struct dap{                // DAP for extended INT 13-42  
       u8   len;           // dap length=0x10 (16 bytes)
       u8   zero;          // must be 0  
       u16  nsector;       // number of sectors to read: 1 to 127
       u16  addr;          // memory address = (segment:addr)
       u16  segment;    
       u32  s1;            // low  4 bytes of sector#
       u32  s2;            // high 4 bytes of sector#
};

struct dap dap, *dp;       // global dap struct
u16 color = RED;           // initial color for putc()

#define  BOOTSEG 0x9000


char mbr[512];
char ans[64];
INODE *boot_inode, *mtx_inode;

u32 prtitns[4][2];

// load a disk sector to (DS, addr), where addr is an offset in segment
int getSector(u32 sector, char *addr)
{
  dp->nsector = 1;
  dp->addr    = addr;
  dp->s1      = (u32)sector;
  diskr();    // call int13-43 in assembly
}

int getblk(u32 sector, char *addr)
{
  dp->nsector = 2;
  dp->addr    = addr;
  dp->s1      = (u32)sector;
  diskr();
}

INODE* ino2inode(u32 ino, char *buf3){
  u32 inodes_per_group,desc_per_block,inodes_per_block,group,inumber,gdblk,gdisp,blk,disp;
  GD *gp;
  INODE *ip;
  inodes_per_group = 2048;
  desc_per_block = 32;
  inodes_per_block = 8;
  group = (ino-1)/inodes_per_group;
  inumber = (ino-1)%inodes_per_group;
  gdblk = group / desc_per_block;
  gdisp = group % desc_per_block;
  blk = inumber / inodes_per_block;
  disp = inumber % inodes_per_block;
  getblk(prtitns[0][0] + 4 + gdblk*2, buf3);
  gp = (GD *)buf3 + gdisp;
  blk += gp->bg_inode_table;
  getblk(prtitns[0][0] + blk*2, buf3);
  ip = (INODE *)buf3 + disp;
  return ip;
}

int show_inode_dirs(INODE *ip){
        int i; char c; DIR *dp;
        u32 boot_inode_number;
        for(i=0; i<12; i++){
                if((u16)ip->i_block[i]){
			printf("enter if\n\r");
                        getblk(prtitns[0][0] + (ip->i_block[i]*2), buf2);
                        dp = (DIR *)buf2;
                        while ((char*)dp < &buf2[BLK]){
                                c = dp->name[dp->name_len];
                                dp->name[dp->name_len] = 0;
                                printf("%s\n\r",dp->name);
                                if (strcmp(dp->name,"boot") == 0){
					printf("found boot.\n\r");
                                        boot_inode_number = dp->inode;
                                        boot_inode = ino2inode(boot_inode_number,buf3);
                                }
				if (strcmp(dp->name,"hdmtx") == 0){
					printf("found mtx.\n\r");
                                        boot_inode_number = dp->inode;
                                        mtx_inode = ino2inode(boot_inode_number,buf4);
                                }
                                dp->name[dp->name_len] = c;
                                dp = (char *)dp + dp->rec_len;
                        }
                }
        }
}

int main()
{
  int i;
  struct partition *p;
  char sprblk[1024];

  u32 ino,iblk;
  INODE *ip;
  GD *gp;
  SB *sb;
  u32 *up;
  u16 dp_addr;

  printf("booter start in main()\n");
  // initialize the dap struct
  dp = &dap;
  dp->len  = 0x10;        // must be 16
  dp->zero = 0;           // must be 0
  dp->nsector = 1;        // load one sector
  dp->addr = 0;           // will set to addr              
  dp->segment = BOOTSEG;  // load to which segment
  dp->s1 = 0;             // will set to LBA sector#
  dp->s2 = 0;             // high 4-byte address s2=0

  getSector((u32)0, (u16)mbr); // get MBR
  p = (u8 *)mbr + 0x1BE;
  printf("d  h  s  c  t   ");
  printf("e_h  e_s e_c s_sec nr_sec");
  printf("%s","\n\r");
  for (i=0;i<4;i++){
	prtitns[i][0] = p->start_sector;
	prtitns[i][1] = p->nr_sectors;
  	printf("%u %u %u %u %u",p->drive,p->head,p->sector,p->cylinder,p->type);
  	printf("%u %u %u  %l %l",p->end_head,p->end_sector,p->end_cylinder,p->start_sector,p->nr_sectors);
	printf("%s","\n\r");
	p++;
  }
  getSector(prtitns[0][0]+2,sprblk);
  sb = (SB *)sprblk;
  getblk(prtitns[0][0] + 4, buf1);
  gp = (GD *)buf1;
  iblk=gp->bg_inode_table;
  getblk(prtitns[0][0] + (iblk<<1), buf1);
  ip = (INODE *)buf1 + 1;
  show_inode_dirs(ip); 
  show_inode_dirs(boot_inode);
  if(mtx_inode->i_block[13])
	printf("there's i_block[13]");
  if(mtx_inode->i_block[12]){
        getblk(prtitns[0][0] + (mtx_inode->i_block[12]<<1), buf2);
  }
  dp->segment = 0x1000;
  dp_addr = 0;
  for (i=0;i<12;i++){
        getblk(prtitns[0][0] + (mtx_inode->i_block[i]<<1),0);
        dp->segment += 0x40;
	putc('*');
  }
  if (mtx_inode->i_block[12]){
        up = (u32 *)buf2;
        while(*up){
                getblk(prtitns[0][0] + ((*up)<<1),0);
                dp->segment += 0x40;
		up++;
		putc('.');
        }
  }
  prints("ready?");getc();
}
