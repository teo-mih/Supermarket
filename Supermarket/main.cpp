#include "SuperMarketSystem.h"
#include <iostream>

Vector<Worker*> pendingCashiers;

Vector<String> split(const String& str) {
    Vector<String> tokens;
    size_t len = str.getSize();
    size_t i = 0;
    // First token: command before first '<'
    while (i < len && str[i] != '<') {
        ++i;
    }
    if (i > 0) {
        String cmd;
        for (size_t j = 0; j < i; ++j) {
            cmd += str[j];
        }
        // Remove trailing spaces if any
        size_t end = cmd.getSize();
        while (end > 0 && cmd[end - 1] == ' ') --end;
        if (end > 0) {
            String trimmed;
            for (size_t j = 0; j < end; ++j) trimmed += cmd[j];
            tokens.push_back(trimmed);
        }
    }
    // Parse tokens between '<' and '>'
    while (i < len) {
        // Find next '<'
        while (i < len && str[i] != '<') ++i;
        if (i >= len) break;
        ++i; // skip '<'
        size_t start = i;
        while (i < len && str[i] != '>') ++i;
        if (i > start) {
            String token;
            for (size_t j = start; j < i; ++j) token += str[j];
            tokens.push_back(token);
        }
        ++i; // skip '>'
    }
    return tokens;
}

void printWelcome() {
    std::cout << "Welcome to FMI Supermarket Management System 2024-2025!\n";
    std::cout << "Please choose an action:\n";
}

void mainLoop() {
    String input;
    while (true) {
        std::cout << "> ";
        char buffer[1024];
        std::cin.getline(buffer, 1024);
        input = String(buffer);

        if (input == "exit" || input == "quit") break;

        Vector<String> tokens = split(input);
        if (tokens.getSize() == 0) continue;

        // REGISTER MANAGER
        if (tokens[0] == "register" && tokens.getSize() >= 7) {
            if (tokens[1] == "manager") {
                // tokens[2] = first name, tokens[3] = last name, tokens[4] = phone, tokens[5] = age, tokens[6] = password
                // Example: registerManager(tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);
                short id = Worker::GenerateId();
                String name = tokens[2];
                String lastname = tokens[3];
                size_t phone = static_cast<size_t>(std::stoull(tokens[4].c_str()));
                size_t age = static_cast<size_t>(std::stoul(tokens[5].c_str()));
                String password = tokens[6];

                Manager manager(id, name, lastname, phone, age, password);
                String specialCode = manager.generateSpecialCode();
                manager.setIdentificationCode(specialCode);

                std::cout << "Manager registered successfully!\n";
                std::cout << "Special code: " << specialCode << "\n";
                std::cout << "Code: " << id << "_" << specialCode << ".txt\n";
            }
            else if (tokens[1] == "cashier") {
                // tokens[2] = first name, tokens[3] = last name, tokens[4] = phone, tokens[5] = age, tokens[6] = password
                // Example: registerCashier(tokens[2], tokens[3], tokens[4], tokens[5], tokens[6]);
                short id = Worker::GenerateId();
                String name = tokens[2];
                String lastname = tokens[3];
                size_t phone = static_cast<size_t>(std::stoull(tokens[4].c_str()));
                size_t age = static_cast<size_t>(std::stoul(tokens[5].c_str()));
                String password = tokens[6];

                // Create a Worker with Role::Cashier and inactive status
                Cashier* cashier = new Cashier(id, name, lastname, phone, age, password);
                cashier->setIsActive(false);
                pendingCashiers.push_back(cashier);
                std::cout << "Cashier registration pending approval from a manager.\n";
                std::cout << "Cashier ID: " << id << "\n";
            }
        }
        // LOGIN
        else if (tokens[0] == "login" && tokens.getSize() >= 3) {
            // tokens[1] = id, tokens[2] = password
            // Example: login(tokens[1], tokens[2]);
            std::cout << "User with ID: " << tokens[1] << " has been logged into the system!\n";
        }
        // APPROVE CASHIER
        else if (tokens[0] == "approve" && tokens.getSize() >= 3) {
            // tokens[1] = cashier id, tokens[2] = special code
            // Example: approveCashier(tokens[1], tokens[2]);
            std::cout << "Cashier approved successfully!\n";
        }
        // ADD CATEGORY
        else if (tokens[0] == "add-category" && tokens.getSize() >= 2) {
            // tokens[1] = category name, tokens[2] = description (optional)
            std::cout << "Category \"" << tokens[1] << "\" added successfully!\n";
        }
        // ADD PRODUCT BY WEIGHT
        else if (tokens[0] == "add-product" && tokens.getSize() >= 2 && tokens[1] == "product_by_weight") {
            // Prompt for additional info if needed
            std::cout << "Enter product name: ";
            char nameBuf[256];
            std::cin.getline(nameBuf, 256);
            String name(nameBuf);

            std::cout << "Enter product category: ";
            char catBuf[256];
            std::cin.getline(catBuf, 256);
            String category(catBuf);

            std::cout << "Enter price per kg: ";
            double price;
            std::cin >> price;
            std::cin.ignore();

            std::cout << "Enter quantity (kg): ";
            int quantity;
            std::cin >> quantity;
            std::cin.ignore();

            // Example: addProductByWeight(name, category, price, quantity);
            std::cout << "Product \"" << name << "\" added successfully under category \"" << category << "\"\n";
        }
        // ADD PRODUCT BY UNIT
        else if (tokens[0] == "add-product" && tokens.getSize() >= 2 && tokens[1] == "product_by_unit") {
            std::cout << "Enter product name: ";
            char nameBuf[256];
            std::cin.getline(nameBuf, 256);
            String name(nameBuf);

            std::cout << "Enter product category: ";
            char catBuf[256];
            std::cin.getline(catBuf, 256);
            String category(catBuf);

            std::cout << "Enter price per unit: ";
            double price;
            std::cin >> price;
            std::cin.ignore();

            std::cout << "Enter quantity (units): ";
            int quantity;
            std::cin >> quantity;
            std::cin.ignore();

            // Example: addProductByUnit(name, category, price, quantity);
            std::cout << "Product \"" << name << "\" added successfully under category \"" << category << "\"\n";
        }
        // LOGOUT
        else if (tokens[0] == "logout") {
            // Example: logout();
            std::cout << "Logged out.\n";
        }
        // UNKNOWN COMMAND
        else {
            std::cout << "Unknown command.\n";
        }
    }
}


int main() {
    printWelcome();
    mainLoop();
    return 0;
}
