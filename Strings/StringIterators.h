#ifndef STRING_ITERATORS_H
#define STRING_ITERATORS_H

#include <string>
#include <string_view>
#include <limits>
#include <array>


#include "../3rdParty/utf8/utf8.h"

/// <summary>
/// Input string is unicode string
/// Will return uint32_t -> unicode code point
/// 
/// Example:
/// std::u8string testUnicode = u8"ABC"
///		u8"\u010D"          // č
///		u8"\u017E"          // ž
///		u8"\u03A9"          // "omega"
///		u8"\u6C34"          // "chinese"
///		u8"\U0001F600"      // :)
///		u8"\U0001F63A"      // "cat face"
///		u8"a\u0301";        // a + combining acute
/// 
/// </summary>
struct CustomU8Iterator
{
	static inline char32_t DONE = std::numeric_limits<uint32_t>::max();

	CustomU8Iterator(const std::u8string& str) :
		CustomU8Iterator(std::u8string_view(str))		
	{
	}

	CustomU8Iterator(const std::u8string_view& view) :
		itStart(view.data()),
		it(view.data()),
		itEnd(view.data() + view.size())
	{
	}

	CustomU8Iterator(const std::string_view& view) :
		itStart((char8_t*)view.data()),
		it((char8_t*)view.data()),
		itEnd((char8_t*)view.data() + view.size())
	{
	}

	CustomU8Iterator(const CustomU8Iterator& other) :		
		it(other.it),
		itStart(other.itStart),
		itEnd(other.itEnd)
	{
	}

	void SetOffsetFromStart(uint32_t offset) 
	{ 
		it = itStart; 
		this->SetOffsetFromCurrent(offset);
	}
	void SetOffsetFromCurrent(uint32_t offset) 
	{ 
		for (uint32_t i = 0; i < offset; i++)
		{
			utf8::unchecked::next(it);
		}
	}

	char32_t GetFirst()
	{ 
		it = itStart;
		return utf8::unchecked::peek_next(it); 
	}
	char32_t GetCurrent()
	{ 
		if (this->HasNext() == false)
		{
			return CustomU8Iterator::DONE;
		}
		return utf8::unchecked::peek_next(it); 
	}

	char32_t GetNext()
	{ 
		if (this->HasNext() == false)
		{
			return CustomU8Iterator::DONE;
		}
		utf8::unchecked::next(it); 

		return this->GetCurrent();
	}
	char32_t GetCurrentAndAdvance()
	{
		if (this->HasNext() == false)
		{
			return CustomU8Iterator::DONE;
		}
		char32_t c = utf8::unchecked::next(it);
		return c;
	}
	bool HasNext() { return it < itEnd; }

protected:
		
	const char8_t* it;
	const char8_t* itEnd;
	const char8_t* itStart;
};


/*
Unicode -> UTF8
Example: "č"
Unicode: U+010D
UTF8 bytes: [0xC4, 0x8D] -> [196, 141]
*/

#endif
