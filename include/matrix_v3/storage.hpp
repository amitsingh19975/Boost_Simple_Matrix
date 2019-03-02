#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <vector>
#include <array>
#include <memory>

namespace sm_v3{
    template<typename S>
    struct Storage;

    template<typename T, typename A>
    struct Storage< std::vector<T,A> >{
        using storage_type      = std::vector<T,A>;
        using size_type       = typename storage_type::size_type;
        using difference_type = typename storage_type::difference_type;
        using value_type      = typename storage_type::value_type;

        using reference       = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;

        using pointer         = typename storage_type::pointer;
        using const_pointer   = typename storage_type::const_pointer;

        using iterator        = typename storage_type::iterator;
        using const_iterator  = typename storage_type::const_iterator;

        using reverse_iterator        = typename storage_type::reverse_iterator;
        using const_reverse_iterator  = typename storage_type::const_reverse_iterator;

        template<class U>
        using rebind = std::vector<U, typename std::allocator_traits<A>::template rebind_alloc<U>>;
    };

    template<typename T,size_t N>
    struct Storage< std::array<T,N> >{
        using storage_type    = std::array<T,N>;

        using size_type       = typename storage_type::size_type;
        using difference_type = typename storage_type::difference_type;
        using value_type      = typename storage_type::value_type;

        using reference       = typename storage_type::reference;
        using const_reference = typename storage_type::const_reference;

        using pointer         = typename storage_type::pointer;
        using const_pointer   = typename storage_type::const_pointer;

        using iterator        = typename storage_type::iterator;
        using const_iterator  = typename storage_type::const_iterator;

        using reverse_iterator        = typename storage_type::reverse_iterator;
        using const_reverse_iterator  = typename storage_type::const_reverse_iterator;

        template<class U>
	    using rebind = std::array<U,N>;
    };
}

#endif // STORAGE_HPP
