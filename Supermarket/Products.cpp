#include "Products.h"

Product::Product(const String& name, const Category& category, double price)
	: name(name), category(category), price(price) {
}

const String& Product::getName() const { return name; }
const Category& Product::getCategory() const { return category; }
double Product::getPrice() const { return price; }
 