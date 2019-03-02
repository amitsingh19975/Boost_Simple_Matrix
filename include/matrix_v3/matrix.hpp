#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "engine.hpp"
#include "operations.hpp"
#include <cassert>

namespace sm_v3{
    template<typename EnginePolicy, typename OperationPolicy>
    struct Matrix : public BaseExpression< 
        Matrix<EnginePolicy, OperationPolicy >>,
        public EnginePolicy{
        
        using Type = typename EnginePolicy::value_type;
        using EnginePolicy::m_data;
        using EnginePolicy::m_rows;
        using EnginePolicy::m_cols;
        using EnginePolicy::rows;
        using EnginePolicy::cols;
        using EnginePolicy::size;

        Matrix():EnginePolicy(){}
    
        Matrix(Matrix const& other):EnginePolicy(other){}
        Matrix(Matrix && other):EnginePolicy(std::move(other)){}
        
        Matrix& operator=(Matrix const& other){
            this->m_data = other.m_data;
            this->m_rows = other.m_rows;
            this->m_cols = other.m_cols;
            return *this;
        }
        Matrix& operator=(Matrix && other){
            this->m_data = std::move(other.m_data);
            this->m_rows = std::move(other.m_rows);
            this->m_cols = std::move(other.m_cols);
            return *this;
        }
        
        Matrix(typename EnginePolicy::size_type rows, 
            typename EnginePolicy::size_type cols):EnginePolicy(rows, cols){}

        Matrix(typename EnginePolicy::reference other,
            typename EnginePolicy::size_type rows, 
            typename EnginePolicy::size_type cols):EnginePolicy(other, rows, cols){}
        
        Matrix(typename EnginePolicy::const_reference other,
            typename EnginePolicy::size_type rows, 
            typename EnginePolicy::size_type cols):EnginePolicy(other, rows, cols){}

        template<typename Expression>
        Matrix(BaseExpression<Expression> const& m){
            Expression const& temp = m.self();
            if constexpr(!std::is_array_v<typename EnginePolicy::storage_type>){
                m_rows = temp.rows();
                m_cols = temp.cols();
                m_data.resize(temp.size());
            }else{
                assert(m_rows == temp.rows());
                assert(m_cols == temp.cols());
            }
            for(auto i = 0 ; i < m_rows ; i++){
                for(auto j = 0 ; j < m_cols ; j++){
                    this->operator()(i,j) = temp(i,j);
                }
            }
        }

        template<
        typename Operation, 
        typename Op1, 
        typename Op2>
        Matrix(BinaryExpression< Operation , Op1, Op2 >  const& m):EnginePolicy(m.rows(),m.cols()){
            for(auto i = 0; i < m.rows(); i++){
                for(auto j = 0; j < m.cols(); j++){
                    this->operator()(i,j) = m(i,j);
                }
            }
        }

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        constexpr typename EnginePolicy::value_type& operator()(size_t i, size_t j){
            assert(i < m_rows || j < m_cols);
            return m_data[(j * m_rows) + i];
        }

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        constexpr const typename EnginePolicy::value_type& operator()(size_t i, size_t j) const{
            assert(i < m_rows || j < m_cols);
            return m_data[(j * m_rows) + i];
        }
    
        /**
         * Operator[] Overloading
         * for accessing linearly
         * @param i type of size_t
         * @return T&
         */
        constexpr typename EnginePolicy::value_type& operator[](size_t i){
            assert(i < m_data.size());
            return m_data[i];
        }

        template<typename Expression>
        constexpr Matrix& operator=(BaseExpression<Expression> const &rhs){
            return *this = Matrix(rhs);
        }
        
        template<typename Expression>
        constexpr Matrix& operator=(BaseExpression<Expression> &&rhs){
            Expression const& n_rhs = rhs.self();
            if constexpr(!std::is_array_v<typename EnginePolicy::storage_type>){
                m_rows = std::move(n_rhs.rows());
                m_cols = std::move(n_rhs.cols());
                m_data.resize(n_rhs.size());
            }else{
                assert(m_rows == n_rhs.rows());
                assert(m_cols == n_rhs.cols());
            }
            for(auto i = 0; i < n_rhs.rows(); i++){
                for(auto j = 0; j < n_rhs.cols(); j++){
                    this->operator()(i,j) = std::move(n_rhs(i,j));
                }
            }
            return *this;
        }

        /**
         * Operator+= Overloading
         * for addtion of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator+=(BaseExpression<Expression> const &rhs){
            return *this = std::move(Matrix(*this + rhs));
        }
    
        /**
         * Operator-= Overloading
         * for subtraction of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator-=(BaseExpression<Expression> const &rhs){
            return *this = std::move(Matrix(*this - rhs));
        }
        /**
         * Operator*= Overloading
         * for multipication of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr Matrix& operator*=(BaseExpression<Expression> const &rhs){
            return *this = std::move(Matrix(*this * rhs));
        }
    
        /**
         * Operator== Overloading
         * for comparision of two matrices
         * @return bool true if they are equal
         * otherwise false
         */
        template<typename Expression>
        constexpr bool operator==(BaseExpression<Expression> const &rhs){
            Expression const& n_rhs = rhs.self();
            if(this->m_cols != n_rhs.cols() && this->m_rows != n_rhs.rows()) return false;
            for(auto i = 0; i < n_rhs.rows(); i++){
                for(auto j = 0; j < n_rhs.cols(); j++){
                    if( this->operator()(i,j) != n_rhs(i,j) ) return false;
                }
            }
            return true;
        }
    
        /**
         * Operator!= Overloading
         * for comparision of two matrices
         * @return bool true if they are not equal
         * otherwise false
         */
        template<typename Expression>
        constexpr bool operator!=(BaseExpression<Expression> const &rhs){
            return !(*this == rhs);
        }

        ~Matrix() = default;

    };

    template<typename T>
    using Dynamic_V = Engine< DynamicEngine< Storage<std::vector<T>> > >; 

    // template<typename T, size_t matrix_rows, size_t matrix_cols>
    // using Static_A = Engine < StaticEngine< matrix_rows, matrix_cols, 
    //     Storage< std::array<T,matrix_cols * matrix_rows> > > >; 
    
    template<typename T, size_t matrix_rows, size_t matrix_cols>
    using Static_V = Engine < StaticEngine< matrix_rows, matrix_cols, 
        Storage< std::vector<T> > > >; 

    template<typename T>
    using DMatrix = Matrix<Dynamic_V<T>,Operation_Add_Sub_Mul>;

    template<typename T, size_t matrix_rows, size_t matrix_cols>
    using SMatrix = Matrix<Static_V<T,matrix_rows,matrix_cols>,Operation_Add_Sub_Mul>;

}

#endif // MATRIX_HPP
