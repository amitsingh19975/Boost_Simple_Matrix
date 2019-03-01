#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H

#ifndef MATRIX_TEST_SIZE
#define MATRIX_TEST_SIZE 1000
#endif

#include "../include/matrix-v2.hpp"
#include <iostream>
#include <chrono>
#include <complex>
#include <cassert>

namespace matrix_test {
    using namespace sm;
    using chr_high = std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::complex;
    
    chr_high::time_point t1,t2;
    milliseconds t;

    #define START t1 = chr_high::now();
    #define STOP(messg) t2 = chr_high::now(); \
            t = duration_cast<milliseconds>(t2 - t1);\
            std::cout<<messg<<t.count()<<'\n';

    template<typename T>
    auto at(std::vector<T>& v,size_t size,size_t i, size_t j) -> T&{
        return v[(j * size) + i];
    }
    
    auto testIntAssign() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        START
        n = m;
        STOP("Assignment Time in milliseconds: ")
        assert(m==n);
        std::cout<<"Assignment Test Passed!"<<"\n\n";
    }

    auto testIntCompare() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i + j;
            }
        }
        
        std::vector<size_t> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);
        std::vector<size_t> test_eq(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);

        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = i * MATRIX_TEST_SIZE + j + 1;
            }
        }
            
        
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_eq,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }

        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test_eq,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,j);
            }
        }

        auto eq = m * n + n;
        START
        assert(m==n);
        STOP("Compare(==) Time in milliseconds: ")
        std::cout<<"Compare(==) Test Passed!"<<'\n';
        
        n[0] = 1324;
        
        START
        assert((m!=n));
        STOP("Compare(!=) Time in milliseconds: ")
        std::cout<<"Compare(!=) Test Passed!"<<"\n\n";
    }

    auto testIntAdd() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> sum(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                sum(i,j) = 2 * (i + j);
            }
        }

        START
        auto s = m + n;
        for(auto i = 0; i < s.rows(); i++)
            for(auto j = 0; j < s.cols(); j++)
                s(i,j);
        STOP("Matrix Addition Time in milliseconds: ")
        assert(sum == s);
        std::cout<<"Matrix Addition Test Passed!\n"<<'\n';
        
    }
    auto testIntAddAssign() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> sum(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i + j;
            }
        }

        START
        m += n;
        STOP("Matrix Addition Assign Time in milliseconds: ")

        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                sum(i,j) = 2 * (i + j);
            }
        }
                
        assert(sum == m);
        std::cout<<"Matrix Addition Assign Test Passed!\n\n";
        
    }
    auto testIntSub() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> test(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i + j;
            }
        }

        START
        auto diff = m - n;
        for(auto i = 0; i < diff.rows(); i++)
            for(auto j = 0; j < diff.cols(); j++)
                diff(i,j);
        STOP("Matrix Subtraction Time in milliseconds: ")
        assert(test == diff);
        std::cout<<"Matrix Subtraction Test Passed!\n\n";
    }
    auto testIntSubAssign() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> diff(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i + j;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i + j;
            }
        }

        START
        m -= n;
        STOP("Matrix Subtraction Assign Time in milliseconds: ")

        assert(diff == m);
        std::cout<<"Matrix Subtraction Assign Test Passed!\n\n";
    }

    auto testIntMul() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i*m.cols() + j + 1;
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = i*m.cols() + j + 1;
            }
        }

        std::vector<size_t> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);
        std::vector<size_t> test_prod(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);
        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = i * MATRIX_TEST_SIZE + j + 1;
            }
        }

        START
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                size_t val = 0;
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_prod,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }
        STOP("Matrix Direct Multipication Time in milliseconds: ");

        START
        auto prod = m * n;
        for(auto i = 0; i < prod.rows(); i++){
            for(auto j = 0; j < prod.cols(); j++){
                assert(( prod(i,j) == at(test_prod,MATRIX_TEST_SIZE,i,j) ));
            }
        }
        STOP("Matrix Lazy Multipication Time in milliseconds: ");

        std::cout<<"Matrix Multipication Test Passed!\n\n";
    }

    auto testIntMulAssign() ->void {
        Matrix_V<size_t> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<size_t> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = i*m.cols() + j + 1;
            }
        }
        for(auto i = 0; i < n.rows(); i++){
            for(auto j = 0; j < n.cols(); j++){
                n(i,j) = i*n.cols() + j + 1;
            }
        }

        std::vector<size_t> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);
        std::vector<size_t> test_prod(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,0);
        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = i * MATRIX_TEST_SIZE + j + 1;
            }
        }

        START
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_prod,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }
        STOP("Matrix Direct Assign Multipication  Time in milliseconds: ");

        START
        m *= n;
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                // std::cout<<m(i,j)<<'='<<at(test_prod,MATRIX_TEST_SIZE,i,j)<<'\n';
                assert(( m(i,j) == at(test_prod,MATRIX_TEST_SIZE,i,j) ));
            }
        }
        STOP("Matrix Lazy Assign Multipication Time in milliseconds: ");

        std::cout<<"Matrix Multipication Test Passed!\n\n";
    }

    auto testComplexAssign() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
                
        START
        n = m;
        STOP("Complex Assignment Time in milliseconds: ")
        assert(m==n);
        std::cout<<"Complex Assignment Test Passed!"<<"\n\n";
    }

    auto testComplexCompare() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i + j,i + j);
            }
        }
        
        std::vector<complex<size_t>> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});
        std::vector<complex<size_t>> test_eq(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});

        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = i * MATRIX_TEST_SIZE + j + 1;
            }
        }
        
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_eq,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }

        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test_eq,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,j);
            }
        }
        auto eq = m * n + n;
        START
        assert(m==n);
        STOP("Complex Compare(==) Time in milliseconds: ")
        std::cout<<"Complex Compare(==) Test Passed!"<<'\n';
        
        n[0] = 1324;
        
        START
        assert((m!=n));
        STOP("Complex Compare(!=) Time in milliseconds: ")
        std::cout<<"Complex Compare(!=) Test Passed!"<<"\n\n";
    }

    auto testComplexAdd() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> sum(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);

        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i + j,i + j);
            }
        }

        for(auto i = 0; i < m.rows(); i++)
            for(auto j = 0; j < m.cols(); j++)
                sum(i,j) = complex(2 * (i + j),2 * (i + j));
    
        START
        auto s = m + n;
        for(auto i = 0; i < s.rows(); i++)
            for(auto j = 0; j < s.cols(); j++)
                s(i,j);
        STOP("Complex Matrix Addition Time in milliseconds: ")   
        assert(sum == s);
        std::cout<<"Complex Matrix Addition Test Passed!\n\n";
        
    }
    auto testComplexAddAssign() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> sum(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i + j,i + j);
            }
        }
        START
        m += n;
        STOP("Complex Matrix Addition Assign Time in milliseconds: ")


        for(auto i = 0; i < m.rows(); i++)
            for(auto j = 0; j < m.cols(); j++)
                sum(i,j) = complex(2 * (i + j),2 * (i + j));
                
        assert(sum == m);
        std::cout<<"Complex Matrix Addition Assign Test Passed!\n\n";
        
    }
    auto testComplexSub() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> test(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i + j,i + j);
            }
        }
        START
        auto diff = m - n;
        for(auto i = 0; i < diff.rows(); i++){
            for(auto j = 0; j < diff.cols(); j++){
                diff(i,j);
            }
        }
            
        STOP("Complex Matrix Subtraction Time in milliseconds: ")
        assert(test == diff);
        std::cout<<"Complex Matrix Subtraction Test Passed!\n\n";
    }
    auto testComplexSubAssign() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> diff(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i + j,i + j);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i + j,i + j);
            }
        }
        START
        m -= n;
        STOP("Complex Matrix Subtraction Assign Time in milliseconds: ")


        assert(diff == m);
        std::cout<<"Complex Matrix Subtraction Assign Test Passed!\n\n";
    }

    auto testComplexMul() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i * m.cols() + j + 1,i * m.cols() + j + 1);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i * m.cols() + j + 1,i * m.cols() + j + 1);
            }
        }
        
        std::vector<complex<size_t>> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});
        std::vector<complex<size_t>> test_prod(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});
        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = complex(i * MATRIX_TEST_SIZE + j + 1,i * MATRIX_TEST_SIZE + j + 1);
            }
        }
            

        START
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_prod,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }
        STOP("Complex Matrix Direct Multipication Time in milliseconds: ");

        START
        auto prod = m * n;
        for(auto i = 0; i < prod.rows(); i++){
            for(auto j = 0; j < prod.cols(); j++){
                assert(( prod(i,j) == at(test_prod,MATRIX_TEST_SIZE,i,j) ));
            }
        }
        STOP("Complex Matrix Lazy Multipication Time in milliseconds: ");
        std::cout<<"Complex Matrix Multipication Test Passed!\n\n";
    }

    auto testComplexMulAssign() ->void {
        Matrix_V<complex<size_t>> m(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        Matrix_V<complex<size_t>> n(MATRIX_TEST_SIZE, MATRIX_TEST_SIZE);
        
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                m(i,j) = complex(i * m.cols() + j + 1,i * m.cols() + j + 1);
            }
        }
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                n(i,j) = complex(i * m.cols() + j + 1,i * m.cols() + j + 1);
            }
        }
        
        std::vector<complex<size_t>> test(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});
        std::vector<complex<size_t>> test_prod(MATRIX_TEST_SIZE * MATRIX_TEST_SIZE,complex{0,0});
        for(auto i = 0; i < MATRIX_TEST_SIZE; i++){
            for(auto j = 0; j < MATRIX_TEST_SIZE; j++){
                at(test,MATRIX_TEST_SIZE,i,j) = complex(i * MATRIX_TEST_SIZE + j + 1,i * MATRIX_TEST_SIZE + j + 1);
            }
        }

        START
        for( int i = 0; i < MATRIX_TEST_SIZE; i++ ) {
            for( int j = 0; j < MATRIX_TEST_SIZE; j++ ) {
                size_t val = 0;
                for( int k = 0; k < MATRIX_TEST_SIZE; k++ ) {
                    at(test_prod,MATRIX_TEST_SIZE,i,j) += at(test,MATRIX_TEST_SIZE,i,k) * at(test,MATRIX_TEST_SIZE,k,j);
                }
            }
        }
        STOP("Complex Matrix Direct Assign Multipication Time in milliseconds: ");

        START
        m *= n;
        for(auto i = 0; i < m.rows(); i++){
            for(auto j = 0; j < m.cols(); j++){
                assert(( m(i,j) == at(test_prod,MATRIX_TEST_SIZE,i,j)));
            }
        }
        STOP("Complex Matrix Lazy Assign Multipication Time in milliseconds: ");
        std::cout<<"Complex Matrix Multipication Assign Test Passed!\n\n";
    }
}

#endif // MATRIX_TEST_H
