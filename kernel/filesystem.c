#include "filesystem.h"
#include "string.h"
#include "standio.h"  

#define block_bitmap ((char*)BITMAP_ADD)

void fs_init(){
    struct superblock *sb = (struct superblock*)SUPERBLOCK_ADD;
    
    if (sb->num_nodes != INODE_NUM){
        sb->num_nodes = INODE_NUM;
        sb->num_blocks = BLOCK_NUM;
        sb->inode_start = ITABLE_ADD;
        sb->block_start = BITMAP_ADD;
        sb->data_start = BLOCK_ADD;

        // Initialize inodes
        struct inode *in = (struct inode*)ITABLE_ADD;
        for (int i = 0; i < INODE_NUM; i++){
            in[i].used = 0;
        }

        // Initialize block bitmap (persistent)
        for (int i = 0; i < BLOCK_NUM; i++){
            block_bitmap[i] = 0;
        }
        vga_printf("Filesystem initialized\n");
    }
}

int new_block(){
    for (int i = 0; i < BLOCK_NUM; i++){
        if(block_bitmap[i] == 0) {
            block_bitmap[i] = 1;
            return i;
        }
    }
    return -1;
}

int fs_write(char *name, char *buf, int len){
    struct inode *in = (struct inode*)ITABLE_ADD;
    char *blocks = (char *)BLOCK_ADD;

    for (int i = 0; i < INODE_NUM; i++) {
        if (in[i].used && strcmp(in[i].name, name) == 0) {
            int written = 0;
            int blocks_used = 0;

            while (written < len && blocks_used < 10) {
                int blk = new_block();
                if (blk == -1) return written;
                
                in[i].block_add[blocks_used] = blk;
                int to_write = (len - written > BLOCK_SIZE) 
                    ? BLOCK_SIZE : (len - written);
                
                memcpy(blocks + blk * BLOCK_SIZE, 
                       buf + written, 
                       to_write);
                written += to_write;
                blocks_used++;
            }
            in[i].size = written;
            return written;
        }
    }
    for (int i = 0; i < INODE_NUM; i++) {
        if (!in[i].used) {
            in[i].used = 1;
            strcpy(in[i].name, name); 
            in[i].name[15] = '\0';         
            
            int written = 0;
            int blocks_used = 0;

            while (written < len && blocks_used < 10) {
                int blk = new_block();
                if (blk == -1) break;
                in[i].block_add[blocks_used] = blk;
                int to_write = (len - written > BLOCK_SIZE) ? BLOCK_SIZE : (len - written);
                memcpy(blocks + blk * BLOCK_SIZE,buf + written,to_write);
                written += to_write;
                blocks_used++;
            }
            in[i].size = written;
            return written;
        }
    }
    vga_printf("return with error\n");
    return -1;  
}

int fs_read(char *name, char *buffer) {
    struct inode *in = (struct inode*)ITABLE_ADD;
    char *blocks = (char *)BLOCK_ADD;
    print_int(strcmp(in[1].name, name));
    vga_printf("\n");
    for (int i = 0; i < INODE_NUM; i++) {
        if (in[i].used && strcmp(in[i].name, name) == 0) {
            int total = in[i].size;
            int read = 0;
            for (int j = 0; j < 10 && read < total; j++){
                int blk = in[i].block_add[j];
                int to_read = (total - read > BLOCK_SIZE)? BLOCK_SIZE : (total - read);
                memcpy(buffer + read,blocks + blk * BLOCK_SIZE,to_read);
                read += to_read;
            }
            return read;
        }
    }
    return -1;  
}