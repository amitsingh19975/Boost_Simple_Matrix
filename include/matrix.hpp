#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <type_traits>

/**
 * Simple Matrix
 */
namespace simple{

    template<typename Expression>
    struct BaseExpression{
        constexpr auto self() const-> Expression const&{
            return static_cast<Expression const&>(*this);
        }
        virtual ~BaseExpression(){}
    };

    template<typename Operation, typename Op1, typename Op2> 
    struct BinaryExpression : public BaseExpression<BinaryExpression<Operation,Op1,Op2>>{
        Op1 const& m_lhs;
        Op2 const& m_rhs;
        Operation m_oper;

        BinaryExpression(Op1 const& lhs, Op2 const& rhs):m_lhs(lhs),m_rhs(rhs){}

        using Type = std::common_type_t<typename Op1::Type,typename Op2::Type>;
        
        constexpr auto operator()(size_t i, size_t j) const -> Type{
            return m_oper(m_lhs.self(),m_rhs.self(),i,j);
        }

        constexpr auto operator()(size_t i) const -> bool{
            return m_oper(m_lhs.self(),m_rhs.self(),i);
        }
        constexpr auto row() const noexcept -> size_t{return m_lhs.row();}
        constexpr auto col() const noexcept -> size_t{return m_rhs.col();}
        constexpr auto size() const noexcept -> size_t{return row() * col();}


        virtual ~BinaryExpression(){}
    };

    struct Addtion{
        template<typename Op1, typename Op2>
        constexpr auto operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const->
            std::common_type_t<typename Op1::Type,typename Op2::Type>{
                return lhs(i,j) + rhs(i,j);
            }
    };

    struct Subtraction{
        template<typename Op1, typename Op2>
        constexpr auto operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const->
        std::common_type_t<typename Op1::Type,typename Op2::Type>{
            return lhs(i,j) - rhs(i,j);
        }
    };

    struct Multipication{
        template<typename Op1, typename Op2>
        constexpr auto operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const->
        std::common_type_t<typename Op1::Type,typename Op2::Type>{
            std::common_type_t<typename Op1::Type,typename Op2::Type> sum = 0;
            for(size_t k = 0; k < lhs.col(); k++){
                sum += lhs(i,k) * rhs(k,j);
            }
            return sum;
        }
    };

    template<typename Op1, typename Op2>
    auto operator+(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> BinaryExpression<Addtion,Op1,Op2>{
        assert(lhs.self().row() == rhs.self().row());
        assert(lhs.self().col() == rhs.self().col());
        return {lhs.self(),rhs.self()};
    }

    template<typename Op1, typename Op2>
    auto operator-(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> BinaryExpression<Subtraction,Op1,Op2>{
        assert(lhs.self().row() == rhs.self().row());
        assert(lhs.self().col() == rhs.self().col());
        return {lhs.self(),rhs.self()};
    }

    template<typename Op1, typename Op2>
    auto operator*(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> BinaryExpression<Multipication,Op1,Op2>{
        assert(lhs.self().row() == rhs.self().col());
        return {lhs.self(),rhs.self()};
    }

    template<typename T>
    class Matrix : public BaseExpression<Matrix<T>>{
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

        using Type = T;

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
     * Copy Constructor
     * @param m type of Matrix
     */
        template<typename Expression>
        Matrix(BaseExpression<Expression> const& m);

    /**
     * Operator() Overloading
     * @param i type of size_t
     * @param j type of size_t
     */
        T& operator()(size_t i, size_t j);
        
        const T operator()(size_t i, size_t j) const;
    
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
        template<typename Expression>
        Matrix& operator=(BaseExpression<Expression> const &rhs);
    /**
     * Operator== Overloading
     * @return Matrix
     */
        template<typename Expression>
        Matrix& operator=(BaseExpression<Expression> &&rhs);

    /**
     * Operator+= Overloading
     * for addtion of two matrices
     * and assigns them
     * @return Matrix
     */
        template<typename Expression>
        Matrix& operator+=(BaseExpression<Expression> const &rhs);
    
    /**
     * Operator-= Overloading
     * for subtraction of two matrices
     * and assigns them
     * @return Matrix
     */
        template<typename Expression>
        Matrix& operator-=(BaseExpression<Expression> const &rhs);
    /**
     * Operator*= Overloading
     * for multipication of two matrices
     * and assigns them
     * @return Matrix
     */
        template<typename Expression>
        Matrix operator*=(BaseExpression<Expression> const &rhs);
    
    /**
     * Operator== Overloading
     * for comparision of two matrices
     * @return bool true if they are equal
     * otherwise false
     */
        template<typename Expression>
        bool operator==(BaseExpression<Expression> const &rhs);
    
    /**
     * Operator!= Overloading
     * for comparision of two matrices
     * @return bool true if they are not equal
     * otherwise false
     */
        template<typename Expression>
        bool operator!=(BaseExpression<Expression> const &rhs);

    /**
     * Destructor
     */
        ~Matrix(){}
    };

    template<typename T>
    template<typename Expression>
    Matrix<T>::Matrix(BaseExpression<Expression> const& m){
        Expression const& temp = m.self();
        m_data.resize(temp.row() * temp.col());
        m_row = temp.row();
        m_col = temp.col();
        for(auto i = 0 ; i < m_row ; i++){
            for(auto j = 0 ; j < m_col ; j++){
                this->operator()(i,j) = temp(i,j);
            }
        }
    }

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
    const T Matrix<T>::operator()(size_t i, size_t j) const{
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
    template<typename Expression>
    Matrix<T>& Matrix<T>::operator+=(BaseExpression<Expression> const &rhs){
        *this = (*this + rhs);
        return *this;
    }

    template<typename T>
    template<typename Expression>
    Matrix<T>& Matrix<T>::operator-=(BaseExpression<Expression> const &rhs){
        *this = (*this - rhs);
        return *this;
    }

    template<typename T>
    template<typename Expression>
    Matrix<T> Matrix<T>::operator*=(BaseExpression<Expression> const &rhs){
        Matrix<T> temp = *this * rhs;
        *this = temp;
        return *this;
    }

    template<typename T>
    template<typename Expression>
    Matrix<T>& Matrix<T>::operator=(BaseExpression<Expression> const &rhs){
        Expression const& n_rhs = rhs.self();
        this->m_col = n_rhs.col();
        this->m_row = n_rhs.row();
        m_data.resize(m_col*m_row);
        for(auto i = 0; i < row(); i++){
            for(auto j = 0; j < col(); j++){
                this->operator()(i,j) = n_rhs(i,j);
            }
        }
        return *this;
    }

    template<typename T>
    template<typename Expression>
    Matrix<T>& Matrix<T>::operator=(BaseExpression<Expression> &&rhs){
        Expression const& n_rhs = rhs.self();
        this->m_col = std::move(n_rhs.col());
        this->m_row = std::move(n_rhs.row());
        m_data.resize(m_col*m_row);
        for(auto i = 0; i < n_rhs.row(); i++){
            for(auto j = 0; j < n_rhs.col(); j++){
                this->operator()(i,j) = std::move(n_rhs(i,j));
            }
        }
        return *this;
    }

    template<typename T>
    template<typename Expression>
    bool Matrix<T>::operator==(BaseExpression<Expression> const& rhs){
        Expression const& n_rhs = rhs.self();
        if(this->m_col != n_rhs.col() && this->m_row != n_rhs.row()) return false;
        for(auto i = 0; i < n_rhs.row(); i++){
            for(auto j = 0; j < n_rhs.col(); j++){
                if( this->operator()(i,j) != n_rhs(i,j) ) return false;
            }
        }
        return true;
    }

    template<typename T>
    template<typename Expression>
    bool Matrix<T>::operator!=(BaseExpression<Expression> const& rhs){
        return !((*this) == rhs);
    }


}

#endif