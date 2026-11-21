#pragma once

#include "SearchEngineRequest.h"
#include "SearchEngine.h"
#include "Product.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <optional> //nullable type

class ConsoleInterface // : IAppInterface
{
public:

	
	ConsoleInterface()
	{
		//should be injected by DependencyInjectionService
		_searchEngine = SearchEngine();
	}
	void Run();

private:
	/*readonly*/ SearchEngine _searchEngine;

	void ChooseOption();
	void RemoveElement();
	void AddElement();
	void SearchElement();
	void SortElements();
	bool ExitProgram();
	template <typename T, typename Parser> //Parser type is determined automatically 
	T RetryInputValidation(Parser parsingMethod)
	{
		T value{};
		std::string input;

		while (true)
		{
			std::getline(std::cin, input);

			if (parsingMethod(input, value))
			{
				return value;
			}

			std::cout << "Invalid input. Please enter a valid value." << std::endl;
		}
	}

#pragma region DisplayElements

	void DisplayElements();
	SearchEngineRequest CreateSearchRequest();
	vector<Product> GetSearchEngineResults(SearchEngineRequest request);
	void DisplayElement(vector<Product> products, int currentIndex);

	template <typename T, typename Parser>
	std::optional<T> EnterSearchParameter(Parser parsingMethod, const std::vector<std::string>& consoleLines)
	{
		//foreach; & - ref; const - no mod
		for (const std::string& line : consoleLines)
		{
			std::cout << line << std::endl;
		}

		std::string input;
		std::getline(std::cin, input);

		if (!input.empty())
		{
			T value;
			if (parsingMethod(input, value))
			{
				return value;
			}
			else
			{
				std::cout << "Invalid input. Please enter a valid value." << std::endl;
				return RetryInputValidation<T>(parsingMethod);
			}
		}

		return std::nullopt;
	}

#pragma endregion

};
