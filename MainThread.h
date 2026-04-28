#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "BinaryTree.h"

enum class Language
{
	English,
	Spanish
};

/*
	Facilitates all functionality for the program.
	Create an instance in main and call start()
*/
class MainThread
{
private:
	TrieDictionary dictionary;
	Language currentLanguage;
	std::unordered_map<std::string, std::string> cachedDefinitions;

	/*
		Constants
	*/

	const std::string FILEPATH_ENGLISH = "WordLists/english_words.txt";
	const std::string FILEPATH_SPANISH = "WordLists/spanish_words.txt";

	/*
		Methods
	*/

	void clearScreen();

	template<typename T>
	bool prompt(T& value)
	{
		std::cin >> value;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}

		return true;
	}

	size_t longestStringLength(const std::vector<std::string>& stringVector)
	{
		/*
		* Using ranges to find the longest length string:
		* {} is the default comparison (std::ranges::less in this instance)
		* &std::string::size calls .size() on each string before comparison, called a projection
		* The difference between std::ranges::max_element and std::max_element is that it accepts containers and supports projections
		*/
		auto longestStringIt = std::ranges::max_element(stringVector, {}, &std::string::size);
		if (longestStringIt != stringVector.end())
		{
			std::string longestString = *longestStringIt;
			return longestString.length();
		}
		return 0;
	}

	const std::string getLanguageFilePath(const Language& language) const;
	bool dumpLanguage();

	/*
		Print Methods
	*/
	
	/* Prints a line of dashes with the exact length of the input string, immediately afte displaying the input string. */
	void printDashLine(const std::string& s, bool newLineAfter = true);
	/* Prints a line of dashes with the input length. */
	void printDashLine(int length, bool newLineAfter = true);
	void printLanguageOptions();
	void printDictionaryOptions();
	void printChosenDictionaryOption(int chosenOption);

	/*
		Methods requiring user input
	*/

	/* Returns false when the language option does not exist or the input is invalid. */
	bool chooseLanguage();
	/* Returns false when the user enters the exit option. */
	bool chooseDictionaryOption();
	bool autocomplete();
	bool definitionLookup();
	bool findWord();

public:
	MainThread() = default;

	void start();
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 