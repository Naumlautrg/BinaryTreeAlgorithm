#include "BinaryTree.h"

TrieDictionary::TrieDictionary(const std::string& value)
{
	treeRoot = std::make_unique<TrieNode>(value);
}

void TrieDictionary::insert(const std::string& value)
{
	TrieNode* current = treeRoot.get();

	for (char ch : value) 
	{
		const int index = ch - 'a';
		if (current->children[index])
		{
			current->children[index] = std::make_unique<TrieNode>();
			current = current->children[index].get();
		}
	}
}

void TrieDictionary::remove(const std::string& value)
{
}

const bool TrieDictionary::breadthFirstSearch(const std::string& value) const
{
	std::queue<TrieNode*> q;
	
	q.push(treeRoot.get());

	while (!q.empty())
	{
		TrieNode* front = q.front();

		if (front->data == value)
			return front;

		for (size_t i = 0; i < front->children.size(); ++i)
			q.push(front->children.at(i));

		q.pop();
	}
}

const bool TrieDictionary::depthFirstSearch(const std::string& value) const
{
	return false;
}

const TrieNode* TrieDictionary::root() const
{
	return treeRoot.get();
}

const bool TrieDictionary::isLeaf(TrieNode* node) const
{
	return node->children.size() == 0;
}
