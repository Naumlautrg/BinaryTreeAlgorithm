#pragma once

#include <fstream>
#include <string>
#include <iostream>

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

	const std::string getLanguageFilePath(const Language& language) const;
	bool dumpLanguage();

	/*
		Display Methods
	*/
	
	// Displays a line of dashes after displaying the input string with the exact length of the input string.
	void displayDashLine(const std::string& s, bool newLineAfter = true);
	// Displays a line of dashes with the input length.
	void displayDashLine(const int& length, bool newLineAfter = true);
	void displayLanguageOptions();
	// Returns false when user enters the exit option.
	void displayDictionaryOptions();

	/*
		Methods requiring user input
	*/

	bool chooseLanguage();
	bool chooseDictionaryOption();
	bool autocomplete();
	bool spellcheck();
	bool findWord();

public:
	MainThread() = default;

	void start();
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    