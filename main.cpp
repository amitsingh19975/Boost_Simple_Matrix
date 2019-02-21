#include <iostream>
#include "test/test.hpp"

using namespace std;
using namespace simple;

int main(){

    test::testIntAssign(1000);
    test::testIntCompare(1000);
    test::testIntAdd(1000);
    test::testIntAddAssign();
    test::testIntSub(1000);
    test::testIntSubAssign();
    test::testIntMul(1000);
    test::testIntMulAssign(1000);
    test::testComplexAssign(1000);
    test::testComplexCompare();
    test::testComplexAdd(1000);
    test::testComplexSub(1000);
    test::testComplexSubAssign(1000);
    test::testComplexAddAssign(1000);
    test::testComplexMul(1000);
    test::testComplexMulAssign(1000);

    return 0;
}