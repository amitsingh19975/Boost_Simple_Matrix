#include <iostream>
#include "test/test.hpp"

using namespace std;
using namespace simple;

int main(){

    test::testIntAssign();
    test::testIntCompare();
    test::testIntAdd();
    test::testIntAddAssign();
    test::testIntSub();
    test::testIntSubAssign();
    test::testIntMul();
    test::testIntMulAssign();
    test::testComplexAssign();
    test::testComplexCompare();
    test::testComplexAdd();
    test::testComplexSub();
    test::testComplexSubAssign();
    test::testComplexAddAssign();
    test::testComplexMul();
    test::testComplexMulAssign();

    return 0;
}