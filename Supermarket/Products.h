#pragma once
#include <iostream>
#include "String.h"
#include "Vector.hpp"

struct Category {
	String Name;
	String Description;
	int id;
};

class Product {
protected:
	String name;
	Category category;
	double price;
	int id;
	int quantity;
public:
	Product(const String& name, const Category& category, double price, int id, int quantity);
	const String& getName() const;
	const Category& getCategory() const;
	double getPrice() const;
	int getId() const;
	int getQuantity() const;
	void printReceipt(int transactionId, int cashierId, const Vector<Product>& products, double finalPrice);
	virtual ~Product() = default;
};


