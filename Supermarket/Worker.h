#pragma once
#include "String.h"

class Worker
{
	short id;
	String name;
	String lastname;
	size_t phone_number;
	size_t age;
	String password;
public:
	Worker(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password);
	short getId() const;
	const String& getName() const;
	const String& getLastname() const;
	size_t getPhoneNumber() const;
	size_t getAge() const;
	const String& getPassword() const;
	void setPassword(const String& new_password);
};


