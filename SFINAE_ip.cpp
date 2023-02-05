#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <stdint.h>
#include <cstddef>

template <class, class = void>
struct is_containers : std::true_type {};

template <class T>
struct is_containers<T, std::enable_if_t<std::iterator_traits<typename T::iterator>::value_type > >:std::false_type{};

template <class T>
constexpr bool is_containers_v = is_containers<T>::value;  //vector or list 

template<class T>
typename std::enable_if<is_containers_v<T> && !std::is_integral_v<T>, void>::type print_ip(const T& arg) {
	for(auto it = arg.begin(); it != arg.end(); ++it) {
		if (it != arg.begin()) 
			std::cout << ".";
		std::cout << *it;
	}
	std::cout << std::endl;
	
}

template<class T>
typename std::enable_if<std::is_integral<T>::value, void>::type print_ip(const T& arg) {
	if (arg == 0)
		std::cout << "0.0\n";
	else {
		std::vector<int> ip;
		auto tempArg = std::make_unsigned_t<T>(arg);// & ~(1 << (sizeof(T) * 8 - 1)));		
		while (tempArg) {						
			auto lowByte = tempArg & 0xff;
			ip.insert(ip.begin(), lowByte);
			tempArg >>= 8;
		}
		print_ip(ip);
	}
}

int main () {
	
	print_ip( int8_t{-1} ); // 255
	print_ip( int16_t{0} ); // 0.0
	print_ip( int32_t{2130706433} ); // 127.0.0.1
	print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
	print_ip( std::string{"Hello, World!"} ); // Hello, World!
	print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
	print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
	// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0	
}