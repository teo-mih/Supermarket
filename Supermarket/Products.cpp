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