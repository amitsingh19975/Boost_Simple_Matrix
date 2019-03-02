#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <type_traits>
#include <iostream>
namespace sm_v3{
    template<typename Expression>
    struct BaseExpression{
        constexpr auto self() const -> Expression const&{
            return static_cast<Expression const&>(*this);
        }
    };

    template<
        typename Operation, 
        typename Op1, 
        typename Op2 >
    struct BinaryExpression : public BaseExpression< BinaryExpression< Operation , Op1, Op2 > >{
        Op1 const& m_lhs;
        Op2 const& m_rhs;
        size_t m_rows;
        size_t m_cols;
        Operation m_oper;
        using Type = std::common_type_t<typename Op1::Type ,typename Op2::Type>;

        BinaryExpression(Op1 const& op1, Op2 const& op2): m_lhs(op1),m_rhs(op2)
            ,m_rows(op1.rows()),m_cols(op1.cols()){}

        constexpr auto operator()(size_t i, size_t j) const{
            return m_oper(m_lhs.self(),m_rhs.self(),i,j);
        }

        /**
         * @return rows
         */
        constexpr auto rows() const -> size_t{return m_rows;}
        
        /**
         * @return cols
         */
        constexpr auto cols() const -> size_t{return m_cols;}
        
        /**
         * @return size of vector
         */
        constexpr auto size() const noexcept -> size_t{return rows() * cols();}
    };

    struct AdditionExpression{
        template<typename Op1, typename Op2>
        constexpr decltype(auto) operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const{
            return lhs(i,j) + rhs(i,j);
        }
    };

    struct SubtractionExpression{
        template<typename Op1, typename Op2>
        constexpr decltype(auto) operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const{
            return lhs(i,j) - rhs(i,j);
        }
    };

    struct MultipicationExpression{
        template<typename Op1, typename Op2>
        constexpr decltype(auto) operator()(Op1 const& lhs, Op2 const& rhs, size_t i, size_t j) const{
            std::common_type_t<typename Op1::Type,typename Op2::Type> sum = 0;
            for(auto k = 0; k < lhs.cols(); k++){
                sum += lhs(i,k) * rhs(k,j);
            }
            return sum;
        }
    };

    // template<typename Op1, typename Op2>
    // constexpr auto operator+(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
    //     BinaryExpression<AdditionExpression, Op1, Op2>{
    //         assert(lhs.self().rows() == rhs.self().rows());
    //         assert(lhs.self().cols() == rhs.self().cols());
    //         return {lhs.self(),rhs.self()};
    // }

    // template<typename Op1, typename Op2>
    // constexpr auto operator-(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
    //     BinaryExpression<SubtractionExpression, Op1, Op2>{
    //         assert(lhs.self().rows() == rhs.self().rows());
    //         assert(lhs.self().cols() == rhs.self().cols());
    //         return {lhs.self(),rhs.self()};
    // }

    // template<typename Op1, typename Op2>
    // constexpr auto operator*(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
    //     BinaryExpression<MultipicationExpression, Op1, Op2>{
    //         assert(lhs.self().rows() == rhs.self().cols());
    //         return {lhs.self(),rhs.self()};
    // }

}

#endif // EXPRESSION_HPP
