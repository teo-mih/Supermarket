#pragma once
#include "String.h"
#include "Products.h"
#include "Vector.hpp"
#include <iostream>


class GiftCard {
protected:
    String code;
    double discountPercent;
public:
    GiftCard(const String& code, double discountPercent);
    virtual ~GiftCard() = default;

    const String& getCode() const;
    double getDiscountPercent() const;

    // Returns true if the voucher applies to the product
    virtual bool appliesTo(const Product& product) const = 0;
};


class SingleCategoryGiftCard : public GiftCard {
    String categoryName;
public:
    SingleCategoryGiftCard(const String& code, double discountPercent, const String& categoryName);
    bool appliesTo(const Product& product) const override;
};


class MultipleCategoryGiftCard : public GiftCard {
    Vector<String> categoryNames;
public:
    MultipleCategoryGiftCard(const String& code, double discountPercent, const Vector<String>& categoryNames);
    bool appliesTo(const Product& product) const override;
};


class AllProductsGiftCard : public GiftCard {
public:
    AllProductsGiftCard(const String& code, double discountPercent);
    bool appliesTo(const Product&) const override;
};

String generateVoucherCode(int counter);
double applyVoucherToSale(const GiftCard* voucher, const Vector<Product*>& soldProducts);
void parseProductLoad(const String& line, String& productType, int& productId, int& quantity);
void parseNewProduct(const String& line, String& productType, int& id, String& name, String& category, double& price, int& quantity);
void parseGiftCardType1(const String& line, String& category, double& percent);
void parseGiftCardType2(const String& line, int& count, Vector<String>& categories, double& percent);
void parseGiftCardType3(const String& line, double& percent);