#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define FS_START 0x200000       // Use 2MB to avoid kernel overlap
#define INODE_NUM 64
#define BLOCK_NUM 512
#define BLOCK_SIZE 512
#define MAGIC 0xDEADBEEF        // For superblock validation

struct superblock{
    int num_nodes;
    int num_blocks;
    int inode_start;
    int block_start;
    int data_start;
};

struct inode{
    char name[16];
    int size;
    int used;
    int block_add[10];
};

// Calculate addresses relative to FS_START
#define SUPERBLOCK_ADD (FS_START)
#define BITMAP_ADD    (FS_START + sizeof(struct superblock))
#define ITABLE_ADD    (FS_START + sizeof(struct superblock) + 64) 
#define BLOCK_ADD     (FS_START + 1024) 

void fs_init();
int new_block();
int fs_read(char *name, char *buffer);
int fs_write(char *name, char *buf, int len);
char **fs_list();

#endif