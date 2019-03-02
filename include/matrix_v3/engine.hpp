#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "dynamic_engine.hpp"
#include "static_engine.hpp"
#include <iostream>

template<typename Engine_t>
struct Engine : public Engine_t{
    using Engine_t::m_data;
    using Engine_t::m_rows;
    using Engine_t::m_cols;
    
    Engine():Engine_t(){};
    
    Engine(Engine const& other):Engine_t(other){}
    
    Engine(Engine && other):Engine_t(std::move(other)){}
    
    Engine& operator=(Engine const& other){return *this = Engine(other);}
    Engine& operator=(Engine && other){
        return *this = Engine(std::move(other));
    }
    
    Engine(typename Engine_t::size_type rows, 
        typename Engine_t::size_type cols):Engine_t(rows, cols){}

    Engine(typename Engine_t::reference other,
        typename Engine_t::size_type rows, 
        typename Engine_t::size_type cols):Engine_t(other, rows, cols){}
    
    Engine(typename Engine_t::const_reference other,
        typename Engine_t::size_type rows, 
        typename Engine_t::size_type cols):Engine_t(other, rows, cols){}

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

    constexpr friend std::ostream &operator<<(std::ostream &os, Engine const &m){
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

    constexpr typename Engine_t::iterator begin(){
        return m_data.begin();
    }

    constexpr typename Engine_t::iterator end(){
        return m_data.end();
    }

    constexpr typename Engine_t::const_iterator cbegin(){
        return m_data.cbegin();
    }

    constexpr typename Engine_t::const_iterator cend(){
        return m_data.cend();
    }

    constexpr typename Engine_t::reverse_iterator rbegin(){
        return m_data.rbegin();
    }

    constexpr typename Engine_t::reverse_iterator rend(){
        return m_data.rend();
    }

    constexpr typename Engine_t::const_reverse_iterator crbegin(){
        return m_data.crbegin();
    }

    constexpr typename Engine_t::const_reverse_iterator crend(){
        return m_data.crend();
    }
};


#endif // ENGINE_HPP
