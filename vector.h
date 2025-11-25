#ifndef OOP_VECTOR_H
#define OOP_VECTOR_H
#include "dynamic_array.h"  

namespace oop {

template<typename T>

class vector : public oop::dynamic_array<T> {
    private:
    using base = dynamic_array<T>;
    using base::mData;
    using base::mSize;
    using base::mCap;
    using base::expandCapacity;
    using base::CheckCapacity;
    using base::push;
    using base::pop;

    public:

    typedef T* iterator;

    iterator begin(){
        return &mData[0];
    }

    iterator end(){
        return begin() + mSize;
    }


    void push_back(const T& value){
        push(value);
    };

    void pop_back(){
        pop();
    };

    void clear(){
        mSize = 0;
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

    
    size_t size() const {
        return base::size();
    };
    
    bool empty() const {
        return base::empty();
    }
};

}

#endif //OOP_VECTOR_H