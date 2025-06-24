#pragma once
#include "Worker.h"
#include "Vector.hpp"
#include "Products.h"

struct Notification {
	String performer;
	String description;
	std::string datetime;
};

struct Transaction {
	String cashierName;
	double amount;
	std::string datetime;
	String receiptFileName;
};
Vector<Transaction> transactions;

class SupermarketSystem {
	Vector<Worker*> users;
	Vector<Product*> products;
	Vector <Notification> feed;
	Worker* currentUser = nullptr;
public:

	void login(const int id, const String& password);
	void registerUser(Worker* user);
	void logout();

    void listUserData() const;
	void listWorkers() const;
	void listProducts() const;
	Vector<Product*> getProductsByCategory(const String& categoryName) const;
	void listFeed() const;
	void listTransactions() const;

	void sell(const Vector<Product*>& soldProducts, double totalAmount);
};

