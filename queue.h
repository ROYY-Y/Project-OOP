#ifndef OOP_QUEUE_H
#define OOP_QUEUE_H
#include "dynamic_array.h"  

namespace oop {

template<typename T>
class queue : public oop::dynamic_array<T> {
    private:
    using base = dynamic_array<T>;
    using base::mData;
    using base::mSize;
    using base::mCap;
    size_t mFront;
      

    void expandCapacity(size_t usercap){ // ขยาย capacity
        T* arr = new T[usercap];
        for(size_t i = 0;i < mSize;i++){
            arr[i] = mData[(mFront + i) % mCap];
        }
        delete[] mData;
        mData = arr;
        mCap = usercap;
        mFront = 0;
    };

    void CheckCapacity(size_t usercap){ // check capacity ว่า User ขอเท่าไหร่
        if(usercap > mCap){
            size_t newcap = (usercap > mCap * 2) ? usercap : mCap * 2;
            expandCapacity(newcap);
        }
    };

    public:

    queue() : mData(new T[1]()), mCap(1), mSize(0), mFront(0) { } // constructor

    ~queue(){ // destructor
        delete[] mData;
    };

    queue(const queue<T> &a){ // copy constructor
        mData = new T[a.cap()]();
        mCap = a.cap();
        mSize = a.size();
        mFront = a.mFront;
        for(size_t i = 0;i < a.mCap;i++){
            mData[i] = a.mData[i];
        }
    };

    queue<T> operator=(const queue<T> &other){ // assignment operator
        if(mData != other.mData){
            delete[] mData;
            mData = new T[other.cap()]();
            mCap = other.cap();
            mSize = other.size();
            mFront = other.mFront;
            for(size_t i = 0;i < other.mCap;i++){
                mData[i] = other.mData[i];
            }
        }
        return *this;

    };
    T& operator[](size_t i) {
    return mData[i];
    };

    const T& operator[](size_t i) const {
    return mData[i];
    }

    size_t cap()  const{
    return mCap;
    }
    
    bool empty() const {
        return base::empty();
    } 

    size_t size() const {
        return base::size();
    };

    const T& front() const{
        return mData[mFront];
    }

    const T& back() const{
        return mData[(mFront + mSize - 1) % mCap]; 
    }

    void push (const T& value){  
        CheckCapacity(mSize+1);
        mData[(mFront + mSize) % mCap] = value;
        mSize++;    
    }

    void pop(){
        mFront = (mFront + 1) % mCap;
        mSize--;

    }

   
};

};
#endif