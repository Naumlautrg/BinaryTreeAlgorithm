#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <fstream>
#include <unordered_map>

#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include <unicode/normalizer2.h>

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
	/* A unorded_map is used for its low space complexity and fast lookup speed.
		A vector or array *could* be used, but would be not be ideal in its spatial usage 
		since we plan on inserting very large amounts of elements (the initial case being the entire english dictionary) 
		
		Although this implementation with char32_t works and is ideal, 
		it does not account for the rare case in some languages where an uppercase or lowercase letter spans multiple characters
		A simple but heavy performance-cost solution is to use std::u32string instead, but better is to normalize and case-fold input 
		(which is done with normalizeToUtf32)*/

	char32_t data;
	std::unordered_map<char32_t, std::unique_ptr<TrieNode>> children;
	bool isLeaf = false;

	TrieNode(const char32_t& ch = U' ')
		: data(ch) { }
};

class TrieDictionary
{
private:
	std::unique_ptr<TrieNode> treeRoot = std::make_unique<TrieNode>();

	std::u32string utf8ToUtf32(const std::string& str) const;
	std::string utf32ToUtf8(const std::u32string& str) const;
	std::u32string normalizeToUtf32(const std::string& str);

	void insertRecurs(const std::u32string& u32str);
	bool removeRecurs(TrieNode* root, const std::u32string& key, size_t index);

	/* Recursively collects the words beginning with the prefix input */
	void prefixCollection(const TrieNode* node, std::u32string& currentWord, std::vector<std::string>& words) const;

public:
	TrieDictionary() = default;
	TrieDictionary(const std::string& value);

	void insert(const std::string& value);
	bool remove(const std::string& value);

	bool contains(const std::string& value) const;
	/* Returns a vector containing all of the words found during traversal. */
	const std::vector<std::string> inclusiveSearch(const std::string& value);
	/* Returns a vector containing all of the words beginning with the value (autocomplete). */
	const std::vector<std::string> exclusiveSearch(const std::string& value);

	/*
	* @returns treeRoot
	*/
	const TrieNode* root() const;

	const bool isLeaf(TrieNode* node) const;
		
};
