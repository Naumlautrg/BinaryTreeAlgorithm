#include "MainThread.h"

void MainThread::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

bool MainThread::dumpEnglish()
{
	std::ifstream file(FILEPATH_ENGLISH);

	if (!file.is_open())
		return false;

	std::string word;
	while (std::getline(file, word))
	{
		dictionary.insert(word);
	}

	file.close();

	return true;
}

void MainThread::chooseLanguage(bool& success)
{
}

void MainThread::start()
{
}
