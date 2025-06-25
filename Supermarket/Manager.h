#pragma once
#include "Worker.h"
#include "Vouchers.h"
#include "Products.h"
#include "cstdlib"
#include <fstream>
class Manager : public Worker
{
	String identificationCode;

	bool isValidCodeFormat(const String& code) const;
	void saveCodeToFile(const String& code) const;

public:
	Manager(short id, const String& name, const String& lastname, size_t phone_number, size_t age, const String& password);
	

	void listPendingCashiers(const Vector<Worker*>& users) const;
	void approveCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password);
	void declineCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password);
	void listWarnedCashiers(const Vector<Worker*>& users, int minPoints) const;
	void warnCashier(Vector<Worker*>& users, short cashierId, int points, const String& specialCode, const String& password);
	void promoteCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password);
	void fireCashier(Vector<Worker*>& users, short cashierId, const String& specialCode, const String& password);

	void addCategory(Vector<Category>& categories, const String& name, const String& description);
	void deleteCategory(Vector<Category>& categories, Vector<Product*>& products, int categoryId);
	void addProduct(Vector<Product*>& products, Product* product);
	void deleteProduct(Vector<Product*>& products, int productId);
	void loadProducts(Vector<Product*>& products, Vector<Category>& categories, const String& filename);
	void loadGiftCards(Vector<GiftCard*>& giftCards, const String& filename);

	bool setIdentificationCode(const String& code);
	const String& getIdentificationCode() const;
	bool authenticate(const String& code, const String& password) const;

	void seedRandom();
	String generateSpecialCode();
};

