#ifndef TEST_H
#define TEST_H

#include "../include/matrix.hpp"
#include <iostream>
#include <chrono>
#include <complex>
#include <cassert>

namespace test {
    using namespace simple;
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

    
    auto testIntAssign(size_t test_size = 100) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        START
        n = m;
        STOP("Assignment Time in milliseconds: ")
        assert(m==n);
        std::cout<<"Assignment Test Passed!"<<"\n\n";
    }

    auto testIntCompare(size_t test_size = 100) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i + j;
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

    auto testIntAdd(size_t test_size = 100) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i + j;
        START
        auto s = m + n;
        STOP("Matrix Addition Time in milliseconds: ")

        Matrix<size_t> sum(test_size,test_size);

        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                sum(i,j) = 2 * (i + j);
                
        assert(sum == s);
        std::cout<<"Matrix Addition Test Passed!\n"<<'\n';
        
    }
    auto testIntAddAssign(size_t test_size = 100) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i + j;
        START
        m += n;
        STOP("Matrix Addition Assign Time in milliseconds: ")

        Matrix<size_t> sum(test_size,test_size);

        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                sum(i,j) = 2 * (i + j);
                
        assert(sum == m);
        std::cout<<"Matrix Addition Assign Test Passed!\n\n";
        
    }
    auto testIntSub(size_t test_size = 100) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i + j;
        START
        auto diff = m - n;
        STOP("Matrix Subtraction Time in milliseconds: ")

        Matrix<size_t> t(test_size,test_size);

        assert(t == diff);
        std::cout<<"Matrix Subtraction Test Passed!\n\n";
    }
    auto testIntSubAssign(size_t test_size = 100) ->void {
        Matrix<int> m(test_size,test_size);
        Matrix<int> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i + j;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i + j;
        START
        m -= n;
        STOP("Matrix Subtraction Assign Time in milliseconds: ")

        Matrix<int> diff(test_size,test_size);

        assert(diff == m);
        std::cout<<"Matrix Subtraction Assign Test Passed!\n\n";
    }

    auto testIntMul(size_t test_size = 4) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i*m.col() + j + 1;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i*m.col() + j + 1;
        START
        auto prod = m * n;
        STOP("Matrix Multipication Time in milliseconds: ");

        std::vector<std::vector<size_t>> test(test_size,std::vector<size_t>(test_size));
        for(auto i = 0; i < test_size; i++)
            for(auto j = 0; j < test_size; j++)
                test[i][j] = i * test_size + j + 1;


        for( int i = 0; i < test_size; i++ ) {
            for( int j = 0; j < test_size; j++ ) {
                size_t val = 0;
                for( int k = 0; k < test_size; k++ ) {
                    val += test[i][k] * test[k][j];
                }
                assert(( prod(i,j) == val ));
            }
        }
        std::cout<<"Matrix Multipication Test Passed!\n\n";
    }

    auto testIntMulAssign(size_t test_size = 3) ->void {
        Matrix<size_t> m(test_size,test_size);
        Matrix<size_t> n(test_size,test_size);
        
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = i*m.col() + j + 1;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = i*m.col() + j + 1;
        START
        m *= n;
        STOP("Matrix Multipication Assign Time in milliseconds: ");
        std::vector<std::vector<size_t>> test(test_size,std::vector<size_t>(test_size));
        for(auto i = 0; i < test_size; i++)
            for(auto j = 0; j < test_size; j++)
                test[i][j] = i * test_size + j + 1;


        for( int i = 0; i < test_size; i++ ) {
            for( int j = 0; j < test_size; j++ ) {
                size_t val = 0;
                for( int k = 0; k < test_size; k++ ) {
                    val += test[i][k] * test[k][j];
                }
                assert(( m(i,j) == val ));
            }
        }
        std::cout<<"Matrix Multipication Assign Test Passed!\n\n";
    }

    auto testComplexAssign(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n;
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        START
        n = m;
        STOP("Complex Assignment Time in milliseconds: ")
        assert(m==n);
        std::cout<<"Complex Assignment Test Passed!"<<"\n\n";
    }

    auto testComplexCompare(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i + j,i + j);
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

    auto testComplexAdd(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i + j,i + j);
        START
        auto s = m + n;
        STOP("Complex Matrix Addition Time in milliseconds: ")

        Matrix<complex<int>> sum(test_size,test_size);

        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                sum(i,j) = complex(2 * (i + j),2 * (i + j));
                
        assert(sum == s);
        std::cout<<"Complex Matrix Addition Test Passed!\n\n";
        
    }
    auto testComplexAddAssign(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i + j,i + j);
        START
        m += n;
        STOP("Complex Matrix Addition Assign Time in milliseconds: ")

        Matrix<complex<int>> sum(test_size,test_size);

        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                sum(i,j) = complex(2 * (i + j),2 * (i + j));
                
        assert(sum == m);
        std::cout<<"Complex Matrix Addition Assign Test Passed!\n\n";
        
    }
    auto testComplexSub(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i + j,i + j);
        START
        auto diff = m - n;
        STOP("Complex Matrix Subtraction Time in milliseconds: ")

        Matrix<complex<int>> t(test_size,test_size);

        assert(t == diff);
        std::cout<<"Complex Matrix Subtraction Test Passed!\n\n";
    }
    auto testComplexSubAssign(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i + j,i + j);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i + j,i + j);
        START
        m -= n;
        STOP("Complex Matrix Subtraction Assign Time in milliseconds: ")

        Matrix<complex<int>> diff(test_size,test_size);

        assert(diff == m);
        std::cout<<"Complex Matrix Subtraction Assign Test Passed!\n\n";
    }

    auto testComplexMul(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i * m.col() + j + 1,i * m.col() + j + 1);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i * m.col() + j + 1,i * m.col() + j + 1);
        START
        auto prod = m * n;
        STOP("Complex Matrix Multipication Time in milliseconds: ");

        std::vector<std::vector<complex<int>>> test(test_size,std::vector<complex<int>>(test_size));
        for(auto i = 0; i < test_size; i++)
            for(auto j = 0; j < test_size; j++)
                test[i][j] = complex(i * test_size + j + 1,i * test_size + j + 1);


        for( int i = 0; i < test_size; i++ ) {
            for( int j = 0; j < test_size; j++ ) {
                complex val = complex(0,0);
                for( int k = 0; k < test_size; k++ ) {
                    val += test[i][k] * test[k][j];
                }
                assert(( prod(i,j) == val ));
            }
        }
        std::cout<<"Complex Matrix Multipication Test Passed!\n\n";
    }

    auto testComplexMulAssign(size_t test_size = 100) ->void {
        Matrix<complex<int>> m(test_size,test_size);
        Matrix<complex<int>> n(test_size,test_size);
        
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                m(i,j) = complex(i * m.col() + j + 1,i * m.col() + j + 1);
        for(auto i = 0; i < m.row(); i++)
            for(auto j = 0; j < m.col(); j++)
                n(i,j) = complex(i * m.col() + j + 1,i * m.col() + j + 1);
        START
        m *= n;
        STOP("Complex Matrix Multipication Assign Time in milliseconds: ");

        std::vector<std::vector<complex<int>>> test(test_size,std::vector<complex<int>>(test_size));
        for(auto i = 0; i < test_size; i++)
            for(auto j = 0; j < test_size; j++)
                test[i][j] = complex(i * test_size + j + 1,i * test_size + j + 1);


        for( int i = 0; i < test_size; i++ ) {
            for( int j = 0; j < test_size; j++ ) {
                complex val = complex(0,0);
                for( int k = 0; k < test_size; k++ ) {
                    val += test[i][k] * test[k][j];
                }
                assert(( m(i,j) == val ));
            }
        }
        std::cout<<"Complex Matrix Multipication Assign Test Passed!\n\n";
    }
}

#endif // TEST_H
