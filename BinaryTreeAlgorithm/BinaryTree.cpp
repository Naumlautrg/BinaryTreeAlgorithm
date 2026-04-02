#include "BinaryTree.h"

TrieDictionary::TrieDictionary(const std::string& value)
{
	treeRoot = std::make_unique<TrieNode>();
	insert(value);
}

char TrieDictionary::copyCase(const char& c, const char& ref)
{
	// Likely a better way to do this (even if barely impactful)
	if (ref == std::toupper(ref))
		return std::toupper(c);
	else
		return std::tolower(c);
}

void TrieDictionary::insert(const std::string& str)
{
	TrieNode* current = treeRoot.get();

	for (char8_t ch : str)
	{
		const int index = ch - copyCase('a', ch);
		if (current->children[index] == nullptr)
		{
			//current->children[index] = std::make_unique<TrieNode>(value);
			//current = current->children[index].get();
			current->children[index] = new TrieNode(str[index]);
			current = current->children[index];
		}
	}

	current->isLeaf = true;
}

void TrieDictionary::remove(const char8_t& value)
{
}

const bool TrieDictionary::breadthFirstSearch(const char8_t& value) const
{
	std::queue<TrieNode*> q;
	
	q.push(treeRoot.get());

	while (!q.empty())
	{
		TrieNode* front = q.front();

		if (front->data == value)
			return front;

		for (size_t i = 0; i < front->children.size(); ++i)
			//q.push(front->children.at(i).get());
			q.push(front->children.at(i));

		q.pop();
	}

	// placeholder return value
	return false;
}

const bool TrieDictionary::depthFirstSearch(const char8_t& value) const
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
