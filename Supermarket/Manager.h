#pragma once
#include "Worker.h"
#include <fstream>
class Manager : public Worker
{
	String identificationCode;

	bool isValidCodeFormat(const String& code) const;
	void saveCodeToFile(const String& code) const;

public:
	Manager(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password);

	bool setIdentificationCode(const String& code);
	const String& getIdentificationCode() const;
	bool authenticate(const String& code, const String& password) const;
};

