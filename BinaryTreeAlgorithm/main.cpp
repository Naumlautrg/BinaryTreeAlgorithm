#include <iostream>

#include "BinaryTree.h"
#include <unicode/ustream.h>

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
	dict.insert("Wotonon");
	dict.insert("Wo");
	dict.insert("Wor");
	dict.insert("Word");
	std::cout << dict.directSearch("Word") << "\n";
	std::vector<std::u32string> words = dict.directSearchAll("Word");
	for (int i = 0; i < words.size(); ++i)
	{
		icu::UnicodeString ustr = icu::UnicodeString::fromUTF32(
			reinterpret_cast<const UChar32*>(words[i].c_str()), words[i].length());
		std::cout << ustr << "\n";
	}
}

int main()
{
	//demoBinaryTree();
	demoTrie();

	return 0;
}