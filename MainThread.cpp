#include "MainThread.h"

void MainThread::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

size_t MainThread::longestStringLength(const std::vector<std::string>& stringVector)
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

const std::string MainThread::getLanguageFilePath(const Language& language) const
{
	switch (language)
	{
	case Language::English:
		return FILEPATH_ENGLISH;
	case Language::Spanish:
		return FILEPATH_SPANISH;
	default:
		return "";
	}
}

bool MainThread::dumpLanguage()
{
	std::ifstream file(getLanguageFilePath(currentLanguage));

	if (!file)
		return false;

	clearScreen();
	std::cout << "Filling dictionary with language file contents...";

	std::string word;
	while (std::getline(file, word))
	{
		dictionary.insert(word);
	}
	
	std::cout << " Done!";
	printDashLine(55);
	
	file.close();

	return true;
}

std::vector<std::string> MainThread::getDefinitions(const std::string& word)
{
	std::vector<std::string> definitions;
	std::string url = "https://api.dictionaryapi.dev/api/v2/entries/en/" + word;

	cpr::Response r = cpr::Get(cpr::Url(url));
	const long SUCCESS_CODE = 200;

	if (r.status_code == SUCCESS_CODE)
	{
		auto data = nlohmann::json::parse(r.text);

		/* 
			You'll have to look at the API example to understand how the data is ordered
			https://dictionaryapi.dev/
		*/
		for (const auto& meaning : data[0]["meanings"])
			for (const auto& definition : meaning["definitions"])
				definitions.push_back(definition["definition"]);

		return definitions;
	}
	else
	{
		std::cerr << "An error has occurred.\nError Code " << r.status_code << "\n";
		return {};
	}
}

void MainThread::printDashLine(const std::string& s, bool newLineAfter)
{
	std::cout << s << "\n" << std::string(s.length(), '-');
	if (newLineAfter) std::cout << "\n";
}

void MainThread::printDashLine(int length, bool newLineAfter)
{
	std::cout << "\n" << std::string(length, '-');
	if (newLineAfter) std::cout << "\n";
}

void MainThread::printLanguageOptions()
{
	std::cout << "You must supply the program a target language.\n";
	std::cout << "Select from one of the options listed below (1-2):\n";
	std::cout << "1 - English\n"
			<< "2 - Spanish\n";
	std::cout << "Enter here: ";
}

void MainThread::printDictionaryOptions()
{
	std::cout << "Select an option from the listed below:\n";
	std::cout << "1 - Autocomplete\n"
			<< "2 - Get Definition (Requires internet connection)\n"
			<< "3 - Check Word\n"
			<< "4 - Exit\n";
	std::cout << "Enter here: ";
}

void MainThread::printChosenDictionaryOption(int chosenOption)
{
	switch (chosenOption)
	{
	case 1:
		printDashLine("Option: 1 - Autocomplete");
		break;
	case 2:
		printDashLine("Option: 2 - Get Definition");
		break;
	case 3:
		printDashLine("Option: 3 - Check Word");
		break;
	case 4:
		printDashLine("Option: 4 - Exit");
		break;
	default:
		std::cout << "Invalid option.\n";
		break;
	}
}

bool MainThread::chooseLanguage()
{
	int chosenLanguage = 0;

	printLanguageOptions();

	bool languageValid = prompt(chosenLanguage);

	if (languageValid)
	{
		switch (chosenLanguage)
		{
		case 1:
			currentLanguage = Language::English;
			break;
		case 2:
			currentLanguage = Language::Spanish;
			break;
		default:
			clearScreen();
			printDashLine("That option does not exist. Please select another option.");
			return false;
			break;
		}
		return true;
	}
	else
	{
		clearScreen();
		printDashLine("Invalid input. Please enter a valid option.");
		return false;
	}
}

bool MainThread::chooseDictionaryOption()
{
	const int EXIT_OPTION = 4;
	int chosenOption = 0;

	printDictionaryOptions();

	if (prompt(chosenOption))
	{
		clearScreen();
		printChosenDictionaryOption(chosenOption);
		switch (chosenOption)
		{
		case 1:
			autocomplete();
			return true;
		case 2:
			definitionLookup();
			break;
		case 3:
			checkWord();
			break;
		case 4:
			return false;
		default:
			std::cout << "";
			break;
		}
	}

	return true;
}

bool MainThread::autocomplete()
{
	std::string input = "";

	char booleanInput = ' ';
	const char OPTION_YES = 'Y';
	const char OPTION_NO = 'N';
	const size_t RESULTDISPLAY_MAX = 5;
	size_t resultDisplayCount = RESULTDISPLAY_MAX;

	std::cout << "Enter your word or partial word: ";
	if (prompt(input))
	{
		auto wordsFound = dictionary.prefixSearch(input);

		std::cout << "Only the first five autocomplete results will display. You can instead display all results if you prefer.\n";
		std::cout << "Display all results? (Y/N): ";
		// Intentionally omitting brackets for this nested if statement; it's less bloated in appearance
		if (prompt(booleanInput))
			if (std::toupper(booleanInput) == OPTION_YES)
				resultDisplayCount = std::clamp(resultDisplayCount, wordsFound.size(), _CRT_SIZE_MAX);
		// _CRT_SIZE_MAX = maximum value for size_t - 1
			else
				resultDisplayCount = std::clamp(resultDisplayCount, static_cast<size_t>(0), wordsFound.size());

		int dashLineLength = static_cast<int>(longestStringLength(wordsFound));
		printDashLine(dashLineLength);
		std::cout << "\nFound words:\n";
		for (int i = 0; i < resultDisplayCount; ++i)
		{
			std::cout << wordsFound[i] << "\n";
		}
		printDashLine(dashLineLength);
		return true;
	}
	else
	{
		clearScreen();
		printDashLine("Invalid input.");
		return false;
	}
}

bool MainThread::definitionLookup()
{
	std::string input;

	std::cout << "Enter your word: ";
	if (prompt(input))
	{
		if (dictionary.contains(input))
		{
			std::vector<std::string> definitions = getDefinitions(input);
			if (definitions.size() <= 0)
				return false;

			int dashLineLength = static_cast<int>(longestStringLength(definitions));
			
			printDashLine(dashLineLength);
			std::cout << "Definitions for " << input << ":\n";
			for (size_t i = 0; i < definitions.size(); ++i)
			{
				std::cout << definitions[i] << "\n";
			}
			printDashLine(dashLineLength);
			return true;
		}
		else
		{
			clearScreen();
			printDashLine("Word " + input + " does not exist in the dictionary.");
			return false;
		}
	}
	else
	{
		clearScreen();
		printDashLine("Invalid input.");
		return false;
	}
}

bool MainThread::checkWord()
{
	std::string input;

	std::cout << "Enter the word you would like to check the existence of: ";
	if (prompt(input))
	{
		if (dictionary.contains(input))
		{
			clearScreen();
			printDashLine("Word " + input + " is an entry in the dictionary.");
			return true;
		}
		else
		{
			clearScreen();
			printDashLine("Word " + input + " is not an entry in the dictionary.");
			return true;
		}
	}
	else
	{
		clearScreen();
		printDashLine("Invalid input.");
		return false;
	}

	return false;
}

void MainThread::start()
{
	int chosenOption = 0;
	bool success = false;

	while (!chooseLanguage()) {}

	if (!dumpLanguage())
	{
		clearScreen();
		std::cout << "Encountered a problem dumping the language file contents into the dictionary.\n"
			<< "Check if the file " << getLanguageFilePath(currentLanguage) << " exists.";
		std::cin.get();
	}

	while (chooseDictionaryOption()) { }

	exit(0);
}
