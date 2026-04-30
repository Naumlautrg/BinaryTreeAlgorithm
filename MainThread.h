#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <ranges>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "BinaryTree.h"

#undef max // one of the header files defines this, it gets in the way and we don't need it

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

	size_t longestStringLength(const std::vector<std::string>& stringVector);
	const std::string getLanguageFilePath(const Language& language) const;
	bool dumpLanguage();
	/* Only works for English for now */
	std::vector<std::string> getDefinitions(const std::string& word);

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
	bool checkWord();

public:
	MainThread() = default;

	void start();
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 