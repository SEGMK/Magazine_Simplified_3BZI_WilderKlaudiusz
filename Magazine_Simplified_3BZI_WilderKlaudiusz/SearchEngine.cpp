#include "SearchEngine.h"
#include "SearchEngineRequest.h"
#include "Product.h"

tuple<vector<Product>, bool> SearchEngine::GetProducts(SearchEngineRequest searchRequest)
{
	try
	{
		auto receivedProductCollection = vector<Product>
		{
			Product(
				"test",
				"test",
				"test",
				1,
				1,
				1
			),
			Product(
				"test2",
				"test2",
				"test2",
				2,
				2,
				2
			)
		};

		return tuple<vector<Product>, bool>
		{
			receivedProductCollection,
			true
		};
	}
	catch (const exception& ex)
	{
		return tuple < vector<Product>, bool>
		{
			vector<Product>(),
			false
		};
	}
}

bool SearchEngine::PostProduct(Product product)
{
	return false;
}

bool SearchEngine::DeleteProduct(GUID id)
{
	return false;
}