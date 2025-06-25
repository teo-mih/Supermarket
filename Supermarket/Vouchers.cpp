#include "Vouchers.h"

GiftCard::GiftCard(const String& code, double discountPercent)
    : code(code), discountPercent(discountPercent) {
}

const String& GiftCard::getCode() const { return code; }
double GiftCard::getDiscountPercent() const { return discountPercent; }



SingleCategoryGiftCard::SingleCategoryGiftCard(const String& code, double discountPercent, const String& categoryName)
    : GiftCard(code, discountPercent), categoryName(categoryName) {
}

bool SingleCategoryGiftCard::appliesTo(const Product& product) const {  
   return product.getCategory().Name == categoryName;  
}



MultipleCategoryGiftCard::MultipleCategoryGiftCard(const String& code, double discountPercent, const Vector<String>& categoryNames)
    : GiftCard(code, discountPercent), categoryNames(categoryNames) {
}

bool MultipleCategoryGiftCard::appliesTo(const Product& product) const {
    for (size_t i = 0; i < categoryNames.getSize(); ++i)
        if (product.getCategory().Name == categoryNames[i])
            return true;
    return false;
}



AllProductsGiftCard::AllProductsGiftCard(const String& code, double discountPercent)
    : GiftCard(code, discountPercent) {
}

bool AllProductsGiftCard::appliesTo(const Product&) const { return true; }


String generateVoucherCode(int counter) {
    char code[7];
    code[0] = '0' + (std::rand() % 10);
    code[1] = 'A' + (std::rand() % 26);
    code[2] = '0' + (counter % 10); // single digit for simplicity
    code[3] = 'A' + (std::rand() % 26);
    code[4] = '0' + (std::rand() % 10);
    code[5] = '\0';
    return String(code);
}

double applyVoucherToSale(const GiftCard* voucher, const Vector<Product*>& soldProducts) {
    double total = 0.0;
    for (size_t i = 0; i < soldProducts.getSize(); ++i) {
        const Product* prod = soldProducts[i];
        double price = prod->getPrice() * prod->getQuantity();
        if (voucher && voucher->appliesTo(*prod)) {
            price *= (1.0 - voucher->getDiscountPercent() / 100.0);
        }
        total += price;
    }
    return total;
}

void parseProductLoad(const String& line, String& productType, int& productId, int& quantity) {
    char buffer[256];
    std::strncpy(buffer, line.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, ":");
    if (token) productType = String(token);

    token = std::strtok(nullptr, ":");
    if (token) productId = std::atoi(token);

    token = std::strtok(nullptr, ":");
    if (token) quantity = std::atoi(token);
}

void parseNewProduct(const String& line, String& productType, int& id, String& name, String& category, double& price, int& quantity) {
    char buffer[256];
    std::strncpy(buffer, line.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, ":"); // "NEW"
    token = std::strtok(nullptr, ":");      // productType
    if (token) productType = String(token);

    token = std::strtok(nullptr, ":");      // id
    if (token) id = std::atoi(token);

    token = std::strtok(nullptr, ":");      // name
    if (token) name = String(token);

    token = std::strtok(nullptr, ":");      // category
    if (token) category = String(token);

    token = std::strtok(nullptr, ":");      // price
    if (token) price = std::atof(token);

    token = std::strtok(nullptr, ":");      // quantity
    if (token) quantity = std::atoi(token);
}

void parseGiftCardType1(const String& line, String& category, double& percent) {
    char buffer[256];
    std::strncpy(buffer, line.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, ":"); // "GIFT_CARD_TYPE_1"
    token = std::strtok(nullptr, ":");      // category
    if (token) category = String(token);

    token = std::strtok(nullptr, ":");      // percent
    if (token) percent = std::atof(token);
}

void parseGiftCardType2(const String& line, int& count, Vector<String>& categories, double& percent) {
    char buffer[256];
    std::strncpy(buffer, line.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, ":"); // "GIFT_CARD_TYPE_2"
    token = std::strtok(nullptr, ":");      // count
    if (token) count = std::atoi(token);

    for (int i = 0; i < count; ++i) {
        token = std::strtok(nullptr, ":");
        if (token) categories.push_back(String(token));
    }

    token = std::strtok(nullptr, ":");      // percent
    if (token) percent = std::atof(token);
}

void parseGiftCardType3(const String& line, double& percent) {
    char buffer[256];
    std::strncpy(buffer, line.c_str(), sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = std::strtok(buffer, ":"); // "GIFT_CARD_TYPE_3"
    token = std::strtok(nullptr, ":");      // percent
    if (token) percent = std::atof(token);
}
