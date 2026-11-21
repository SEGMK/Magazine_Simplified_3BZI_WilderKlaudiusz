#pragma once
#include <string>
#include <optional> //nullable type

//you can send it empty so I will treat it as record with no constructor
class SearchEngineRequest // : ISearchEngineRequest
{
public:
	std::optional<double> MaxPrice = std::nullopt;
	std::optional<double> MinPrice = std::nullopt;
	std::string ProductNameContains = "";
	int SortDirection = 0; // 0 - Ascending, 1 - Descending
	int SortBy = 0; // 0 - Price, 1 - Name, 2 - Rating

private:
	
};
