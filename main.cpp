/* This program autocompletes words input by the user and allow for searching for words within a target dictionary.
	English word list file sourced from https://github.com/dwyl/english-words 

	Requires the "icu" vcpkg
*/
#include <iostream>
#include <fstream>
#include <unicode/ustream.h>

#include "BinaryTree.h"

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

	std::vector<std::string> searchResults = dict.exclusiveSearch("Word");
	for (int i = 0; i < searchResults.size(); ++i)
	{
		std::cout << searchResults[i] << "\n";
	}
}

int main()
{
	std::ofstream dictionaryFile("");

	// Demos
	//demoBinaryTree();
	demoTrie();

	return 0;
}