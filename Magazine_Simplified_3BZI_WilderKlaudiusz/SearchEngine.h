#pragma once
#include "Product.h"
#include "SearchEngineRequest.h"

#include <Windows.h>
#include <tuple>

class SearchEngine // : ISearchEngine
{
public:
	tuple<vector<Product>, bool> GetProducts(SearchEngineRequest searchRequest);
	bool PostProduct(Product product);
	bool DeleteProduct(GUID id);
	bool UpdateProduct(GUID id, Product product) 
	{
		bool success = true;

		success &= DeleteProduct(id);
		success &= PostProduct(product);

		return success;
	}

private:
	bool ChooseOption();
	void DisplayElements();
	void RemoveElement();
	void AddElement();
	void SearchElement();
	void SortElements();
	bool ExitProgram();
	bool ValidateInput();
};
