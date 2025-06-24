#include "Manager.h"


Manager::Manager(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password)
    : Worker(id, name, lastname, phone_number, age, password) {}

bool Manager::isValidCodeFormat(const String& code) const {
    if (code.getSize() != 7) return false;
    return isdigit(code[0]) &&
           isupper(code[1]) &&
           isupper(code[2]) &&
           isdigit(code[3]) &&
           isdigit(code[4]) &&
           isdigit(code[5]) &&
           islower(code[6]);
}

void Manager::saveCodeToFile(const String& code) const {
   String fileName = identificationCode + code + ".txt"; 
   std::ofstream file(fileName.c_str());
   if (file.is_open()) {
       file << code;
       file.close();
   }
}

bool Manager::setIdentificationCode(const String& code) {
    if (!isValidCodeFormat(code)) return false;
    identificationCode = code;
    saveCodeToFile(code);
    return true;
}

const String& Manager::getIdentificationCode() const {
    return identificationCode;
}

bool Manager::authenticate(const String& code, const String& password) const {
    return identificationCode == code && getPassword() == password;
}
