#include "SupermarketSystem.h"
#include <fstream>
#include <ctime>
#include <cstdlib>


void SupermarketSystem::login(const int id, const String& password) {
	for (size_t i = 0; i < users.getSize(); ++i) {
		if (users[i]->getId() == id && users[i]->getPassword() == password) {
			std::cout << "Login successful for user: " << users[i]->getName() << std::endl;
			currentUser = users[i];
			return;
		}
	}
	std::cout << "Login failed. Invalid credentials." << std::endl;
}

void SupermarketSystem::registerUser(Worker* user) {
	users.push_back(user);
}

void SupermarketSystem::listUserData() const {
	for (size_t i = 0; i < users.getSize(); ++i) {
		std::cout << "ID: " << users[i]->getId()
			<< ", Name: " << users[i]->getName()
			<< ", Lastname: " << users[i]->getLastname()
			<< ", Phone: " << users[i]->getPhoneNumber()
			<< ", Age: " << users[i]->getAge()
			<< std::endl;
	}
}
void SupermarketSystem::listWorkers() const {
	for (size_t i = 0; i < users.getSize(); ++i) {
		std::cout << "ID: " << users[i]->getId()
			<< ", Name: " << users[i]->getName()
			<< ", Lastname: " << users[i]->getLastname()
			<< ", Phone: " << users[i]->getPhoneNumber()
			<< ", Age: " << users[i]->getAge()
			<< std::endl;
	}
}
void SupermarketSystem::listProducts() const {
	for (size_t i = 0; i < products.getSize(); ++i) {
		std::cout << "Product ID: " << products[i]->getId()
			<< ", Name: " << products[i]->getName()
			<< ", Price: " << products[i]->getPrice()
			<< ", Quantity: " << products[i]->getQuantity()
			<< std::endl;
	}
}

Vector<Product*> SupermarketSystem::getProductsByCategory(const String& categoryName) const {
	Vector<Product*> filteredProducts;
	for (size_t i = 0; i < products.getSize(); ++i) {
		if (products[i]->getCategory().Name == categoryName) {
			filteredProducts.push_back(products[i]);
		}
	}
	return filteredProducts;
}

void SupermarketSystem::listFeed() const {
	for (size_t i = 0; i < feed.getSize(); ++i) {
		std::cout << "Performer: " << feed[i].performer
			<< ", Description: " << feed[i].description
			<< ", DateTime: " << feed[i].datetime
			<< std::endl;
	}
}

void SupermarketSystem::listTransactions() const {
	for (size_t i = 0; i < feed.getSize(); ++i) {
		std::cout << "Transaction by: " << feed[i].performer
			<< ", Description: " << feed[i].description
			<< ", DateTime: " << feed[i].datetime
			<< std::endl;
	}
}

void SupermarketSystem::logout() {
	if (currentUser) {
		std::cout << "User " << currentUser->getName() << " logged out." << std::endl;
		currentUser = nullptr;
	}
	else {
		std::cout << "No user is currently logged in." << std::endl;
	}
}


void SupermarketSystem::sell(const Vector<Product*>& soldProducts, double totalAmount) {
	if (!currentUser) {
		std::cout << "No cashier is logged in." << std::endl;
		return;
	}

	// Generate transaction id
	int transactionId = static_cast<int>(transactions.getSize()) + 1;

	// Get current date and time as string
	std::time_t now = std::time(nullptr);
	std::tm* localtm = std::localtime(&now);
	char datetime[20];
	std::strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtm);

	// Create receipt file name
	char receiptFileName[32];
	std::sprintf(receiptFileName, "receipt_%d.txt", transactionId);

	// Write receipt
	std::ofstream receiptFile(receiptFileName);
	receiptFile << "Receipt #" << transactionId << std::endl;
	receiptFile << "Cashier: " << currentUser->getName() << std::endl;
	receiptFile << "Date: " << datetime << std::endl;
	receiptFile << "------------------------" << std::endl;
	for (size_t i = 0; i < soldProducts.getSize(); ++i) {
		receiptFile << soldProducts[i]->getName() << " x" << soldProducts[i]->getQuantity()
			<< " - $" << soldProducts[i]->getPrice() << std::endl;
	}
	receiptFile << "------------------------" << std::endl;
	receiptFile << "Total: $" << totalAmount << std::endl;
	receiptFile.close();

	// Save transaction info
	Transaction t;
	t.cashierName = currentUser->getName();
	t.amount = totalAmount;
	t.datetime = datetime;
	t.receiptFileName = receiptFileName;
	transactions.push_back(t);

	// Increment cashier's transaction count
	currentUser->incrementTransactionCount();

	// For every 3 transactions, clear earliest warning
	if (currentUser->getTransactionCount() % 3 == 0) {
		currentUser->clearEarliestWarning();
	}

	std::cout << "Transaction complete. Receipt saved as " << receiptFileName << std::endl;
}

