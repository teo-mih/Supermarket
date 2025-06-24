#include "Worker.h"


Worker::Worker(short id, const String & name, const String & lastname, size_t phone_number, size_t age, const String & password)
	: id(id), name(name), lastname(lastname), phone_number(phone_number), age(age), password(password) {
}
short Worker::getId() const { return id; }
const String& Worker::getName() const { return name; }
const String& Worker::getLastname() const { return lastname; }
size_t Worker::getPhoneNumber() const { return phone_number; }
size_t Worker::getAge() const { return age; }
const String& Worker::getPassword() const { return password; }
void Worker::setPassword(const String& new_password) { password = new_password; }

