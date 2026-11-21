#pragma once

#include "SearchEngineRequest.h"

#include <iostream>
#include <limits>
#include <string>

class ConsoleInterface // : IAppInterface
{
public:
	void Run();

private:
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

			std::cout << "Invalid input. Please enter a valid value.\n";
		}
	}

#pragma region DisplayElements

	void DisplayElements();
	SearchEngineRequest CreateSearchRequest();
	void FetchSearchEngineResults(SearchEngineRequest request);

	template <typename T, typename Parser>
	T EnterSearchParameter(Parser parsingMethod, std::string consoleLines[])
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
				return RetryInputValidation<T>(parsingMethod);
			}
		}
	}

#pragma endregion

};
