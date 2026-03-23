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

int main()
{
	demoBinaryTree();

	return 0;
}