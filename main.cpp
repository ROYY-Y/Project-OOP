#include <iostream>
#include "queue.h"
#include "vector.h"
#include "set.h"
#include "map.h"
#include "directed_graph.h"
#include "priority_queue.h"
using namespace std;

int main(){
    oop::Map<int, string> mp;

    cout << "== Test Insert ==" << endl;
    mp.insert(10, "apple");
    mp.insert(20, "banana");
    mp.insert(30, "cat");

    cout << "Contains 20? " << (mp.contains(20) ? "YES" : "NO") << endl;
    cout << "Contains 99? " << (mp.contains(99) ? "YES" : "NO") << endl;

    cout << "\n== Test get(key) ==" << endl;
    string* p = mp.get(30);
    if (p) cout << "get(30) = " << *p << endl;
    else   cout << "get(30) = NOT FOUND" << endl;

    p = mp.get(999);
    if (p) cout << "get(999) = " << *p << endl;
    else   cout << "get(999) = NOT FOUND" << endl;

    cout << "\n== Test operator[] ==" << endl;

    cout << "mp[10] = " << mp[10] << endl; 
    cout << "mp[20] = " << mp[20] << endl; 

    cout << "mp[50] = " << mp[50] << endl;  

    mp[20] = "blueberry"; //
    cout << "mp[20] updated = " << mp[20] << endl;

    cout << "\n== Test Insert Duplicate ==" << endl;
    mp.insert(10, "dog"); 
    cout << "mp[10] = " << mp[10] << "  (should still be 'apple')" << endl;

    cout << "\n== Loop Test ==" << endl;

    for (int k : {10, 20, 30, 50}) {
        cout << k << " -> " << mp[k] << endl;
    }
}