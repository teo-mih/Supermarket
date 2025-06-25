#include "Manager.h"


Manager::Manager(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password)
    : Worker(Role::Manager, id, name, lastname, phone_number, age, password) {}



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
        if (users[i]->getWarnings().getSize() > static_cast<size_t>(minPoints)) {
            std::cout << "ID: " << users[i]->getId()
                << ", Name: " << users[i]->getName()
                << ", Warnings: " << users[i]->getWarnings().getSize()
                << std::endl;
        }
    }
}

void Manager::warnCashier(Vector<Worker*>& users, short cashierId, int points, const String& specialCode, const String& password) {
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
        if (users[i]->getId() == cashierId && users[i]->getIsActive() && users[i]->getRole() == Role::Cashier) {
            users[i]->setRole(Role::Manager);
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
        if (products[i]->getCategory().id == categoryId) {
            std::cout << "Cannot delete category: products exist in this category." << std::endl;
            return;
        }
    }
    for (size_t i = 0; i < categories.getSize(); ++i) {
        if (categories[i].id == categoryId) {
            categories.remove(i);
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
            products.remove(i);
            std::cout << "Product deleted." << std::endl;
            return;
        }
    }
    std::cout << "Product not found." << std::endl;
}
void Manager::loadProducts(Vector<Product*>& products, Vector<Category>& categories, const String& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    char line[256];
    while (file.getline(line, sizeof(line))) {
        // Parse line
        char* token = std::strtok(line, ";");
        if (!token) continue;
        int id = std::atoi(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        String name(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        String categoryName(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        String categoryDesc(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        double price = std::atof(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        int quantity = std::atoi(token);

        // Check if category exists
        int catIndex = -1;
        for (size_t i = 0; i < categories.getSize(); ++i) {
            if (categories[i].Name == categoryName) {
                catIndex = static_cast<int>(i);
                break;
            }
        }
        if (catIndex == -1) {
            categories.push_back({ categoryName, categoryDesc });
            catIndex = static_cast<int>(categories.getSize()) - 1;
        }
        Category& cat = categories[catIndex];

        // Create and add product
        Product* prod = new Product(name, cat, price, id, quantity);
        products.push_back(prod);
    }

    file.close();
    std::cout << "Products loaded from " << filename << std::endl;
}


void Manager::loadGiftCards(Vector<GiftCard*>& giftCards, const String& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return;
    }

    char line[256];
    while (file.getline(line, sizeof(line))) {
        char* token = std::strtok(line, ";");
        if (!token) continue;
        String type(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        String code(token);

        token = std::strtok(nullptr, ";");
        if (!token) continue;
        double discount = std::atof(token);

        if (type == "single") {
            token = std::strtok(nullptr, ";");
            if (!token) continue;
            String category(token);
            giftCards.push_back(new SingleCategoryGiftCard(code, discount, category));
        }
        else if (type == "multi") {
            Vector<String> categories;
            while ((token = std::strtok(nullptr, ";")) != nullptr) {
                categories.push_back(String(token));
            }
            giftCards.push_back(new MultipleCategoryGiftCard(code, discount, categories));
        }
        else if (type == "all") {
            giftCards.push_back(new AllProductsGiftCard(code, discount));
        }
    }

    file.close();
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
