#pragma once

#include <tuple>
#include <iostream>

template<int Index, typename Ch, typename Tr, typename... Args>
class TuplePrinter {
public:
    static void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
        TuplePrinter<Index - 1, Ch, Tr, Args...>::printTuple(os, t);
        os << std::get<Index>(t) << " ";
    }
};

template<typename Ch, typename Tr, typename... Args>
class TuplePrinter<0, Ch, Tr, Args...> {
public:
    static void printTuple(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
        os << std::get<0>(t) << " ";
    }
};

template<typename Ch, typename Tr, typename... Args>
void operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
    TuplePrinter<sizeof...(Args) - 1, Ch, Tr, Args...>::printTuple(os, t);
}