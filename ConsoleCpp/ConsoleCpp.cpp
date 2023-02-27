#include <iostream>

#ifdef _WIN32 
#include <Windows.h>
#define SET_CONSOLE_UTF8 SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8); //Set console output to UTF-8.Visual C++ code on Windows.
#endif // _WIN32 


#if defined(__cpp_char8_t) | defined(__cpp_lib_char8_t)

//Operator <<
std::ostream& operator<<(std::ostream& os, const std::u8string& str)
{
	os << reinterpret_cast<const char*>(str.data());
	return os;
}

//Convert u8string to string.
std::string ToString(const std::u8string& s) {
	return std::string(s.begin(), s.end());
}

std::u8string Tou8String(const std::string& s) {
	return std::u8string(s.begin(), s.end());
}

//const char8_t* literal to string. Operator ""_s
static inline std::string operator"" _s(const char8_t* value, size_t size) {
	static std::string x(reinterpret_cast<const char*>(value), size);
	return x;
}

#endif


using namespace std::string_literals;// operator ""s

int main() {
#ifdef _WIN32
	SET_CONSOLE_UTF8
#endif

		std::u8string u8String = u8"😋😋😋😋"s;// u8string literal.
	std::string str = u8"😋😋😋😋"_s; //Operator "_s". Convert utf8 literal(const char8_t*) to std::string. 

	std::cout << "string              " << str << std::endl; //Using operator << for std::string
	std::cout << "u8string -> string  " << ToString(u8String) << std::endl; //Using function ToString(u8string) -> string
	std::cout << "u8string            " << u8String << std::endl; //Using operator << for std::u8string.
	std::cout << "string -> u8string  " << Tou8String(str) << std::endl; //Using function Tou8String(string) -> u8string
	std::cin.get();
	return 0;
}