#ifndef DYNAMIC_ENGINE_HPP
#define DYNAMIC_ENGINE_HPP

#include "storage.hpp"
#include <iostream>

/**
 * @brief This structure is used to get the size during runtime time
 * or dynamic dimension
 */

template<typename StoragePolicy>
struct DynamicEngine : public StoragePolicy{

    DynamicEngine() = default;
    
    DynamicEngine(DynamicEngine const& other):m_data(other.m_data),m_rows(other.m_rows),m_cols(other.m_cols){}
    DynamicEngine(DynamicEngine && other):m_data(std::move(other.m_data)),
        m_rows(std::move(other.m_rows)),m_cols(std::move(other.m_cols)){}
    
    DynamicEngine& operator=(DynamicEngine const& other){return *this = DynamicEngine(other);}
    DynamicEngine& operator=(DynamicEngine && other){
        return *this = DynamicEngine(std::move(other));
    }

    DynamicEngine(typename StoragePolicy::size_type rows, 
        typename StoragePolicy::size_type cols):m_data(rows * cols,0),m_rows(rows),m_cols(cols){}
    
    DynamicEngine(typename StoragePolicy::reference other,
        typename StoragePolicy::size_type rows, 
        typename StoragePolicy::size_type cols):m_data(other),m_rows(rows),m_cols(cols){}
    
    DynamicEngine(typename StoragePolicy::const_reference other,
        typename StoragePolicy::size_type rows, 
        typename StoragePolicy::size_type cols):m_data(other),m_rows(rows),m_cols(cols){}
        

protected:
    typename StoragePolicy::storage_type    m_data;
    typename StoragePolicy::size_type       m_rows{0};
    typename StoragePolicy::size_type       m_cols{0};
};

#endif // DYNAMIC_ENGINE_HPP
