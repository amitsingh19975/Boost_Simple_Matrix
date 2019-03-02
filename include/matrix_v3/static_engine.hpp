#ifndef STATIC_ENGINE_HPP
#define STATIC_ENGINE_HPP

#include "storage.hpp"
#include <iostream>

template<size_t matrix_rows, size_t matrix_cols, typename StoragePolicy>
struct StaticEngine : public StoragePolicy{

    StaticEngine():m_rows(matrix_rows),m_cols(matrix_cols){
        if constexpr(!std::is_array_v<typename StoragePolicy::storage_type>){
            m_data.resize(m_rows * m_cols,0);
        }
    }
    
    StaticEngine(StaticEngine const& other):m_data(other.m_data),
        m_rows(other.m_rows),m_cols(other.m_cols){
        }
    
    StaticEngine(StaticEngine && other):m_data(std::move(other.m_data)),
        m_rows(std::move(other.m_rows)),m_cols(std::move(other.m_cols)){
        }
    
    StaticEngine(typename StoragePolicy::size_type rows, 
        typename StoragePolicy::size_type cols){
            if constexpr(std::is_array_v<typename StoragePolicy::storage_type>){
                assert(m_rows == rows);
                assert(m_cols == cols);
            }else{
                m_rows = rows;
                m_cols = cols;
                m_data.resize(m_cols * m_rows);
            }
        }

    StaticEngine& operator=(StaticEngine const& other){
        return *this = StaticEngine(other);
    }
    StaticEngine& operator=(StaticEngine && other){
        return *this = StaticEngine(std::move(other));
    }
    
    StaticEngine(typename StoragePolicy::reference other){
        if constexpr(std::is_array_v<typename StoragePolicy::storage_type>){
            assert(m_rows == other.m_rows);
            assert(m_cols == other.m_cols);
        }else{
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_data = other;
        }
    }
    
    StaticEngine(typename StoragePolicy::const_reference other){
        if constexpr(std::is_array_v<typename StoragePolicy::storage_type>){
            assert(m_rows == other.m_rows);
            assert(m_cols == other.m_cols);
        }else{
            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_data = other;
        }
    }

protected:
    typename StoragePolicy::storage_type    m_data;
    typename StoragePolicy::size_type       m_rows{matrix_rows};
    typename StoragePolicy::size_type       m_cols{matrix_cols};
};



#endif // STATIC_ENGINE_HPP
