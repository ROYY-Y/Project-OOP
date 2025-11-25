#ifndef OOP_BINARYTREE_H
#define OOP_BINARYTREE_H
#include <bits/stdc++.h>
using namespace std;
// ---------------- Node for Set / BinaryTree ----------------
namespace oop
{
    template <typename T>
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        int height;
        Node(const T &v) : data(v), left(nullptr), right(nullptr), height(1) {}
    };

    // ---------------- BinaryTree base (abstract-ish) ----------------
    template <typename T>
    class BinaryTree
    {
    public:
        Node<T> *root;
        BinaryTree() : root(nullptr) {}
        virtual ~BinaryTree() { clear(root); }

        // Basic traversals
        void inorder() const
        {
            inorder(root);
            cout << '\n';
        }
        void preorder() const
        {
            preorder(root);
            cout << '\n';
        }
        void postorder() const
        {
            postorder(root);
            cout << '\n';
        }

        // Virtual interface (to be implemented by subclasses)
        virtual bool insert(const T &value) = 0;
        virtual bool remove(const T &value) = 0;
        virtual bool contains(const T &value) const = 0;

    protected:
        void inorder(Node<T> *n) const
        {
            if (!n)
                return;
            inorder(n->left);
            cout << n->data << ' ';
            inorder(n->right);
        }
        void preorder(Node<T> *n) const
        {
            if (!n)
                return;
            cout << n->data << ' ';
            preorder(n->left);
            preorder(n->right);
        }
        void postorder(Node<T> *n) const
        {
            if (!n)
                return;
            postorder(n->left);
            postorder(n->right);
            cout << n->data << ' ';
        }

        void clear(Node<T> *n)
        {
            if (!n)
                return;
            clear(n->left);
            clear(n->right);
            delete n;
        }
    };
}

#endif