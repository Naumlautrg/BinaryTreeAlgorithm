/*
	This program autocompletes words input by the user and allows for searching for words within a target dictionary.
	With internet connection, the user can also search definitions of any words listed in the Free Dictionary API (https://dictionaryapi.dev/)
	English word list file source https://github.com/dwyl/english-words 
	Spanish word list file source https://github.com/xavier-hernandez/spanish-wordlist

	This program also requires three libraries/packages in order to successfully build and compile.
	Each library was installed using the package manager "vcpkg"
	vcpkg install icu (for unicode)
	vcpkg install cpr (c++ requests, wrapper around libcurl for http requests)
	vcpkg install nlohmann-json (for reading json files, in our case the data provided from the Free Dictionary API)
*/
#include <iostream>
#include <fstream>
#include <unicode/ustream.h>
#include <exception>

#include "BinaryTree.h"
#include "MainThread.h"

void demoBinaryTree()
{
	BinaryTree<int> inty(2);

	inty.insert(3);
	inty.preorderPrint();

	inty.insert(4);
	inty.remove(4);
	inty.insert(5);
	inty.preorderPrint();
}

void demoTrie()
{
	TrieDictionary dict;
	dict.insert("Wortonon");
	dict.insert("Wod");
	dict.insert("Wo");
	dict.insert("Wor");
	dict.insert("Word");
	dict.insert("Worda");
	dict.insert("anotherWord");

	std::cout << std::boolalpha << dict.contains("Word") << "\n";

	std::vector<std::string> words = dict.inclusiveSearch("Word");
	for (int i = 0; i < words.size(); ++i)
	{
		std::cout << words[i] << "\n";
	}

	std::cout << "\n";

	std::vector<std::string> searchResults = dict.prefixSearch("Word");
	for (int i = 0; i < searchResults.size(); ++i)
	{
		std::cout << searchResults[i] << "\n";
	}

	dict.clear();
	words = dict.inclusiveSearch("Word");
	for (int i = 0; i < words.size(); ++i)
	{
		std::cout << words[i] << "\n";
	}
}

int main()
{
	try
	{
		// Demos
		//demoBinaryTree();
		//demoTrie();

		MainThread m;
		m.start();

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error occurred: " << e.what() << "\n\n";
	}
}