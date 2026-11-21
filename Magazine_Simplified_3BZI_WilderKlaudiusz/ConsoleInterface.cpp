#include "ConsoleInterface.h"
#include "SearchEngine.h"
#include "SearchEngineRequest.h"
#include "Helper.h"
#include "Product.h"
#include "ProductSerializer.h"

#include <cstdlib>
#include <limits>
#include <iostream>
#include <thread>
#include <stop_token>

using namespace std;

void ConsoleInterface::Run()
{
	ChooseOption();
}
#pragma region MainOptions

void ConsoleInterface::ChooseOption()
{
	int choice = 0;
	bool closeProgram = false;
	string errorMessage = "";

	do
	{
		try
		{
			system("cls");

			if (errorMessage != "")
			{
				cout << errorMessage << endl;
				errorMessage = "";
			}

			cout << "Choose an option:\n";
			cout << "1. Display elements\n";
			cout << "2. Add element\n";
			cout << "3. Remove element\n";
			cout << "0. Exit program\n";

			choice = RetryInputValidation<int>(Helper::TryParseInt);

			switch (choice)
			{
			case 1:
				DisplayElements();
				break;
			case 2:
				AddElement();
				break;
			case 3:
				RemoveElement();
				break;
			case 0:
				closeProgram = ExitProgram();
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
				break;
			}
		}
		catch (const exception& ex)
		{
			errorMessage = "An error occurred: " + string(ex.what());
			//logger
		}
	} while (!closeProgram);
}

#pragma endregion

#pragma region DisplayElements

void ConsoleInterface::DisplayElements()
{
	int choice;
	SearchEngineRequest searchRequest = SearchEngineRequest();
	int currentIndex = 0;
	vector<Product> elementsCollection = vector<Product>();
	string errorMessage = "";

	do
	{
		try
		{
			system("cls");

			if (errorMessage != "")
			{
				cout << errorMessage << endl;
				errorMessage = "";
			}

			DisplayElement(elementsCollection, currentIndex);

			cout << endl;

			cout << "Choose an option:\n";
			cout << "1. Get previous element\n";
			cout << "2. Get next element\n";

			cout << "8. Create new request\n";
			cout << "9. Fetch new results\n";
			cout << "0. Return to main menu\n";

			choice = RetryInputValidation<int>(Helper::TryParseInt);

			switch (choice)
			{
			case 1:

				if (0 < currentIndex)
				{
					currentIndex--;
				}

				break;
			case 2:

				if (currentIndex < elementsCollection.size() - 1)
				{
					currentIndex++;
				}

				break;
			case 8:
				searchRequest = CreateSearchRequest();
				break;
			case 9:
				elementsCollection = GetSearchEngineResults(searchRequest);
				break;
			case 0:
				cout << "Returning to main menu..." << endl;
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
				break;
			}
		}
		catch (const exception& ex)
		{
			errorMessage = "An error occurred: " + string(ex.what());
			//logger
		}
	} while (choice != 0);
}

SearchEngineRequest ConsoleInterface::CreateSearchRequest()
{
	system("cls");
	cout << "Create search request" << endl;
	cout << "Leave Product name empty to search all products." << endl << endl;

	SearchEngineRequest searchRequest = SearchEngineRequest();

	searchRequest.MinPrice = EnterSearchParameter<double>(
		Helper::TryParseDouble,
		vector<string>
		{ 
			"Leave empty to set no minimum price",
			"Product min price: "
		});

	searchRequest.MaxPrice = EnterSearchParameter<double>(
		Helper::TryParseDouble,
		vector<string>
		{
			"Leave empty to set no maximum price",
			"Product max price: "
		});

	cout << "Leave empty to set no maximum price" << endl;
	cout << "Product name contains: " << endl;
	getline(cin, searchRequest.ProductNameContains);

	searchRequest.SortBy = EnterSearchParameter<int>(
		Helper::TryParseInt,
		vector<string>
		{
			"Leave empty to set no minimum price",
			"Sort by (0 = price, 1 = name, 2 = rating): "
		}).value_or(0);

	searchRequest.SortDirection = EnterSearchParameter<int>(
		Helper::TryParseInt,
		vector<string>
		{
			"Leave empty to set no minimum price",
			"Sort direction (0 = ascending, 1 = descending): "
		}).value_or(0);


	cout << "Search request saved:" << endl;
	cout << "Minimum price: "
		<< (searchRequest.MinPrice ? to_string(searchRequest.MinPrice.value()) : "None")
		<< endl;
	cout << "Maximum price: "
		<< (searchRequest.MaxPrice ? to_string(searchRequest.MaxPrice.value()) : "None")
		<< endl;
	cout << "Product name contains: "
		<< searchRequest.ProductNameContains
		<< endl;
	cout << "Sort direction: "
		<< (searchRequest.SortDirection == 0 ? "Ascending" : "Descending")
		<< endl;
	cout << "Sort by: "
		<< (searchRequest.SortBy == 0 ? "Price" :
			searchRequest.SortBy == 1 ? "Name" : "Rating")
		<< endl;
	cout << "\nPress Enter to continue...";
	cin.get();

	return searchRequest;
}

vector<Product> ConsoleInterface::GetSearchEngineResults(SearchEngineRequest request)
{
	auto result = _searchEngine.GetProducts(request);
	
	if (!get<1>(result))
	{
		throw exception("Products could not be fetched from search engine");
	}

	return get<0>(result);
}

void ConsoleInterface::DisplayElement(vector<Product> products, int currentIndex)
{
	if (products.size() == 0)
	{
		cout << "No elements to display" << endl;
		return;
	}

	cout << "Current element index: " << currentIndex << endl;
	cout << "Current element:" << endl;

	json jsonObject = products[currentIndex];
	auto jsonString = jsonObject.dump(4);
	cout << jsonString << endl;
}

#pragma endregion




void ConsoleInterface::RemoveElement()
{
}

void ConsoleInterface::AddElement()
{
}

void ConsoleInterface::SearchElement()
{
}

void ConsoleInterface::SortElements()
{
}



bool ConsoleInterface::ExitProgram()
{
	system("cls");
	cout << "Are you sure you want to exit? (y/n): ";
	char confirm;
	if (!(cin >> confirm))
	{
		return true;
	}

	if (confirm == 'y' || confirm == 'Y')
	{
		cout << "Exiting the program. Goodbye!\n";
		return true;
	}

	return false;
}

