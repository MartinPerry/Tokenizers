#ifndef UTF8_UTILS_H
#define UTF8_UTILS_H

#include <string>


using StringUtf8 = std::u8string;

static inline StringUtf8 AsStringUtf8(const char* str)
{
	return StringUtf8(reinterpret_cast<const char8_t*>(str));
}

static inline StringUtf8 AsStringUtf8(const std::string& str)
{
	return StringUtf8(reinterpret_cast<const char8_t*>(str.c_str()), str.length());
}


#endif
