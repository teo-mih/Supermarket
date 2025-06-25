#include "Worker.h"


Worker::Worker(Role role, short id, const String & name, const String & lastname, size_t phone_number, size_t age, const String & password)
	: role(role), id(id), name(name), lastname(lastname), phone_number(phone_number), age(age), password(password), isActive(true) {
}
short Worker::getId() const { return id; }
const String& Worker::getName() const { return name; }
const String& Worker::getLastname() const { return lastname; }
size_t Worker::getPhoneNumber() const { return phone_number; }
size_t Worker::getAge() const { return age; }
const String& Worker::getPassword() const { return password; }
void Worker::setPassword(const String& new_password) { password = new_password; }

void Worker::addWarning(const String& warning) {
    warnings.push_back(warning);
}

short Worker::GenerateId() {
    return 100 + (std::rand() % 900); // Generates a random number between 100 and 999
}

Role Worker::getRole() const { return role; }
void Worker::setRole(Role newRole) { role = newRole; }


const Vector<String>& Worker::getWarnings() const { return warnings; }

void Worker::clearEarliestWarning() {
    if (warnings.getSize() > 0) {
        warnings.remove(0); // Remove the first warning
    }
}

void Worker::incrementTransactionCount() {
    ++transactionCount;
}

int Worker::getTransactionCount() const {
    return transactionCount;
}

void Worker::leave() {
    isActive = false;
}

bool Worker::isEmployed() const {
    return isActive;
}

bool Worker::getIsActive() const {
    return isActive;
}
void Worker::setIsActive(bool active) {
    isActive = active;
}
