#include "MainThread.h"

void MainThread::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
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
	std::ifstream file(FILEPATH_ENGLISH);

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
	displayDashLine(55);
	
	file.close();

	return true;
}

void MainThread::displayDashLine(const std::string& s, bool newLineAfter)
{
	std::cout << s << "\n" << std::string(s.length(), '-');
	if (newLineAfter) std::cout << "\n";
}

void MainThread::displayDashLine(const int& length, bool newLineAfter)
{
	std::cout << "\n" << std::string(length, '-');
	if (newLineAfter) std::cout << "\n";
}

void MainThread::displayLanguageOptions()
{
	std::cout << "You must supply the program a target language.\n";
	std::cout << "Select from one of the options listed below (1-2):\n";
	std::cout << "1 - English\n"
			<< "2 - Spanish\n";
	std::cout << "Enter here: ";
}

void MainThread::displayDictionaryOptions()
{
	std::cout << "Select an option from the listed below:\n";
	std::cout << "1 - Autocomplete\n"
			<< "2 - Spellcheck\n"
			<< "3 - Find Word";
	std::cout << "Enter here: ";
}

bool MainThread::chooseLanguage()
{
	int chosenLanguage;

	displayLanguageOptions();

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
			displayDashLine("That option does not exist. Please select another option.");
			return false;
			break;
		}
		return true;
	}
	else
	{
		clearScreen();
		displayDashLine("Invalid input. Please enter a valid option.");
		return false;
	}
}

bool MainThread::chooseDictionaryOption()
{
	const int EXIT_OPTION = 4;
	int chosenOption = 0;

	if (prompt(chosenOption))
	{
		switch (chosenOption)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			std::cout << "";
			break;
		}
	}

	return true;
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

	while (!chooseDictionaryOption()) { }


}
