#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H

namespace oop {

template<typename T>

class vector {
    private:
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

    public:
    typedef T* iterator;

    iterator begin(){
        return &mData[0];
    }

    iterator end(){
        return begin() + mSize;
    }

    vector() {
        mData = nullptr;
        mSize = 0;
        mCap = 0;
    }; // constructor

    ~vector(){ // destructor
        delete[] mData;
    };
    vector(const vector<T> &a){ // copy constructor
        mData = new T[a.cap()]();
        mCap = a.cap();
        mSize = a.size();
        for(size_t i = 0;i < a.size();i++){
            mData[i] = a.mData[i];
        }
    };

    vector<T> operator=(const vector<T> &other){ // assignment operator
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


    void push_back(const T& value){
        CheckCapacity(mSize + 1);
        mData[mSize] = value;
        mSize++;
    };

    void pop_back(){
        mSize--; 
    };

    void clear(){
        mSize = 0;
    };

    size_t size() const {
        return mSize;
    };

    iterator insert(iterator it, const T& value){
        size_t index = it - begin();
        CheckCapacity(mSize + 1);
        for(size_t i = mSize;i > index;i--){
            mData[i] = mData[i - 1];
        }
        mData[index] = value;
        mSize++;
        return begin() + index;
    };

    void erase(iterator it){
        while((it + 1) != end()){
            *it = *(it + 1);
            it++;
        }
        mSize--;
    };

    bool empty() const {
        return mSize == 0;
    }
};

}

#endif //OOP_VECTOR_H