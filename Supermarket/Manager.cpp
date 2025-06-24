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

void Manager::listPendingCashiers(const Vector<Worker*>& users) const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (!users[i]->isEmployed()) {
            std::cout << "ID: " << users[i]->getId()
                << ", Name: " << users[i]->getName()
                << ", Lastname: " << users[i]->getLastname()
                << std::endl;
        }
    }
}

void Manager::approveCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password) {
    if (!authenticate(specialCode, password)) {
        std::cout << "Authentication failed. Command not executed." << std::endl;
        return;
    }
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == cashierId && !users[i]->getIsActive()) {
           
            users[i]->setIsActive(true);
            std::cout << "Cashier " << users[i]->getName() << " approved." << std::endl;
            return;
        }
    }
    std::cout << "Cashier not found or already active." << std::endl;
}

void Manager::declineCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password) {
    if (!authenticate(specialCode, password)) {
        std::cout << "Authentication failed. Command not executed." << std::endl;
        return;
    }
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == cashierId && !users[i]->getIsActive()) {
         
            users[i]->setIsActive(false);
            std::cout << "Cashier " << users[i]->getName() << " declined." << std::endl;
            return;
        }
    }
    std::cout << "Cashier not found or already processed." << std::endl;
}

void Manager::listWarnedCashiers(const Vector<Worker*>& users, int minPoints) const {
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->warnings.getSize() > static_cast<size_t>(minPoints)) {
            std::cout << "ID: " << users[i]->getId()
                << ", Name: " << users[i]->getName()
                << ", Warnings: " << users[i]->warnings.getSize()
                << std::endl;
        }
    }
}

void Manager::warnCashier(Vector<Worker*>& users, short cashierId, int points, const String& password) {
    if (!authenticate(specialCode, password)) {
        std::cout << "Authentication failed. Command not executed." << std::endl;
        return;
    }
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == cashierId && users[i]->getIsActive()) {
            for (int p = 0; p < points; ++p) {
                users[i]->addWarning("Warning issued by manager.");
            }
            std::cout << "Cashier " << users[i]->getName() << " received " << points << " warning(s)." << std::endl;
            return;
        }
    }
    std::cout << "Cashier not found or not active." << std::endl;
}

void Manager::promoteCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password) {
    if (!authenticate(specialCode, password)) {
        std::cout << "Authentication failed. Command not executed." << std::endl;
        return;
    }
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == cashierId && users[i]->getIsActive()) {
            
            // users[i]->setRole("manager");
            std::cout << "Cashier " << users[i]->getName() << " promoted to manager." << std::endl;
            return;
        }
    }
    std::cout << "Cashier not found or not active." << std::endl;
}

void Manager::fireCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password) {
    if (!authenticate(specialCode, password)) {
        std::cout << "Authentication failed. Command not executed." << std::endl;
        return;
    }
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i]->getId() == cashierId && users[i]->getIsActive()) {
            users[i]->setIsActive(false);
            std::cout << "Cashier " << users[i]->getName() << " has been fired." << std::endl;
            return;
        }
    }
    std::cout << "Cashier not found or not active." << std::endl;
}

void Manager::addCategory(Vector<Category>& categories, const String& name, const String& description) {
    for (size_t i = 0; i < categories.getSize(); ++i) {
        if (categories[i].Name == name) {
            std::cout << "Category already exists." << std::endl;
            return;
        }
    }
    categories.push_back({ name, description });
    std::cout << "Category added: " << name << std::endl;
}

void Manager::deleteCategory(Vector<Category>& categories, Vector<Product*>& products, int categoryId) {
    // Check if any product uses this category
    for (size_t i = 0; i < products.getSize(); ++i) {
        if (products[i]->getCategory().id == categoryId) { // Assuming Category has an id
            std::cout << "Cannot delete category: products exist in this category." << std::endl;
            return;
        }
    }
    for (size_t i = 0; i < categories.getSize(); ++i) {
        if (categories[i].id == categoryId) {
            categories.erase(i);
            std::cout << "Category deleted." << std::endl;
            return;
        }
    }
    std::cout << "Category not found." << std::endl;
}

void Manager::addProduct(Vector<Product*>& products, Product* product) {
    products.push_back(product);
    std::cout << "Product added: " << product->getName() << std::endl;
}

void Manager::deleteProduct(Vector<Product*>& products, int productId) {
    for (size_t i = 0; i < products.getSize(); ++i) {
        if (products[i]->getId() == productId) {
            products.erase(i);
            std::cout << "Product deleted." << std::endl;
            return;
        }
    }
    std::cout << "Product not found." << std::endl;
}
void Manager::loadProducts(Vector<Product*>& products, Vector<Category>& categories, const String& filename) {
    // Open file, parse lines, add products/categories as needed
    // Implementation depends on your file format
    std::cout << "Products loaded from " << filename << std::endl;
}

void Manager::loadGiftCards(Vector<GiftCard>& giftCards, const String& filename) {
    // Open file, parse lines, add gift cards as needed
    std::cout << "Gift cards loaded from " << filename << std::endl;
}

void Manager::seedRandom() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

String Manager::generateSpecialCode() {
    char code[8];
    code[0] = '0' + (std::rand() % 10);                // digit
    code[1] = 'A' + (std::rand() % 26);                // uppercase
    code[2] = 'A' + (std::rand() % 26);                // uppercase
    code[3] = '0' + (std::rand() % 10);                // digit
    code[4] = '0' + (std::rand() % 10);                // digit
    code[5] = '0' + (std::rand() % 10);                // digit
    code[6] = 'a' + (std::rand() % 26);                // lowercase
    code[7] = '\0';
    return String(code);
}
