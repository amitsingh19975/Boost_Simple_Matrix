#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

/**
 * Simple Matrix
 */
namespace simple{
    template<typename T>
    class Matrix{
    private:
    /**
     * private member for storing data
     */
        std::vector<T> m_data;
    /**
     * prevate member for storing rows
     */
        size_t m_row;    
    /**
     * prevate member for storing cols
     */
        size_t m_col;    
    public:
    /**
     * default constructor
     */
        Matrix():m_row(0),m_col(0){}
    /**
     * Constructor
     * @param row type of size_t
     * @param col type of size_t
     */
        Matrix(size_t row, size_t col):m_row(row),m_col(col),m_data(col * row, 0){}
    
    /**
     * Constructor
     * @param row type of size_t
     * @param col type of size_t
     * @param initial type of any type for storing default value
     */
        Matrix(size_t row, size_t col, T initial):m_row(row),m_col(col),m_data(col * row, initial){}
        
    /**
     * Constructor
     * @param row type of size_t
     * @param col type of size_t
     * @param data type of std::vector of any type
     */
        Matrix(size_t row, size_t col, std::vector<T>& data):m_row(row),m_col(col),m_data(data){}
    
    /**
     * Constructor
     * @param row type of size_t
     * @param col type of size_t
     * @param data type of std::vector of any type move semantics
     */
        Matrix(size_t row, size_t col, std::vector<T>&& data):m_row(row),m_col(col),m_data(std::move(data)){}
    
    /**
     * Copy Constructor
     * @param m type of Matrix
     */    
        Matrix(Matrix<T> const& m):m_row(m.m_row),m_col(m.m_col),m_data(m.m_data){}
    /**
     * Move Constructor
     * @param m type of Matrix
     */
        Matrix(Matrix<T>&& m):m_row(std::move(m.m_row)),m_col(std::move(m.m_col)),m_data(std::move(m.m_data)){}

    /**
     * Operator() Overloading
     * @param i type of size_t
     * @param j type of size_t
     */
        T& operator()(size_t i, size_t j);
    
    /**
     * Operator[] Overloading
     * for accessing linearly
     * @param i type of size_t
     */
        T& operator[](size_t i);
    
    /**
     * @returns the number of rows
     */
        size_t row() const noexcept;

    /**
     * @returns the number of cols
     */    
        size_t col() const noexcept;
    
    /**
     * @returns the number of size of vector
     */
        size_t size() const noexcept;

    /**
     * Operator<< Overloading
     * for showing matrix
     */
        friend std::ostream &operator<<(std::ostream &os, Matrix const &m){
            os<<'['<<' '<<'\n';
            for(size_t i = 0; i < m.row(); i++){
                os<<' '<<'('<<' ';
                for (size_t j = 0; j < m.col(); j++){
                    os << m.m_data[(j * m.row()) + i]<<',';
                    if(j != m.col() - 1){
                        os<<' ';
                    }
                }
                os<<')'<<','<<'\n';
            }
            os<<']'<<'\n';
            return os;
        }

    /**
     * Operator== Overloading
     * @return Matrix
     */
        Matrix& operator=(Matrix const &rhs);
    /**
     * Operator== Overloading
     * @return Matrix
     */
        Matrix& operator=(Matrix &&rhs);
    /**
     * Operator+ Overloading
     * for addtion of two matrices
     * @return Matrix
     */
        Matrix& operator+(Matrix const &rhs);
    
    /**
     * Operator- Overloading
     * for subtraction of two matrices
     * @return Matrix
     */
        Matrix& operator-(Matrix const &rhs);
    
    /**
     * Operator* Overloading
     * for multipication of two matrices
     * @return Matrix
     */
        Matrix operator*(Matrix const &rhs);

    /**
     * Operator+= Overloading
     * for addtion of two matrices
     * and assigns them
     * @return Matrix
     */
        Matrix& operator+=(Matrix const &rhs);
    
    /**
     * Operator-= Overloading
     * for subtraction of two matrices
     * and assigns them
     * @return Matrix
     */
        Matrix& operator-=(Matrix const &rhs);
    /**
     * Operator*= Overloading
     * for multipication of two matrices
     * and assigns them
     * @return Matrix
     */
        Matrix operator*=(Matrix const &rhs);
    
    /**
     * Operator== Overloading
     * for comparision of two matrices
     * @return bool true if they are equal
     * otherwise false
     */
        bool operator==(Matrix const &rhs);
    
    /**
     * Operator!= Overloading
     * for comparision of two matrices
     * @return bool true if they are not equal
     * otherwise false
     */
        bool operator!=(Matrix const &rhs);

    /**
     * Destructor
     */
        ~Matrix(){}
    };

    template<typename T>
    size_t Matrix<T>::row() const noexcept{
        return m_row;
    }
    template<typename T>
    size_t Matrix<T>::col() const noexcept{
        return m_col;
    }
    template<typename T>
    size_t Matrix<T>::size() const noexcept{
        return m_data.size();
    }

    template<typename T>
    T& Matrix<T>::operator()(size_t i, size_t j){
        if(i >= m_row || j >= m_col){
            throw std::out_of_range("Out of Range!");
        }
        return m_data[(j * m_row) + i];
    }
    template<typename T>
    T& Matrix<T>::operator[](size_t i){
        if(i >= m_data.size()){
            throw std::out_of_range("Out of Range!");
        }
        return m_data[i];
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator+(Matrix<T> const &rhs){

        if(this->m_col != rhs.m_col || this->m_row != rhs.m_row){
            throw std::runtime_error("Size does not match!");
        }

        for(size_t i = 0; i < m_data.size(); i++){
            m_data[i] += rhs.m_data[i];
        }
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator-(Matrix<T> const &rhs){
        
        if(this->m_col != rhs.m_col || this->m_row != rhs.m_row){
            throw std::runtime_error("Size does not match!");
        }

        for(size_t i = 0; i < m_row * m_col; i++){
            m_data[i] -= rhs.m_data[i];
        }
        return *this;

    }
    template<typename T>
    Matrix<T> Matrix<T>::operator*(Matrix<T> const &rhs){
        
        if(this->m_col != rhs.m_row){
            throw std::runtime_error("Row doesn't matches with Column!");
        }

        Matrix<T> res(this->m_row,rhs.m_col);

        for(auto i = 0; i < res.m_row; i++){
            for(auto j = 0; j < res.m_col; j++){
                for(auto k = 0; k < this->m_col; k++){
                    res(i,j) += this->m_data[(k * this->m_row) + i] * rhs.m_data[(j * rhs.m_row) + k];
                }
            }
        }
        return res;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator+=(Matrix<T> const &rhs){
         *this = (*this + rhs);
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator-=(Matrix<T> const &rhs){
        *this = (*this - rhs);
        return *this;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator*=(Matrix<T> const &rhs){
        *this = (*this * rhs);
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix const &rhs){
        this->m_col = rhs.m_col;
        this->m_row = rhs.m_row;
        this->m_data = rhs.m_data;
        return *this;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix &&rhs){
        this->m_col = std::move(rhs.m_col);
        this->m_row = std::move(rhs.m_row);
        this->m_data = std::move(rhs.m_data);
        return *this;
    }

    template<typename T>
    bool Matrix<T>::operator==(Matrix const& rhs){
        if(this->m_col != rhs.m_col && this->m_row != rhs.m_row) return false;
        for(auto i = 0; i < rhs.m_data.size(); i++){
            if( this->m_data[i] != rhs.m_data[i] ) return false;
        }
        return true;
    }

    template<typename T>
    bool Matrix<T>::operator!=(Matrix const& rhs){
        return !(*this == rhs);
    }


}

#endif