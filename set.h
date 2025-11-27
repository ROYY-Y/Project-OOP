#ifndef OOP_SET_H
#define OOP_SET_H
#include <bits/stdc++.h>
#include "avltree.h"

namespace oop
{
    template <typename T>
    class Set : public AVLTree<T>
    {
    public:
        // insert ค่าลง set (ห้ามซ้ำ)
        bool insert(const T &value)
        {
            return AVLTree<T>::insert(value);
        }

        // ลบค่าออกจาก set
        bool erase(const T &value)
        {
            return AVLTree<T>::remove(value);
        }

        // เช็คว่ามีค่าหรือเปล่า
        bool contains(const T &value)
        {
            return AVLTree<T>::contains(value);
        }

        // find() → return pointer ไปยังข้อมูล (หรือ nullptr)
        T *find(const T &value)
        {
            return AVLTree<T>::find(value); // ต้องไป implement ใน AVLTree
        }

        // จำนวน element ใน set
        int size() const
        {
            return AVLTree<T>::size();
        }

        // ว่างไหม
        bool empty() const
        {
            return AVLTree<T>::empty();
        }
    };
}
#endif