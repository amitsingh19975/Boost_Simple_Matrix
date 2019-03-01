// #include "test/test.hpp"
#include "test/cmatrix_test.hpp"
#include "test/matrix_test.hpp"
#include <cassert>
#include <chrono>
#include <complex>

int main(){
    ctmatrix_test::testIntAssign();
    ctmatrix_test::testIntCompare();
    ctmatrix_test::testIntAdd();
    ctmatrix_test::testIntAddAssign();
    ctmatrix_test::testIntSub();
    ctmatrix_test::testIntSubAssign();
    ctmatrix_test::testIntMul();
    ctmatrix_test::testIntMulAssign();
    ctmatrix_test::testComplexAssign();
    ctmatrix_test::testComplexCompare();
    ctmatrix_test::testComplexAdd();
    ctmatrix_test::testComplexSub();
    ctmatrix_test::testComplexSubAssign();
    ctmatrix_test::testComplexAddAssign();
    ctmatrix_test::testComplexMul();
    ctmatrix_test::testComplexMulAssign();
    ctmatrix_test::testIntAssign();
    
    matrix_test::testIntCompare();
    matrix_test::testIntAdd();
    matrix_test::testIntAddAssign();
    matrix_test::testIntSub();
    matrix_test::testIntSubAssign();
    matrix_test::testIntMul();
    matrix_test::testIntMulAssign();
    matrix_test::testComplexAssign();
    matrix_test::testComplexCompare();
    matrix_test::testComplexAdd();
    matrix_test::testComplexSub();
    matrix_test::testComplexSubAssign();
    matrix_test::testComplexAddAssign();
    matrix_test::testComplexMul();
    matrix_test::testComplexMulAssign();
    return 0;
}