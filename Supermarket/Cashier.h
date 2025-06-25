#pragma once
#include "Worker.h"
#include "Vector.hpp"

enum WarningSeverity {
    Low = 100,
    Medium = 200,
    High = 300
};

struct Warning {
    String sender;
    String description;
	WarningSeverity severity;
};

class Cashier : public Worker
{
private:
	size_t transactionsCount;
    Vector<Warning> warnings;
public:
    Cashier(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password) {}
    void addWarning(const String& sender, const String& description, WarningSeverity severity);
    const Vector<Warning>& getWarnings() const;

};

