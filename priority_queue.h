#ifndef OOP_PRIORITY_QUEUE_H
#define OOP_PRIORITY_QUEUE_H

#include <iostream>
#include "dynamic_array.h"

namespace oop {

template<typename T, typename Comp = std::less<T>>
class priority_queue : public oop::dynamic_array<T> {
private:
    using base = dynamic_array<T>;
    using base::mData;
    using base::mSize;
    using base::mCap;

    Comp mLess;

    /* ---------- internal helpers ---------- */

    void expand(size_t newCap) {
        T* arr = new T[newCap];
        for (size_t i = 0; i < mSize; i++) arr[i] = mData[i];

        delete[] mData;
        mData = arr;
        mCap = newCap;
    }

    void fixUp(size_t index) {
        T temp = mData[index];
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (mLess(temp, mData[parent])) break;   // parent > temp → stop
            mData[index] = mData[parent];
            index = parent;
        }
        mData[index] = temp;
    }

    void fixDown(size_t index) {
        T temp = mData[index];
        size_t child;

        while ((child = index * 2 + 1) < mSize) {
            if (child + 1 < mSize && mLess(mData[child], mData[child + 1]))
                child++;
            if (mLess(mData[child], temp)) break;

            mData[index] = mData[child];
            index = child;
        }
        mData[index] = temp;
    }

public:

    /* ---------- constructors ---------- */

    priority_queue(const Comp& c = Comp())
        : mLess(c)
    {
        mData = new T[1]();
        mCap = 1;
        mSize = 0;
    }

    priority_queue(const priority_queue<T, Comp>& a)
        : mLess(a.mLess)
    {
        mData = new T[a.mCap]();
        mCap = a.mCap;
        mSize = a.mSize;

        for (size_t i = 0; i < mSize; i++)
            mData[i] = a.mData[i];
    }

    /* ---------- assignment ---------- */

    priority_queue& operator=(const priority_queue<T, Comp>& other) {
        if (this != &other) {
            delete[] mData;

            mData = new T[other.mCap]();
            mCap = other.mCap;
            mSize = other.mSize;
            mLess = other.mLess;

            for (size_t i = 0; i < mSize; i++)
                mData[i] = other.mData[i];
        }
        return *this;
    }

    /* ---------- operators ---------- */

    T& operator[](size_t i) { return mData[i]; }
    const T& operator[](size_t i) const { return mData[i]; }

    /* ---------- public API ---------- */

    size_t cap() const { return mCap; }
    size_t size() const { return base::size(); }
    bool empty() const { return base::empty(); }

    const T& top() const { return mData[0]; }

    void push(const T& value) {
        if (mSize + 1 > mCap) expand(mCap * 2);
        mData[mSize] = value;
        mSize++;
        fixUp(mSize - 1);
    }

    void pop() {
        if (empty()) return;
        mData[0] = mData[mSize - 1];
        mSize--;
        if (mSize > 0) fixDown(0);
    }
};

}

#endif
