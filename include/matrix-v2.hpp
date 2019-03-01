#ifndef SIMPLE_MATRIX_HPP
#define SIMPLE_MATRIX_HPP

#include "storage.hpp"
#include "operations.hpp"
#include <iostream>

namespace sm{
    template<typename OperationPolicy, typename StoragePolicy>
    struct Matrix : public BaseExpression<
        Matrix<OperationPolicy,StoragePolicy>>,
        public StoragePolicy,
        public OperationPolicy{
        
        using Type = typename StoragePolicy::value_type;

        Matrix() = default;
        Matrix(Matrix const& other):m_data(other.m_data),m_rows(other.m_rows),m_cols(other.m_cols){}
        Matrix(Matrix && other):m_data(std::move(other.m_data)),
            m_rows(std::move(other.m_rows)),m_cols(std::move(other.m_cols)){}
        
        Matrix& operator=(Matrix const& other){return *this = Matrix(other);}
        Matrix& operator=(Matrix && other){
            m_data = std::move(other.m_data);
            m_rows = std::move(other.m_rows);
            m_cols = std::move(other.m_cols);
            return *this;
        }

        template<typename Expression>
        Matrix(BaseExpression<Expression> const& m){
            Expression const& temp = m.self();
            m_rows = temp.rows();
            m_cols = temp.cols();
            m_data.resize(temp.size());
            for(auto i = 0 ; i < m_rows ; i++){
                for(auto j = 0 ; j < m_cols ; j++){
                    this->operator()(i,j) = temp(i,j);
                }
            }
        }

        Matrix(typename StoragePolicy::size_type rows, 
            typename StoragePolicy::size_type cols):m_data(rows * cols),m_rows(rows),m_cols(cols){}
        
        Matrix(typename StoragePolicy::iterator begin, 
            typename StoragePolicy::iterator end,
            typename StoragePolicy::size_type rows, 
            typename StoragePolicy::size_type cols):m_data(begin,end),m_rows(rows),m_cols(cols){}
        
        Matrix(typename StoragePolicy::const_iterator begin, 
            typename StoragePolicy::const_iterator end,
            typename StoragePolicy::size_type rows, 
            typename StoragePolicy::size_type cols):m_data(begin,end),m_rows(rows),m_cols(cols){}
        
        Matrix(typename StoragePolicy::reference other,
            typename StoragePolicy::size_type rows, 
            typename StoragePolicy::size_type cols):m_data(other),m_rows(rows),m_cols(cols){}
        
        Matrix(typename StoragePolicy::const_reference other,
            typename StoragePolicy::size_type rows, 
            typename StoragePolicy::size_type cols):m_data(other),m_rows(rows),m_cols(cols){}

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        typename StoragePolicy::value_type& operator()(size_t i, size_t j){
            if(i >= m_rows || j >= m_cols){
            throw std::out_of_range("Out of Range!");
            }
            return m_data[(j * m_rows) + i];
        }

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        const typename StoragePolicy::value_type& operator()(size_t i, size_t j) const{
            if(i >= m_rows || j >= m_cols){
            throw std::out_of_range("Out of Range!");
            }
            return m_data[(j * m_rows) + i];
        }
    
        /**
         * Operator[] Overloading
         * for accessing linearly
         * @param i type of size_t
         * @return T&
         */
        typename StoragePolicy::value_type& operator[](size_t i){
            if(i >= m_data.size()){
                throw std::out_of_range("Out of Range!");
            }
            return m_data[i];
        }
    
        /**
         * @returns the number of rows
         */
        constexpr auto rows() const noexcept{return m_rows;}

        /**
         * @returns the number of cols
         */    
        constexpr auto cols() const noexcept{return m_cols;}
    
        /**
         * @returns the number of size of vector
         */
        constexpr auto size() const noexcept{return m_data.size();}

        /**
         * Operator<< Overloading
         * for showing matrix
         */
        friend std::ostream &operator<<(std::ostream &os, Matrix const &m){
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < m.rows(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < m.cols(); j++){
                    os << m.m_data[(j * m.rows()) + i]<<',';
                    if(j != m.cols() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }

        /**
         * Operator= Overloading
         * @return Matrix
         */
        template<typename Expression>
        Matrix& operator=(BaseExpression<Expression> const &rhs){
            Expression const& n_rhs = rhs.self();
            this->m_cols = n_rhs.cols();
            this->m_rows = n_rhs.rows();
            m_data.resize(m_cols*m_rows);
            for(auto i = 0; i < rows(); i++){
                for(auto j = 0; j < cols(); j++){
                    this->operator()(i,j) = n_rhs(i,j);
                }
            }
            return *this;
        }
        /**
         * Operator== Overloading
         * @return Matrix
         */
        template<typename Expression>
        Matrix& operator=(BaseExpression<Expression> &&rhs){
            Expression const& n_rhs = rhs.self();
            this->m_cols = std::move(n_rhs.cols());
            this->m_rows = std::move(n_rhs.rows());
            m_data.resize(m_cols*m_rows);
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
        Matrix& operator+=(BaseExpression<Expression> const &rhs){
            *this = (*this + rhs);
            return *this;
        }
    
        /**
         * Operator-= Overloading
         * for subtraction of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        Matrix& operator-=(BaseExpression<Expression> const &rhs){
            *this = (*this - rhs);
            return *this;
        }
        /**
         * Operator*= Overloading
         * for multipication of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        Matrix& operator*=(BaseExpression<Expression> const &rhs){
            Matrix temp = *this * rhs;
            *this = temp;
            return *this;
        }
    
        /**
         * Operator== Overloading
         * for comparision of two matrices
         * @return bool true if they are equal
         * otherwise false
         */
        template<typename Expression>
        bool operator==(BaseExpression<Expression> const &rhs){
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
        bool operator!=(BaseExpression<Expression> const &rhs){
            return !(*this == rhs);
        }

        virtual ~Matrix() = default;
    private:
        typename StoragePolicy::storage_type    m_data{typename StoragePolicy::value_type{0}};
        typename StoragePolicy::size_type       m_rows{0};
        typename StoragePolicy::size_type       m_cols{0};
    };


    template<typename T,size_t array_rows,size_t array_cols, typename OperationPolicy, typename StoragePolicy>
    struct CompileTimeMatrix : public BaseExpression<CompileTimeMatrix 
        <T, array_rows, array_cols, OperationPolicy, StoragePolicy > >,
        public StoragePolicy,
        public OperationPolicy{
        
        using Type = T;

        CompileTimeMatrix() = default;
        CompileTimeMatrix(CompileTimeMatrix const& other):m_data(other.m_data){}
        CompileTimeMatrix(CompileTimeMatrix && other):m_data(std::move(other.m_data)){}
        
        constexpr CompileTimeMatrix& operator=(CompileTimeMatrix const& other){
            assert(m_rows == other.m_rows);
            assert(m_cols == other.m_cols);
            m_data = other.m_data;
            return *this;
        }
        constexpr CompileTimeMatrix& operator=(CompileTimeMatrix && other){
            assert(m_rows == other.m_rows);
            assert(m_cols == other.m_cols);
            m_data = std::move(other.m_data);
            return *this;
        }
        
        CompileTimeMatrix(typename StoragePolicy::iterator begin, 
            typename StoragePolicy::iterator end):m_data(begin,end){}
        
        CompileTimeMatrix(typename StoragePolicy::const_iterator begin, 
            typename StoragePolicy::const_iterator end):m_data(begin,end){}
        
        CompileTimeMatrix(typename StoragePolicy::reference other):m_data(other){}
        
        CompileTimeMatrix(typename StoragePolicy::const_reference other):m_data(other){}

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        constexpr auto& operator()(size_t i, size_t j){
            if(i >= m_rows || j >= m_cols){
            throw std::out_of_range("Out of Range!");
            }
            return m_data[(j * m_rows) + i];
        }
    
        /**
         * Operator[] Overloading
         * for accessing linearly
         * @param i type of size_t
         * @return T&
         */
        constexpr auto& operator[](size_t i){
            if(i >= m_data.size()){
                throw std::out_of_range("Out of Range!");
            }
            return m_data[i];
        }

        /**
         * Operator() Overloading
         * @param i type of size_t
         * @param j type of size_t
         * @return T
         */
        constexpr auto& operator()(size_t i, size_t j) const{
            if(i >= m_rows || j >= m_cols){
            throw std::out_of_range("Out of Range!");
            }
            return m_data[(j * m_rows) + i];
        }
    
        /**
         * @returns the number of rows
         */
        constexpr auto rows() const noexcept{return m_rows;}

        /**
         * @returns the number of cols
         */    
        constexpr auto cols() const noexcept{return m_cols;}
    
        /**
         * @returns the number of size of vector
         */
        constexpr auto size() const noexcept{return m_data.size();}

        /**
         * Operator<< Overloading
         * for showing matrix
         */
        friend std::ostream &operator<<(std::ostream &os, CompileTimeMatrix const &m){
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < m.rows(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < m.cols(); j++){
                    os << m.m_data[(j * m.rows()) + i]<<',';
                    if(j != m.cols() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }

        template<typename Expression>
        CompileTimeMatrix& operator=(BaseExpression<Expression> const &rhs){
            Expression const& n_rhs = rhs.self();
            assert(m_rows == n_rhs.m_rows);
            assert(m_cols == n_rhs.m_cols);
            for(auto i = 0; i < rows(); i++){
                for(auto j = 0; j < cols(); j++){
                    this->operator()(i,j) = n_rhs(i,j);
                }
            }
            return *this;
        }

        /**
         * Operator= Overloading
         * @return Matrix
         */
        template<typename Expression>
        constexpr CompileTimeMatrix& operator=(BaseExpression<Expression> &&rhs){
            Expression const& n_rhs = rhs.self();
            assert(m_rows == n_rhs.m_rows);
            assert(m_cols == n_rhs.m_cols);
            for(auto i = 0; i < rows(); i++){
                for(auto j = 0; j < cols(); j++){
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
        constexpr CompileTimeMatrix& operator+=(BaseExpression<Expression> const &rhs){
            *this = (*this + rhs);
            return *this;
        }
    
        /**
         * Operator-= Overloading
         * for subtraction of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr CompileTimeMatrix& operator-=(BaseExpression<Expression> const &rhs){
            *this = (*this - rhs);
            return *this;
        }
        /**
         * Operator*= Overloading
         * for multipication of two matrices
         * and assigns them
         * @return Matrix
         */
        template<typename Expression>
        constexpr CompileTimeMatrix& operator*=(BaseExpression<Expression> const &rhs){
            auto temp = *this * rhs;
            assert(m_rows == temp.m_rows);
            assert(m_cols == temp.m_cols);
            std::array<T,array_cols * array_rows> temp_data;
            for(auto i = 0; i < rows(); i++){
                for(auto j = 0; j < cols(); j++){
                    temp_data[(j * array_cols)  + i] = temp(i,j);
                }
            }
            this->m_data = temp_data;
            return *this;
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

        virtual ~CompileTimeMatrix() = default;
    private:
        typename StoragePolicy::storage_type    m_data{typename StoragePolicy::value_type{0}};
        typename StoragePolicy::size_type       m_rows{array_rows};
        typename StoragePolicy::size_type       m_cols{array_rows};
    };

    template<typename T>
    using Matrix_V = Matrix<Operation_Add_Sub_Mul, Storage<std::vector<T>>>;
    
    template<typename T, size_t rows, size_t cols>
    using Matrix_A = Matrix<Operation_Add_Sub_Mul, Storage<std::array<T,rows * cols>>>;
    
    template<typename T, size_t rows, size_t cols>
    using CTMatrix = CompileTimeMatrix<T,rows,cols, Operation_Add_Sub_Mul, Storage<std::array<T,rows * cols>>>;
}

#endif // SIMPLE_MATRIX_HPP
