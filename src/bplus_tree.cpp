#include "bplus_tree.h"

#include <string.h>

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(const char *p, bool force_empty)
    : fp(NULL), fp_level(0) {
    
    bzero(path, sizeof(path));
    strcpy(path, p);

    if (!force_empty) {
        // 从文件中构建B+树
        if (_map((void *)&_meta, OFFSET_META) != 0) {
            // 读取meta信息失败
            return;
        }

    } else {
        // 构建一颗空树
        _open("w+");
        _init_from_empty();
        _close();
    }
}

template <typename K, typename V>
int BPlusTree<K, V>::_init_from_empty() {
    bzero(&_meta, sizeof(Meta));
    _meta.order = BP_ORDER;
    _meta.value_size = sizeof(V);
    _meta.key_size = sizeof(K);
    _meta.height = 1;
    _meta.slot = OFFSET_BLOCK;

    InternalNode root;
    root.next = root.prev = root.parent = 0;
    _meta.root_offset = _alloc((void *)&root);

    LeafNode leaf;
    leaf.next = leaf.prev = 0;
    leaf.parent = _meta.root_offset;
    _meta.leaf_offset = root.children[0].child = _alloc((void *)&leaf);

    return 0;
}

template <typename K, typename V>
int BPlusTree<K, V>::_open(const char *mode = "rb+") {
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

template <typename K, typename V>
off_t BPlusTree<K, V>::_alloc(size_t size) {
    
}

template <typename K, typename V>
off_t BPlusTree<K, V>::_alloc(LeafNode<K, V> *leaf) {
    
}

template <typename K, typename V>
off_t BPlusTree<K, V>::_alloc(InternalNode<K> *node) {
    
}
