#include <iostream>
#include "test/test.hpp"

using namespace std;
using namespace simple;

int main(){

    test::testIntAssign();
    test::testIntCompare();
    test::testIntAdd(1000);
    test::testIntAddAssign();
    test::testIntSub(1000);
    test::testIntSubAssign();
    test::testIntMul(1000);
    test::testIntMulAssign();
    test::testComplexAssign();
    test::testComplexCompare();
    test::testComplexAdd(1000);
    test::testComplexSub(1000);
    test::testComplexSubAssign();
    test::testComplexAddAssign();
    test::testComplexMul(1000);
    test::testComplexMulAssign();

    return 0;
}