#ifndef EXT2_H
#define EXT2_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

struct ext2_inode {
	u16	i_mode;		/* File mode */
	u16	i_uid;		/* Owner Uid */
	u32	i_size;		/* Size in bytes */
	u32	i_atime;	/* Access time */
	u32	i_ctime;	/* Creation time */
	u32	i_mtime;	/* Modification time */
	u32	i_dtime;	/* Deletion Time */
	u16	i_gid;		/* Group Id */
	u16	i_links_count;	/* Links count */
	u32	i_blocks;	/* Blocks count */
	u32	i_flags;	/* File flags */
	u32     dummy;
	u32	i_block[15];    /* Pointers to blocks */
   	u32     pad[7];         /* inode size MUST be 128 bytes */
};

struct ext2_group_desc
{
	u32	bg_block_bitmap;		/* Blocks bitmap block */
	u32	bg_inode_bitmap;		/* Inodes bitmap block */
	u32	bg_inode_table;		/* Inodes table block */
	u16	bg_free_blocks_count;	/* Free blocks count */
	u16	bg_free_inodes_count;	/* Free inodes count */
	u16	bg_used_dirs_count;	/* Directories count */
	u16	bg_pad;
	u32	bg_reserved[3];
};

struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
};

struct ext2_super_block_start {
	u32 s_inodes_count; // total number of inodes
	u32 s_blocks_count; // total number of blocks
	u32 s_r_blocks_count;
	u32 s_free_blocks_count; // current number of free blocks
	u32 s_free_inodes_count; // current number of free inodes
	u32 s_first_data_block; // first data block: 1 for FD, 0 for HD
	u32 s_log_block_size; // 0 for 1KB block, 2 for 4KB block
	u32 s_log_frag_size; // not used
	u32 s_blocks_per_group; // number of blocks per group
	u32 s_frags_per_group; // not used
	u32 s_inodes_per_group;
	u32 s_mtime, s_wtime;
	u16 s_mnt_count; // number of times mounted
	u16 s_max_mnt_count; // mount limit
	u16 s_magic; // 0xEF53
	// MORE non-essential fileds,
};

typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;
typedef struct ext2_super_block_start SB;

#endif
