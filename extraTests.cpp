#include <iostream>
#include "extraTests.h"

void testExtra() {
    MultiMap m;
    m.add(1, 100);
    m.add(1, 200);
    m.add(1, 300);
    m.add(1, 500);
    m.add(2, 600);
    m.add(4, 800);

    MultiMap m2;
    m2.add(1, 100);
    assert(m2.updateValues(m) == 4);
    assert(m2.size() == 4);

    MultiMap m3;
    m3.add(10011, 100);
    assert(m3.updateValues(m) == 0);
    assert(m3.size() == 1);

    std::cout<<"Test extra\n";
}