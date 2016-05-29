#ifndef _BPLUS_TREE_H_
#define _BPLUS_TREE_H_

#include <vector>

#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(Meta)
#define BP_ORDER 20

struct Meta {
    size_t order; //B+树的阶, 一个节点所包含的孩子数
    size_t value_size; // value的存储空间大小
    size_t key_size; // key的存储空间大小
    size_t internal_node_num; // 内节点数量
    size_t leaf_node_num; //叶子节点数量
    size_t height; // 树的高度
    off_t slot;
    off_t root_offset; // 根节点的偏移量
    off_t leaf_offset; //第一个叶节点的偏移量
};

template <typename K>
struct Index {
    K key;
    off_t child;
};

// 内节点
template <typename K>
struct InternalNode {
    off_t parent; // 父节点
    off_t next; // 右兄弟
    off_t prev; // 左兄弟
    size_t n;
    Index<K> children[BP_ORDER];
};


template <typename K, typename V>
struct Record {
    K key;
    V value;
};

template <typename K, typename V>
struct LeafNode {
    off_t parent;
    off_t next;
    off_t prev;
    Record<K, V> children[BP_ORDER];
};


template <typename K, typename V>
class BPlusTree {
private:
    char _path[512]; // 索引文件路径
    Meta _meta; // B+树的元信息
    FILE *_fp; // 文件指针
    int _fp_level;


public:
    // 构造函数
    BPlusTree(const char *p, bool force_empty);
    // 查找
    int find(int key);
    // 插入
    int insert(int key, int value);
    // 删除
    bool del(int key);
    // 改正
    bool set(int key, int value);


private:
    int _init_from_empty();

    // 从磁盘文件中读入
    int _map(void *block, off_t offset, size_t size);
    // 写入磁盘文件
    int _unmap(void *block, off_t offset, size_t size);
    // 打开文件
    int _open();
    // 关闭文件
    int _close();
    // 在文件中分配空间
    off_t _alloc(size_t size);
    off_t _alloc(LeafNode<K, V> *leaf);
    off_t _alloc(InternalNode *node);
};

#endif
