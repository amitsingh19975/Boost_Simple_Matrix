#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP

#include "expression.hpp"

namespace sm_v3{

    struct Addition{
        template<typename Op1, typename Op2>
        friend constexpr auto operator+(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
            BinaryExpression<AdditionExpression, Op1, Op2>{
                assert(lhs.self().rows() == rhs.self().rows());
                assert(lhs.self().cols() == rhs.self().cols());
                return {lhs.self(),rhs.self()};
        }
    };

    struct Subtraction{
        template<typename Op1, typename Op2>
        friend constexpr auto operator-(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
            BinaryExpression<SubtractionExpression, Op1, Op2>{
                assert(lhs.self().rows() == rhs.self().rows());
                assert(lhs.self().cols() == rhs.self().cols());
                return {lhs.self(),rhs.self()};
        }
    };

    struct Multipication{
        template<typename Op1, typename Op2>
        friend constexpr auto operator*(BaseExpression<Op1> const& lhs, BaseExpression<Op2> const& rhs) -> 
            BinaryExpression<MultipicationExpression, Op1, Op2>{
                assert(lhs.self().rows() == rhs.self().cols());
                return {lhs.self(),rhs.self()};
        }
    };

    struct Operation_Add : public Addition{};
    struct Operation_Mul : public Multipication{};
    struct Operation_Sub : public Subtraction{};
    struct Operation_Add_Sub : public Addition, public Subtraction{};
    struct Operation_Add_Mul : public Addition, public Multipication{};
    struct Operation_Sub_Mul : public Subtraction, public Multipication{};
    struct Operation_Add_Sub_Mul : public Addition, public Subtraction, public Multipication{};
}

#endif // OPERATIONS_HPP
