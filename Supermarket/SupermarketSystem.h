#pragma once
#include "Worker.h"
#include "Vector.hpp"
#include "Products.cpp"

struct Notification {
	String performer;
	String description;
	std::string datetime;
};

class SupermarketSystem {
	Vector<Worker*> users;
	Vector<Product*> products;
	Vector <Notification> feed;
public:

	void login(const int id, const String& password) {
		for (size_t i = 0; i < users.getSize(); ++i) {
			if (users[i]->getId() == id && users[i]->getPassword() == password) {
				std::cout << "Login successful for user: " << users[i]->getName() << std::endl;
				return;
			}
		}
		std::cout << "Login failed. Invalid credentials." << std::endl;
	}

	void registerUser(Worker* user) {
		users.push_back(user);
	}

	void listUserData() const {
		for (size_t i = 0; i < users.getSize(); ++i) {
			std::cout << "ID: " << users[i]->getId()
				<< ", Name: " << users[i]->getName()
				<< ", Lastname: " << users[i]->getLastname()
				<< ", Phone: " << users[i]->getPhoneNumber()
				<< ", Age: " << users[i]->getAge()
				<< std::endl;
		}
	}
	void listWorkers() const {
		for (size_t i = 0; i < users.getSize(); ++i) {
			std::cout << "ID: " << users[i]->getId()
				<< ", Name: " << users[i]->getName()
				<< ", Lastname: " << users[i]->getLastname()
				<< ", Phone: " << users[i]->getPhoneNumber()
				<< ", Age: " << users[i]->getAge()
				<< std::endl;
		}
	}
	void listProducts() const {
		for (size_t i = 0; i < products.getSize(); ++i) {
			std::cout << "Product ID: " << products[i]->getId()
				<< ", Name: " << products[i]->getName()
				<< ", Price: " << products[i]->getPrice()
				<< ", Quantity: " << products[i]->getQuantity()
				<< std::endl;
		}
	}

	void getProductsByCategory(const String& categoryName) const {
		Vector<Product*> filteredProducts;
		for (size_t i = 0; i < products.getSize(); ++i) {
			if (products[i]->getCategory().Name == categoryName) {
				filteredProducts.push_back(products[i]);
			}
		}
		return filteredProducts;
	}

	void listFeed() const {
		for (size_t i = 0; i < feed.getSize(); ++i) {
			std::cout << "Performer: " << feed[i].performer
				<< ", Description: " << feed[i].description
				<< ", DateTime: " << feed[i].datetime
				<< std::endl;
		}
	}

	void listTransactions() const {
		for (size_t i = 0; i < feed.getSize(); ++i) {
			std::cout << "Transaction by: " << feed[i].performer
				<< ", Description: " << feed[i].description
				<< ", DateTime: " << feed[i].datetime
				<< std::endl;
		}
	}

	
};

