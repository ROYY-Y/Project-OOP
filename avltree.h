#ifndef OOP_AVLTREE_H
#define OOP_AVLTREE_H

#include <bits/stdc++.h>
#include "binarytree.h"

namespace oop
{
    template <typename T, typename Compare = std::less<T>>
    class AVLTree : public oop::BinaryTree<T>
    {
    public:
        Compare cmp;
        size_t sz = 0;

        AVLTree() : BinaryTree<T>(), cmp(Compare()), sz(0) {}
        ~AVLTree() override = default;

        template <typename K, typename V>
        struct PairKeyCompare
        {
            bool operator()(const std::pair<K, V> &a, const std::pair<K, V> &b) const
            {
                return a.first < b.first;
            }
        };

        bool insert(const T &value) override
        {
            bool inserted = false;
            this->root = insertRec(this->root, value, inserted);
            if (inserted)
                ++sz;
            return inserted;
        }

        bool remove(const T &value) override
        {
            bool removed = false;
            this->root = removeRec(this->root, value, removed);
            if (removed)
                --sz;
            return removed;
        }

        bool contains(const T &value) const override
        {
            return containsRec(this->root, value);
        }

        int height() const { return nodeHeight(this->root); }
        size_t size() const { return sz; }
        bool empty() const { return sz == 0; }

        T *find(const T &value)
        {
            NodeT *result = findRec(this->root, value);
            return result ? &result->data : nullptr;
        }

    protected:
        using NodeT = Node<T>;

        int nodeHeight(NodeT *n) const { return n ? n->height : 0; }
        int getBalance(NodeT *n) const
        {
            if (!n)
                return 0;
            return nodeHeight(n->left) - nodeHeight(n->right);
        }

        NodeT *findNode(const T &value) const
        {
            return findRec(this->root, value);
        }

        NodeT *findRec(NodeT *node, const T &key) const
        {
            if (!node)
                return nullptr;

            if (cmp(key, node->data))
                return findRec(node->left, key);
            else if (cmp(node->data, key))
                return findRec(node->right, key);
            else
                return node; // equal
        }

        NodeT *rightRotate(NodeT *y)
        {
            NodeT *x = y->left;
            NodeT *T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
            x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;

            return x;
        }

        NodeT *leftRotate(NodeT *x)
        {
            NodeT *y = x->right;
            NodeT *T2 = y->left;

            y->left = x;
            x->right = T2;

            x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
            y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

            return y;
        }

        NodeT *insertRec(NodeT *node, const T &key, bool &inserted)
        {
            if (!node)
            {
                inserted = true;
                return new NodeT(key);
            }

            if (cmp(key, node->data))
            {
                node->left = insertRec(node->left, key, inserted);
            }
            else if (cmp(node->data, key))
            {
                node->right = insertRec(node->right, key, inserted);
            }
            else
            {
                // equal -> do not insert duplicate
                inserted = false;
                return node;
            }

            node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
            int balance = getBalance(node);

            // LL
            if (balance > 1 && cmp(key, node->left->data))
                return rightRotate(node);
            // RR
            if (balance < -1 && cmp(node->right->data, key))
                return leftRotate(node);
            // LR
            if (balance > 1 && cmp(node->left->data, key))
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            // RL
            if (balance < -1 && cmp(key, node->right->data))
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        NodeT *minValueNode(NodeT *n)
        {
            NodeT *cur = n;
            while (cur->left)
                cur = cur->left;
            return cur;
        }

        NodeT *removeRec(NodeT *rootNode, const T &key, bool &removed)
        {
            if (!rootNode)
                return rootNode;

            if (cmp(key, rootNode->data))
            {
                rootNode->left = removeRec(rootNode->left, key, removed);
            }
            else if (cmp(rootNode->data, key))
            {
                rootNode->right = removeRec(rootNode->right, key, removed);
            }
            else
            {
                // found node to be deleted
                removed = true;
                if (!rootNode->left || !rootNode->right)
                {
                    NodeT *temp = rootNode->left ? rootNode->left : rootNode->right;
                    if (!temp)
                    {
                        temp = rootNode;
                        rootNode = nullptr;
                    }
                    else
                    {
                        *rootNode = *temp; // copy contents
                    }
                    delete temp;
                }
                else
                {
                    NodeT *temp = minValueNode(rootNode->right);
                    rootNode->data = temp->data;
                    rootNode->right = removeRec(rootNode->right, temp->data, removed);
                    // Note: removed was set by recursive call; we want true
                    removed = true;
                }
            }

            if (!rootNode)
                return rootNode;

            rootNode->height = 1 + max(nodeHeight(rootNode->left), nodeHeight(rootNode->right));
            int balance = getBalance(rootNode);

            // LL
            if (balance > 1 && getBalance(rootNode->left) >= 0)
                return rightRotate(rootNode);
            // LR
            if (balance > 1 && getBalance(rootNode->left) < 0)
            {
                rootNode->left = leftRotate(rootNode->left);
                return rightRotate(rootNode);
            }
            // RR
            if (balance < -1 && getBalance(rootNode->right) <= 0)
                return leftRotate(rootNode);
            // RL
            if (balance < -1 && getBalance(rootNode->right) > 0)
            {
                rootNode->right = rightRotate(rootNode->right);
                return leftRotate(rootNode);
            }

            return rootNode;
        }

        bool containsRec(NodeT *node, const T &key) const
        {
            if (!node)
                return false;
            if (cmp(key, node->data))
                return containsRec(node->left, key);
            if (cmp(node->data, key))
                return containsRec(node->right, key);
            return true; // equal
        }
    };
}
#endif