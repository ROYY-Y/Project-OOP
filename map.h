#ifndef OOP_MAP_H
#define OOP_MAP_H

#include "avltree.h"

namespace oop
{
    template <typename K, typename V>
    struct PairKeyCompare
    {
        bool operator()(const std::pair<K, V> &a, const std::pair<K, V> &b) const
        {
            return a.first < b.first; // เปรียบเทียบเฉพาะ key
        }
    };

    template <typename K, typename V>
    class Map : public AVLTree<std::pair<K, V>, PairKeyCompare<K, V>>
    {
    private:
        using NodeT = typename AVLTree<std::pair<K, V>, PairKeyCompare<K, V>>::NodeT;

    public:
        Map() : AVLTree<std::pair<K, V>, PairKeyCompare<K, V>>() {}

        void insert(const K &key, const V &value)
        {
            AVLTree<std::pair<K, V>, PairKeyCompare<K, V>>::insert({key, value});
        }

        bool contains(const K &key) const
        {
            return this->findNode({key, V()}) != nullptr;
        }

        V *get(const K &key)
        {
            NodeT *node = this->findNode({key, V()});
            if (!node)
                return nullptr;
            return &(node->data.second);
        }

        V &operator[](const K &key)
        {
            NodeT *node = this->findNode({key, V()});
            if (!node)
            {
                this->insert(key, V()); // ✅ ส่ง key กับ value แยกกัน
                node = this->findNode({key, V()});
            }
            return node->data.second;
        }
    };
}

#endif
