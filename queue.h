#ifndef OOP_QUEUE_H
#define OOP_QUEUE_H
#include "dynamic_array.h"

namespace oop {

template<typename T>
class queue : public dynamic_array<T> {

    using base = dynamic_array<T>;

private:
    size_t mFront;

    void expandCapacity(size_t newcap) {
        T* arr = new T[newcap];
        for(size_t i = 0;i < base::mSize;i++){
            arr[i] = base::mData[(mFront + i) % base::mCap];
        }
        delete[] base::mData;
        base::mData = arr;
        base::mCap = newcap;
        mFront = 0;
    }

    void CheckCapacity(size_t need) {
        if(need > base::mCap){
            size_t newcap = (need > base::mCap * 2) ? need : base::mCap * 2;
            expandCapacity(newcap);
        }
    }

public:
    queue() {
        base::mData = new T[1]();
        base::mCap  = 1;
        base::mSize = 0;
        mFront = 0;
    }

    const T& front() const {
        return base::mData[mFront];
    }

    const T& back() const {
        return base::mData[(mFront + base::mSize - 1) % base::mCap];
    }

    void push(const T& value) {
        CheckCapacity(base::mSize + 1);
        base::mData[(mFront + base::mSize) % base::mCap] = value;
        base::mSize++;
    }

    void pop() {
        mFront = (mFront + 1) % base::mCap;
        base::mSize--;
    }
};

}

#endif
