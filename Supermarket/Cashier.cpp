#include "Cashier.h"

void Cashier::addWarning(const String& sender, const String& description, WarningSeverity severity) {
	Warning warning{ sender, description, severity };
	warnings.push_back(std::move(warning));
}

const Vector<Warning>& Cashier::getWarnings() const {
	return warnings;
}