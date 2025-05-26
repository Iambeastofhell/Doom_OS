#include "filesystem.h"

void fs_init(){
    struct superblock *sb = (struct superblock*) SUPERBLOCK_ADD;
    struct inode *in  = (struct inode*)ITABLE_ADD;
    char *blocks = (char *)BLOCK_ADD;
    if (sb->num_blocks!=INODE_NUM){
        sb->num_nodes = INODE_NUM;
        sb->num_blocks = BLOCK_NUM;
        sb->block_start = BLOCK_ADD;
        sb->inode_start = ITABLE_ADD;
        for (int i = 0; i < INODE_NUM; i++){
            in[i].used = 0;
        }
        
    }
    
}