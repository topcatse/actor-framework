#ifndef LIBCPPA_UTIL_TYPE_LIST_HPP
#define LIBCPPA_UTIL_TYPE_LIST_HPP

#include <typeinfo>

#include "cppa/util/void_type.hpp"

namespace cppa {

// forward declarations
class uniform_type_info;
const uniform_type_info* uniform_typeid(const std::type_info&);

} // namespace cppa

namespace cppa { namespace util {

template<typename... Types> struct type_list;

template<>
struct type_list<>
{
    typedef void_type head_type;
    typedef type_list<> tail_type;
    static const size_t size = 0;
};

template<typename Head, typename... Tail>
struct type_list<Head, Tail...>
{

    typedef Head head_type;

    typedef type_list<Tail...> tail_type;

    static const size_t size =  sizeof...(Tail) + 1;

    type_list()
    {
        init<type_list>(m_arr);
    }

    inline const uniform_type_info& at(size_t pos) const
    {
        return *m_arr[pos];
    }

    template<typename TypeList>
    static void init(const uniform_type_info** what)
    {
        what[0] = uniform_typeid(typeid(typename TypeList::head_type));
        if (TypeList::size > 1)
        {
            ++what;
            init<typename TypeList::tail_type>(what);
        }
    }

 private:

    const uniform_type_info* m_arr[size];

};

} } // namespace cppa::util

#endif // LIBCPPA_UTIL_TYPE_LIST_HPP
