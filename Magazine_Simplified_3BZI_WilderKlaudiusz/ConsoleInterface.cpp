#include "ConsoleInterface.h"
#include "SearchEngine.h"
#include "SearchEngineRequest.h"
#include "Helper.h"

#include <cstdlib>
#include <limits>
#include <iostream>
#include <thread>
#include <stop_token>


void ConsoleInterface::Run()
{
	ChooseOption();
}
#pragma region MainOptions

void ConsoleInterface::ChooseOption()
{
	int choice = 0;
	bool closeProgram = false;
	std::string errorMessage = "";
	do
	{
		try
		{
			system("cls");

			if (errorMessage != "")
			{
				std::cout << errorMessage << std::endl;
				errorMessage = "";
			}

			std::cout << "Choose an option:\n";
			std::cout << "1. Display elements\n";
			std::cout << "2. Add element\n";
			std::cout << "3. Remove element\n";
			std::cout << "0. Exit program\n";

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
				std::cout << "Invalid choice. Please try again.\n";
				break;
			}
		}
		catch (const std::exception& e)
		{
			errorMessage = "An error occurred: " + std::string(e.what());
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

	do
	{
		system("cls");
		std::cout << "Choose an option:\n";
		std::cout << "1. Get next page\n";
		std::cout << "2. Get previous page\n";

		std::cout << "8. Create new request\n";
		std::cout << "9. Fetch new results\n";
		std::cout << "0. Return to main menu\n";

		choice = RetryInputValidation<int>(Helper::TryParseInt);

		switch (choice)
		{
		case 1:
			// Handle Option 1
			break;
		case 2:
			// Handle Option 2
			break;
		case 8:
			searchRequest = CreateSearchRequest();
			break;
		case 9:
			// Handle Option 9
			break;
		case 0:
			std::cout << "Returning to main menu..." << std::endl;
			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
			break;
		}
	} while (choice != 0);
}

SearchEngineRequest ConsoleInterface::CreateSearchRequest()
{
	system("cls");
	std::cout << "Create search request\n";
	std::cout << "Leave Product name empty to search all products.\n\n";

	SearchEngineRequest searchRequest = SearchEngineRequest();

	searchRequest.MinPrice = EnterSearchParameter<double>(
		Helper::TryParseDouble,
		new std::string[] 
		{ 
			"Leave empty to set no minimum price",
			"Product min price: "
		});

	searchRequest.MaxPrice = EnterSearchParameter<double>(
		Helper::TryParseDouble,
		new std::string[]
		{
			"Leave empty to set no maximum price",
			"Product max price: "
		});

	std::cout << "Product name contains: ";
	std::cout << "Leave empty to set no maximum price";
	std::getline(std::cin, searchRequest.ProductNameContains);

	searchRequest.SortBy = EnterSearchParameter<int>(
		Helper::TryParseInt,
		new std::string[]
		{
			"Leave empty to set no minimum price",
			"Sort by (0 = price, 1 = name, 2 = rating): "
		});

	searchRequest.MinPrice = EnterSearchParameter<int>(
		Helper::TryParseInt,
		new std::string[]
		{
			"Leave empty to set no minimum price",
			"Sort direction (0 = ascending, 1 = descending): "
		});


	std::cout << "Search request saved:" << std::endl;
	std::cout << "Minimum price: "
		<< (searchRequest.MinPrice ? std::to_string(searchRequest.MinPrice.value()) : "None")
		<< std::endl;
	std::cout << "Maximum price: "
		<< (searchRequest.MaxPrice ? std::to_string(searchRequest.MaxPrice.value()) : "None")
		<< std::endl;
	std::cout << "Product name contains: "
		<< searchRequest.ProductNameContains
		<< std::endl;
	std::cout << "Sort direction: "
		<< (searchRequest.SortDirection == 0 ? "Ascending" : "Descending")
		<< std::endl;
	std::cout << "Sort by: "
		<< (searchRequest.SortBy == 0 ? "Price" :
			searchRequest.SortBy == 1 ? "Name" : "Rating")
		<< std::endl;
	std::cout << "\nPress Enter to continue...";
	std::cin.get();

	return searchRequest;
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
	std::cout << "Are you sure you want to exit? (y/n): ";
	char confirm;
	if (!(std::cin >> confirm))
	{
		return false;
	}

	if (confirm == 'y' || confirm == 'Y')
	{
		std::cout << "Exiting the program. Goodbye!\n";
		return false;
	}

	return true;
}

