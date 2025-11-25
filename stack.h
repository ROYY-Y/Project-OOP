#ifndef OOP_STACK_H
#define OOP_STACK_H
#include "dynamic_array.h"  

namespace oop {

template<typename T>

class stack : public oop::dynamic_array<T> {
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

    const T& top() const{
        return mData[mSize - 1];
    };

    void push(const T& value){
        base::push(value);
    };

    void pop(){
        base::pop();
    };

    size_t size() const{
        return base::size();
    };

    bool empty() const {
        return base::empty();
    }

};
}

#endif