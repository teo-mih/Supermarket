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
public:
	Product(const String& name, const Category& category, double price) {}
	const String& getName() const;
	const Category& getCategory() const;
	double getPrice() const;
	virtual ~Product() = default;
};


