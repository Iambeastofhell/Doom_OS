#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define FS_START 0X100000
#define INODE_NUM 64
#define BLOCK_NUM 512
#define BLOCK_SIZE 512


struct superblock{
    int num_nodes;
    int num_blocks;
    int inode_start;
    int block_start;
};

struct inode{
    char name[16];
    int size;
    int used;
    int block_add;
};

#define SUPERBLOCK_ADD FS_START
#define ITABLE_ADD (SUPERBLOCK_ADD+512)
#define BLOCK_ADD (ITABLE_ADD +sizeof(struct inode)*INODE_NUM)

#endif