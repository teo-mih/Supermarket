#pragma once
#include <iostream>
#pragma warning (disable: 4996)
class String
{
	char* str;
	int length;
	size_t capacity;

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int size) const;
	explicit String(size_t newSize);
	void resize(size_t newCapacity);
	void copyFrom(const String& other);
	void free();

public:
	String();
	String(const char* str);
	String(const String& other);
	String& operator=(const String& other);
	const char* c_str() const;
	const char* to_str() const;
	size_t getSize() const;
	size_t getCapacity() const;

	const char& operator[](size_t idx) const;
	char& operator[](size_t idx);

	String& operator+=(const String& other);
	String& operator+=(const char& c);

	friend String operator+(const String& lhs, const String& rhs);

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);

	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);

	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);

	
	friend std::ostream& operator<<(std::ostream& os, const String& s);
	friend std::istream& operator>>(std::istream& is, String& other);

	~String();

};