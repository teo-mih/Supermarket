#pragma once
#include "String.h"
#include "Vector.hpp"
enum class Role { Cashier, Manager };

class Worker
{
	short id;
	String name;
	String lastname;
	size_t phone_number;
	size_t age;
	String password;
	bool isActive;
	int transactionCount = 0;
	Vector<String> warnings;
	Role role;
public:
	Worker(Role role, short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password);

	Role getRole() const;
	void setRole(Role newRole);
	short getId() const;
	const String& getName() const;
	const String& getLastname() const;
	size_t getPhoneNumber() const;
	size_t getAge() const;
	const String& getPassword() const;
	void setPassword(const String& new_password);
	void addWarning(const String& warning);
	void clearEarliestWarning();
	void incrementTransactionCount();
	int getTransactionCount() const;
	bool getIsActive() const;
	void setIsActive(bool active);

	void leave();
	bool isEmployed() const;
};


