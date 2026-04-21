#pragma once

#include <fstream>
#include <string>

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

	/*
		Constants
	*/

	const std::string FILEPATH_ENGLISH = "WordLists\\EnglishWordList.txt";
	const std::string FILEPATH_SPANISH = "WordLists\\SpanishWordList.txt";

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

	const std::string& languageFilePath(const Language& language) const;
	bool dumpLanguage();

	/*
		Methods requiring user input
	*/

	void chooseLanguage(bool& success);

public:
	MainThread() = default;

	void start();
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    