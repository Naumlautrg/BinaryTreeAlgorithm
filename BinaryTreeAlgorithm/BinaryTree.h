#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <cctype>

template<typename T>
struct Node
{
	T data;
	std::unique_ptr<Node<T>> left;
	std::unique_ptr<Node<T>> right;

	Node<T>(const T& key)
		: data(key), left(nullptr), right(nullptr) { }
};

template<typename T>
class BinaryTree
{
private:
	std::unique_ptr<Node<T>> treeRoot = nullptr;
	size_t treeSize;

	void insertRecurs(std::unique_ptr<Node<T>>& root, const T& data)
	{
		if (!root)
		{
			root = std::make_unique<Node<T>>(data);
		}
		else if (data < root.get()->data)
			insertRecurs(root->left, data);
		else if (data > treeRoot.get()->data)
			insertRecurs(root->right, data);

		treeSize++;
	}

	void removeRecurs(std::unique_ptr<Node<T>>& root, const T& data)
	{
		// Nothing to remove
		if (!root)
			return;
		else if (data == root->data)
			root = nullptr;
		else if (data < treeRoot.get()->data)
			removeRecurs(root->left, data);
		else if (data > treeRoot.get()->data)
			removeRecurs(root->right, data);
	}

	void preorderPrintRecurs(const Node<T>* root) const
	{
		if (root)
		{
			std::cout << root->data << " ";
			preorderPrintRecurs(root->left.get());
			preorderPrintRecurs(root->right.get());
		}
	}

public:
	BinaryTree() = default;
	BinaryTree(const T& key)
	{
		treeRoot = std::make_unique<Node<T>>(key);

		treeSize = 1;
	}

	void insert(const T& data)
	{
		insertRecurs(treeRoot, data);
	}

	void remove(const T& data)
	{
		removeRecurs(treeRoot, data);
	}

	bool contains(Node<T>* root, const T& data) const
	{
		// Tree is empty
		if (!root)
			return false;
		// Data found
		else if (data == root->data)
			return true;
		// Data must be in left subtree
		else if (data < root->data)
			return contains(root->left.get(), data);
		// Data must be in right subtree
		else if (data > root->data)
			return contains(root->right.get(), data);
	}

	const Node<T>* root() const
	{
		return treeRoot.get();
	}

	const size_t size() const
	{
		return treeSize;
	}

	/*
	* This function assumes an ostream operator overload exists for the type T
	* This uses preorder traversal, meaning the root node is processed first, then the left subtree, and finally the right subtree
	*/
	void preorderPrint() const
	{
		preorderPrintRecurs(treeRoot.get());
	}
};

struct TrieNode
{
	char8_t data;
	//std::vector<std::unique_ptr<TrieNode>> children;
	std::vector<TrieNode*> children;
	bool isLeaf;

	TrieNode()
		: data(' '), children(std::vector<TrieNode*>(26)), isLeaf(false) { }
	TrieNode(const char8_t& data)
		: data(data), children(std::vector<TrieNode*>(26)), isLeaf(false) { }
	//TrieNode(const std::string& data, const std::vector<std::unique_ptr<TrieNode>>& children)
	//	: data(data), children(children), isLeaf(false) { }
	TrieNode(const char8_t& data, const std::vector<TrieNode*>& children)
		: data(data), children(children), isLeaf(false) { }
};

struct Language
{
	char8_t startOfAlphabet;
	int lettersInAlphabet;
};

class TrieDictionary
{
private:
	std::unique_ptr<TrieNode> treeRoot = nullptr;

	/*
	* @returns The uppercase or lowercase of argument c, depending on the case of the ref
	*/
	char copyCase(const char& c, const char& ref);

public:
	TrieDictionary() = default;
	TrieDictionary(const std::string& value);

	void insert(const std::string& value);

	void remove(const char8_t& value);

	// Pending documentation
	const bool breadthFirstSearch(const char8_t& value) const;

	// Pending documentation
	const bool depthFirstSearch(const char8_t& value) const;

	/*
	* @returns treeRoot
	*/
	const TrieNode* root() const;

	const bool isLeaf(TrieNode* node) const;
		
};
