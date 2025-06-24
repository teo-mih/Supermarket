#include "String.h"

String::String() : String("")
{
}

//String::String(const String& other) {
//	copyFrom(other);
//}
String::String(size_t newSize) {
	capacity = allocateCapacity(newSize);
	str = new char[capacity];
	length = newSize;
	str[length] = '\0';
}
// Copy constructor
String::String(const String& other) {
	copyFrom(other);
}
String::String(const char* str) : length(strlen(str)), capacity(allocateCapacity(length))
{
	this->str = new char[this->capacity];
	strcpy(this->str, str);
}

const char* String::c_str() const
{
	return this->str;
}

const char* String::to_str() const {
	return str;
}

size_t String::getSize() const
{
	return this->length;
}

size_t String::getCapacity() const
{
	return this->capacity;
}

unsigned int String::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}
unsigned int String::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void String::resize(size_t newCapacity)
{
	this->capacity = newCapacity;

	char* newstr = new char[this->capacity];
	strcpy(newstr, this->str);

	delete[] this->str;
	this->str = newstr;
}

void String::copyFrom(const String& other)
{
	this->length = other.length;
	this->capacity = other.capacity;

	this->str = new char[strlen(other.str) + 1];
	strcpy(this->str, other.str);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& s)
{
	os << s.str;
	return os;
}

std::istream& operator>>(std::istream& is, String& other)
{
	char buff[1000];
	is >> buff;

	size_t buffLength = strlen(buff);

	if (buffLength >= other.getCapacity())
	{
		other.resize(other.allocateCapacity(buffLength));
	}

	strcpy(other.str, buff);

	other.length = buffLength;

	return is;
}

const char& String::operator[](size_t idx) const
{
	return this->str[idx];
}

char& String::operator[](size_t idx)
{
	return this->str[idx];
}

String& String::operator+=(const String& other)
{
	if (getSize() + other.getSize() >= getCapacity())
	{
		resize(allocateCapacity(getSize() + other.getSize()));
	}

	strncat(this->str, other.str, other.getSize());

	this->length += other.getSize();

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) != 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) >= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.str, rhs.str) > 0;
}

void String::free()
{
	delete[] this->str;

	this->str = nullptr;
	this->length = this->capacity = 0;
}
String::~String()
{
	free();
}
