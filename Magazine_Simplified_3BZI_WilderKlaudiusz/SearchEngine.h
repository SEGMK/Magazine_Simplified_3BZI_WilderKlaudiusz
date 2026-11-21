#pragma once

class SearchEngine // : ISearchEngine
{
public:
	void GetSearchResults(const std::string& query);
	void GetAllSeachOptions();
	void GetCurrentSearchOption();
	void SetSearchOption(int option);
	void ClearSearchOptions();

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
