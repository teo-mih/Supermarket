#pragma once
#include <iostream>
#include "String.h"
struct Category {
	String Name;
	String Description;
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
	virtual ~Product() = default;
};


