#include <iostream>

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

	dict.insert("Word");
}

int main()
{
	//demoBinaryTree();
	demoTrie();

	return 0;
}