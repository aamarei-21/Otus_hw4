#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <stdint.h>
#include <cstddef>

template <class>
struct is_containers : std::false_type {};

template <class T, class... Args>
struct is_containers<std::vector<T, Args...> >:std::true_type{};

template <class T, class... Args>
struct is_containers<std::list<T, Args...> >:std::true_type{};

template <class T>
constexpr bool is_containers_v = is_containers<T>::value;  //vector or list 

void print_ip(const std::string& arg) {
	std::cout << arg;
}

template<class T>
typename std::enable_if<is_containers_v<T>, void>::type print_ip(const T& arg) {
	// std::cout << "is_same_v = " << (std::is_same_v<std::string, T>) << std::endl;
	for(auto it = arg.begin(); it != arg.end(); ++it) {
		if (it != arg.begin()) 
			std::cout << ".";
		std::cout << *it;
	}
}

template<class T>
typename std::enable_if<std::is_integral<T>::value, void>::type print_ip(const T& arg) {
	if (arg == 0)
		std::cout << "0.0";
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
	int8_t param = -1;
	print_ip( param ); std::cout << std::endl;// 255
	print_ip( int16_t{0} ); std::cout << std::endl;// 0.0
	print_ip( int32_t{2130706433} ); std::cout << std::endl;// 127.0.0.1
	print_ip( int64_t{8875824491850138409} );std::cout << std::endl;// 123.45.67.89.101.112.131.41
	const std::string& str = "Hello, SFINAE!";
	print_ip(str); std::cout << std::endl;// Hello, SFINAE!
	print_ip( std::string{"Hello, World!"} ); std::cout << std::endl;// Hello, World!
	print_ip( std::vector<int>{100, 200, 300, 400} ); std::cout << std::endl;// 100.200.300.400
	print_ip( std::list<short>{400, 300, 200, 100} ); std::cout << std::endl;// 400.300.200.100
	// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0	
}