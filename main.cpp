#include <iostream>
#include "set.h"
#include "map.h"
int main(){
    oop::Map<int,string> m;
    m[10] = "100";
    std::cout << m[10];
}