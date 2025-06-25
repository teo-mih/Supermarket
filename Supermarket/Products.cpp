#include "Products.h"

Product::Product(const String& name, const Category& category, double price, int id, int quantity)
	: name(name), category(category), price(price), id(id), quantity(quantity) {
}

const String& Product::getName() const { return name; }
const Category& Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
int Product::getId() const { return id; }
int Product::getQuantity() const {
	return quantity;
}

void Product::printReceipt(int transactionId, int cashierId, const Vector<Product>& products, double finalPrice) {
    std::cout << "RECEIPT\n";
    std::cout << "TRANSACTION ID: " << transactionId << "\n";
    std::cout << "CASHIER ID: " << cashierId << "\n";

    // Print date and time
    std::time_t t = std::time(nullptr);
    char dateStr[100];
    std::strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    std::cout << dateStr << "\n";

    for (size_t i = 0; i < products.getSize(); ++i) {
        const Product& product = products[i];
        std::cout << product.getName() << "\n";
        std::cout << product.getQuantity() << "*" << product.getPrice() << "\n";
        std::cout << (product.getQuantity() * product.getPrice()) << "\n";
        std::cout << "###\n";
    }
    std::cout << "TOTAL: " << finalPrice << "\n";
}