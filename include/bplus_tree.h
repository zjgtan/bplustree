#ifndef _BPLUS_TREE_H_
#define _BPLUS_TREE_H_

#include <vector>

#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(Meta)
#define BP_ORDER 20

struct Meta {
    size_t order; //B+���Ľ�, һ���ڵ��������ĺ�����
    size_t value_size; // value�Ĵ洢�ռ��С
    size_t key_size; // key�Ĵ洢�ռ��С
    size_t internal_node_num; // �ڽڵ�����
    size_t leaf_node_num; //Ҷ�ӽڵ�����
    size_t height; // ���ĸ߶�
    off_t slot;
    off_t root_offset; // ���ڵ��ƫ����
    off_t leaf_offset; //��һ��Ҷ�ڵ��ƫ����
};

template <typename K>
struct Index {
    K key;
    off_t child;
};

// �ڽڵ�
template <typename K>
struct InternalNode {
    off_t parent; // ���ڵ�
    off_t next; // ���ֵ�
    off_t prev; // ���ֵ�
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
    char _path[512]; // �����ļ�·��
    Meta _meta; // B+����Ԫ��Ϣ
    FILE *_fp; // �ļ�ָ��
    int _fp_level;


public:
    // ���캯��
    BPlusTree(const char *p, bool force_empty);
    // ����
    int find(int key);
    // ����
    int insert(int key, int value);
    // ɾ��
    bool del(int key);
    // ����
    bool set(int key, int value);


private:
    int _init_from_empty();

    // �Ӵ����ļ��ж���
    int _map(void *block, off_t offset, size_t size);
    // д������ļ�
    int _unmap(void *block, off_t offset, size_t size);
    // ���ļ�
    int _open();
    // �ر��ļ�
    int _close();
    // ���ļ��з���ռ�
    off_t _alloc(size_t size);
    off_t _alloc(LeafNode<K, V> *leaf);
    off_t _alloc(InternalNode *node);
};

#endif
