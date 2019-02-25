#include <iostream>
#include "test/test.hpp"

using namespace std;
using namespace simple;

int main(){
    int size = 1000;
    // test::testIntAssign(size);
    // test::testIntCompare(size);
    // test::testIntAdd(size);
    // test::testIntAddAssign(size);
    // test::testIntSub(size);
    // test::testIntSubAssign(size);
    test::testIntMul(size);
    // test::testIntMulAssign(size);
    // test::testComplexAssign(size);
    // test::testComplexCompare(size);
    // test::testComplexAdd(size);
    // test::testComplexSub(size);
    // test::testComplexSubAssign(size);
    // test::testComplexAddAssign(size);
    test::testComplexMul(size);
    // test::testComplexMulAssign(size);

    return 0;
}