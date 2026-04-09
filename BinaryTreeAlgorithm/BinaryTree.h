#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <fstream>
#include <unordered_map>

/*	!!! Requires the "icu" vcpkg package
		vcpkg install icu
		This is needed for unicode functionality so that any language can be inserted into a TrieDictionary. */
#include <unicode/uchar.h>
#include <unicode/unistr.h>

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
		A vector or array *could* be used, but would be unkind in its memory usage since we plan on inserting very large amounts of elements */

	std::u32string data;
	//std::vector<std::unique_ptr<TrieNode>> children;
	std::unordered_map<std::u32string, std::unique_ptr<TrieNode>> children;
	bool isLeaf = false;

	TrieNode(const std::u32string& str = U"")
		: data(str) { }
};

class TrieDictionary
{
private:
	std::unique_ptr<TrieNode> treeRoot = std::make_unique<TrieNode>();

	std::u32string utf8ToUtf32(const std::string& str) const;

	void insertRecurs(const std::u32string& u32str);
	bool removeRecurs(TrieNode* root, const std::u32string& key, size_t index);

	//bool depthFirstSearchRecurs(const TrieNode* node, const std::u32string& key, size_t index) const;

public:
	TrieDictionary() = default;
	TrieDictionary(const std::string& value);

	void insert(const std::string& value);
	void insert(const std::u32string& value);

	bool remove(const std::string& value);
	bool remove(const std::u32string& value);

	const bool depthFirstSearch(const std::string& value) const;
	const bool depthFirstSearch(const std::u32string& value) const;
	bool directSearch(const std::string& value) const;
	bool directSearch(const std::u32string& value) const;
	/* Returns a vector containing all of the valid words found during traversal. */
	const std::vector<std::u32string> directSearchAll(const std::string& value) const;

	/*
	* @returns treeRoot
	*/
	const TrieNode* root() const;

	const bool isLeaf(TrieNode* node) const;
		
};
