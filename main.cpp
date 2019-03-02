#include "include/matrix_v3/matrix.hpp"
#include "test/matrix_test_v3_dynamic.hpp"
#include "test/matrix_test_v3_static.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <complex>


int main(){
    smatrix_test::testIntAssign();
    smatrix_test::testIntCompare();
    smatrix_test::testIntAdd();
    smatrix_test::testIntAddAssign();
    smatrix_test::testIntSub();
    smatrix_test::testIntSubAssign();
    smatrix_test::testIntMul();
    smatrix_test::testIntMulAssign();
    smatrix_test::testComplexAssign();
    smatrix_test::testComplexCompare();
    smatrix_test::testComplexAdd();
    smatrix_test::testComplexSub();
    smatrix_test::testComplexSubAssign();
    smatrix_test::testComplexAddAssign();
    smatrix_test::testComplexMul();
    smatrix_test::testComplexMulAssign();
    smatrix_test::testIntAssign();
    
    dynamic_matrix_test::testIntCompare();
    dynamic_matrix_test::testIntAdd();
    dynamic_matrix_test::testIntAddAssign();
    dynamic_matrix_test::testIntSub();
    dynamic_matrix_test::testIntSubAssign();
    dynamic_matrix_test::testIntMul();
    dynamic_matrix_test::testIntMulAssign();
    dynamic_matrix_test::testComplexAssign();
    dynamic_matrix_test::testComplexCompare();
    dynamic_matrix_test::testComplexAdd();
    dynamic_matrix_test::testComplexSub();
    dynamic_matrix_test::testComplexSubAssign();
    dynamic_matrix_test::testComplexAddAssign();
    dynamic_matrix_test::testComplexMul();
    dynamic_matrix_test::testComplexMulAssign();

    return 0;
}