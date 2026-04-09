#include "BinaryTree.h"

TrieDictionary::TrieDictionary(const std::string& value)
{
	insert(value);
}

//std::u32string TrieDictionary::copyCase(const std::u32string& c, const std::u32string& ref)
//{
//	return u_isupper(ref) ? u_toupper(c) : u_tolower(c);
//}

std::u32string TrieDictionary::utf8ToUtf32(const std::string& str) const
{
	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(str);

	std::u32string result;
	for (int32_t i = 0; i < ustr.length(); ++i)
		result.push_back(ustr[i]);


	return result;
}

void TrieDictionary::insertRecurs(const std::u32string& u32Str)
{
	TrieNode* current = treeRoot.get();

	for (size_t i = 0; i < u32Str.size(); ++i)
	{
		std::u32string ch = u32Str.substr(i, 1);
		if (!current->children[ch])
			current->children[ch] = std::make_unique<TrieNode>();
		current = current->children[ch].get();
	}

	current->isLeaf = true;
}

bool TrieDictionary::removeRecurs(TrieNode* root, const std::u32string& key, size_t index)
{
	if (!root)
		return false;

	if (index == key.size())
	{
		if (!root->isLeaf)
			return false;
		root->isLeaf = false;
		return root->children.empty();
		/* If the node is valid and not a leaf,
		whether or not it should be removed depends on if it has children.
		In other words, "big" will not be removed if "l" (or any other nodes) follow it. */
	}

	std::u32string ch = key.substr(index, 1);
	auto it = root->children.find(ch);
	// If the key cannot be found, do not delete the node
	if (it == root->children.end())
		return false;

	// Should the child be deleted?
	bool deleteChild = removeRecurs(it->second.get(), key, index);
	if (deleteChild)
		root->children.erase(ch);

	return !root->isLeaf && root->children.empty();
}

void TrieDictionary::insert(const std::string& value)
{
	insertRecurs(utf8ToUtf32(value));
}

void TrieDictionary::insert(const std::u32string& value)
{
	insertRecurs(value);
}

bool TrieDictionary::remove(const std::string& value)
{
	return removeRecurs(treeRoot.get(), utf8ToUtf32(value), 0);
}

bool TrieDictionary::remove(const std::u32string& value)
{
	return removeRecurs(treeRoot.get(), value, 0);
}

const bool TrieDictionary::depthFirstSearch(const std::string& value) const
{
	return false;
}

const bool TrieDictionary::depthFirstSearch(const std::u32string& value) const
{
	return false;
}

bool TrieDictionary::directSearch(const std::string& value) const
{
	const TrieNode* current = treeRoot.get();
	std::u32string utf32Str = utf8ToUtf32(value);

	for (size_t i = 0; i < utf32Str.size(); ++i)
	{
		/* This creates a temporary utf32string for every character in the utf32Str variable 
			Not performant at all, will probably replace later */
		std::u32string ch = utf32Str.substr(i, 0);

		auto it = current->children.find(ch);
		if (it == current->children.end())
			return false;

		current = it->second.get();
	}

	return current->isLeaf;
}

bool TrieDictionary::directSearch(const std::u32string& value) const
{
	const TrieNode* root = treeRoot.get();

	for (size_t i = 0; i < value.size(); ++i)
	{
		/* This creates a temporary utf32string for every character in the utf32Str variable
			Not performant at all, will probably replace later */
		std::u32string ch = value.substr(i, 0);

		auto it = root->children.find(ch);
		if (it == root->children.end())
			return false;

		root = it->second.get();
	}

	return root->isLeaf;
}

const std::vector<std::u32string> TrieDictionary::directSearchAll(const std::string& value) const
{
	std::vector<std::u32string> foundWords = std::vector<std::u32string>();
	std::u32string utf32Str = utf8ToUtf32(value);

	const TrieNode* current = treeRoot.get();
	std::u32string currentWord;

	for (size_t i = 0; i < utf32Str.size(); ++i)
	{
		std::u32string ch = utf32Str.substr(i, 0);

		auto it = current->children.find(ch);
		if (it == current->children.end())
			break;

		if (current->isLeaf)
			foundWords.push_back(currentWord);
	}

	/* We only want to return the foundWords IF the full word actually exists 
		(aka, do not display partial matches from traversal) */
	if (current->isLeaf && currentWord == utf32Str)
		return foundWords;
	else
		return {};
}

const TrieNode* TrieDictionary::root() const
{
	return treeRoot.get();
}

const bool TrieDictionary::isLeaf(TrieNode* node) const
{
	return node->children.size() == 0;
}
