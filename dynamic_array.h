#ifndef OOP_DYNAMIC_ARRAY_H
#define OOP_DYNAMIC_ARRAY_H

namespace oop {


template<typename T>
class dynamic_array {
    protected:
    T* mData;
    size_t mCap;
    size_t mSize;
    void expandCapacity(size_t usercap){ // ขยาย capacity
        T* arr = new T[usercap];
        for(size_t i = 0;i < mSize;i++){
            arr[i] = mData[i];
        }
        delete[] mData;
        mData = arr;
        mCap = usercap;
    };

    void CheckCapacity(size_t usercap){ // check capacity ว่า User ขอเท่าไหร่
        if(usercap > mCap){
            size_t newcap = (usercap > mCap * 2) ? usercap : mCap * 2;
            expandCapacity(newcap);
        }
    };

    
    void push(const T& value){
        CheckCapacity(mSize + 1);
        mData[mSize] = value;
        mSize++;
    };

    void pop(){
        mSize--; 
    };

    public:

    dynamic_array() {
        mData = nullptr;
        mSize = 0;
        mCap = 0;
    }; // constructor

    ~dynamic_array(){ // destructor
        delete[] mData;
    };
    dynamic_array(const dynamic_array<T> &a){ // copy constructor
        mData = new T[a.cap()]();
        mCap = a.cap();
        mSize = a.size();
        for(size_t i = 0;i < a.size();i++){
            mData[i] = a.mData[i];
        }
    };

    dynamic_array<T> operator=(const dynamic_array<T> &other){ // assignment operator
        if(mData != other.mData){
            delete[] mData;
            mData = new T[other.cap()]();
            mCap = other.cap();
            mSize = other.size();
            for(size_t i = 0;i < other.size();i++){
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

    size_t cap() const{
    return mCap;
    }

    size_t size() const {
        return mSize;
    };

    bool empty() const {
        return mSize == 0;
    }

};
}
#endif