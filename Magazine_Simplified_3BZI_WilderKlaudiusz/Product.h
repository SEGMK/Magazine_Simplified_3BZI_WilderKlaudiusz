#pragma once

#include <string>
#include <Windows.h>
#include <nlohmann/json.hpp>

using namespace std;

class Product
{
public:
	Product(
		
		string name,
		string description,
		string type,
		double price,
		double quantity,
		double discountPercentage
	)
	{
		auto result = CoCreateGuid(&Guid);
		if (FAILED(result))
		{
			throw exception("product could not be created");
		}

		Name = name;
		Description = description;
		Type = type;
		Price = price;
		Quantity = quantity;
		DiscountPercentage = discountPercentage;
	}

	GUID GetId() const { return Guid; };//copy
	string GetName() const { return Name; }; //copy
	string GetDescription() const { return Description; }; //copy
	string GetType() const { return Type; }; //copy

	//value types
	double GetPrice() const { return Price; };
	double GetQuantity() const { return Quantity; };
	double GetAmount() const { return (Price * Quantity) / DiscountPercentage; };

private:
	GUID Guid;
	string Name;
	string Description;
	string Type;
	double Price;
	double Quantity;
	double DiscountPercentage;

};