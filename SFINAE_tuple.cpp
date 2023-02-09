#include <iostream>
#include <tuple>
#include <vector>
#include <utility>

template<class Tup, std::size_t... I>
void printElementTuple(const Tup& arg, std::index_sequence<I...>) {
    ((std::cout << (I == 0? "" : "." )<< std::get<I>(arg)), ...);
}

template<class ...Args>
void print_ip(const std::tuple<Args...> &arg) {
    printElementTuple(arg, std::index_sequence_for<Args...>{});
}

// template<class T, 
//     std::enable_if_t<std::is_same_v<std::tuple<>, T>, void> >
// void print_ip(T& arg) {
//     auto size = std::tuple_size<T>::value;
//     printTuple(arg);    
// }

int main () {
    auto tup = std::make_tuple(10, 20, 40);
    auto vec = std::vector<int>{10, 20};
    
    // printTuple(tup);
    print_ip( std::make_tuple(123, 456, 789, 0) ); 
    return 0;
}