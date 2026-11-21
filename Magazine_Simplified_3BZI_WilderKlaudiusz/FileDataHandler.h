#pragma once

#include "Product.h"

#include <string>

using namespace std;

class FileDataHandler
{
public:
	void SaveProducts(vector<Product> products);
	vector<Product> LoadProducts();
private:
	const string FileStoragePath = "/magazine/products/";
};