#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

namespace simple{
    template<typename T>
    class Matrix{
    private:
        std::vector<T> m_data;
        size_t m_row;    
        size_t m_col;    
    public:
        Matrix():m_row(0),m_col(0){}
        Matrix(size_t row, size_t col):m_row(row),m_col(col),m_data(col * row, 0){}
        Matrix(size_t row, size_t col, T initial):m_row(row),m_col(col),m_data(col * row, initial){}
        Matrix(size_t row, size_t col, std::vector<T>& data):m_row(row),m_col(col),m_data(data){}
        Matrix(size_t row, size_t col, std::vector<T>&& data):m_row(row),m_col(col),m_data(std::move(data)){}
        Matrix(Matrix<T>& m):m_row(m.m_row),m_col(m.m_col),m_data(m.m_data){}
        Matrix(Matrix<T>&& m):m_row(std::move(m.m_row)),m_col(std::move(m.m_col)),m_data(std::move(m.m_data)){}

        T& operator()(size_t i, size_t j);
        T& operator[](size_t i);
        
        size_t row() const noexcept;
        size_t col() const noexcept;
        size_t size() const noexcept;

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

        Matrix& operator=(Matrix const &rhs);
        Matrix& operator=(Matrix &&rhs);
        Matrix& operator+(Matrix const &rhs);
        Matrix& operator-(Matrix const &rhs);
        Matrix operator*(Matrix const &rhs);

        Matrix& operator+=(Matrix const &rhs);
        Matrix& operator-=(Matrix const &rhs);
        Matrix operator*=(Matrix const &rhs);
        
        bool operator==(Matrix const &rhs);
        bool operator!=(Matrix const &rhs);

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