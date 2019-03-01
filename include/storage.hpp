#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <vector>
#include <array>

namespace sm{
    template<typename S>
    struct Storage;

    template<typename T>
    struct Storage< std::vector<T> >{
        using storage_type    = std::vector<T>;

        using size_type       = typename storage_type::size_type;
        using value_type      = typename storage_type::value_type;

        using reference       = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;

        using iterator        = typename storage_type::iterator;
        using const_iterator  = typename storage_type::const_iterator;
    };

    template<typename T,size_t N>
    struct Storage< std::array<T,N> >{
        using storage_type    = std::array<T,N>;

        using size_type       = typename storage_type::size_type;
        using value_type      = typename storage_type::value_type;

        using reference       = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;

        using iterator        = typename storage_type::iterator;
        using const_iterator  = typename storage_type::const_iterator;
    };
}

#endif // STORAGE_HPP
