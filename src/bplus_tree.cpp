#include "bplus_tree.h"

#include <string.h>

BPlusTree::BPlusTree(const char *p, bool force_empty)
    : fp(NULL), fp_level(0) {
    
    bzero(path, sizeof(path));
    strcpy(path, p);

    if (!force_empty) {
        // 从文件中构建B+树
        if ()

    } else {
        // 构建一颗空树
    }
}

int BPlusTree::_open(const char *mode = "rb+") {
    if (_fp_level != 0) {
        return -1;
    } 

    _fp = fopen(_path, mode);
    _fp_level++;

    return 0
}

void BPlusTree::_close() {
    if (_fp_level == 1) {
        fclose(_fp);
    } 
    --_fp_level;
}

int BPlusTree::_map(void *block, off_t offset, size_t size) {
    _open();
    fseek(_fp, offset, SEEK_SET);
    size_t num = fread(block, size, 1, _fp);
    _close();
    return num - 1;
}
