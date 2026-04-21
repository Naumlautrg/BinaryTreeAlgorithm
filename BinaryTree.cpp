#include "BinaryTree.h"

TrieDictionary::TrieDictionary(const std::string& value)
{
	insert(value);
}

std::u32string TrieDictionary::utf8ToUtf32(const std::string& str) const
{
	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(str);

	std::u32string result;
	for (int32_t i = 0; i < ustr.length(); ++i)
		result.push_back(ustr[i]);

	return result;
}

std::string TrieDictionary::utf32ToUtf8(const std::u32string& str) const
{
	icu::UnicodeString u32Str = icu::UnicodeString::fromUTF32(
		reinterpret_cast<const UChar32*>(str.data()),
		static_cast<int32_t>(str.length()));
	std::string utf8Str;

	return u32Str.toUTF8String(utf8Str);
}

std::u32string TrieDictionary::normalizeToUtf32(const std::string& str)
{
	UErrorCode errorCode = UErrorCode::U_ZERO_ERROR;

	icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(str);

	// magic icu code to be interpreted and understood at a later date
	const icu::Normalizer2* normalizer = icu::Normalizer2::getNFCInstance(errorCode);
	icu::UnicodeString normalized;
	normalizer->normalize(ustr, normalized, errorCode);

	normalized.foldCase();

	std::u32string result;
	result.reserve(normalized.length());

	for (int32_t i = 0; i < normalized.length(); )
	{
		UChar32 c = normalized.char32At(i);
		result.push_back(static_cast<char32_t>(c));
		i += U16_LENGTH(c);
	}

	return result;
}

void TrieDictionary::insertRecurs(const std::u32string& u32Str)
{
	TrieNode* current = treeRoot.get();

	// Looping through the tree until there is no further children, then creating a node at that position
	for (char32_t ch : u32Str)
	{
		std::unique_ptr<TrieNode>& child = current->children[ch];
		if (!child)
			child = std::make_unique<TrieNode>();

		current = child.get();
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
		In other words, "big" will not be removed if "l" (or some other node) follow it. */
	}

	char32_t ch = key[index];
	auto it = root->children.find(ch);
	// If the key cannot be found, do not delete the node
	if (it == root->children.end())
		return false;

	// Should the child be deleted?
	bool deleteChild = removeRecurs(it->second.get(), key, index + 1);
	if (deleteChild)
		root->children.erase(it);

	// This node should be deleted if it not the end of another word and has no children 
	return !root->isLeaf && root->children.empty();
}

void TrieDictionary::prefixCollection(const TrieNode* node, std::u32string& currentWord, std::vector<std::string>& words) const
{
	// If the node is a leaf, a word ends at this node
	if (node->isLeaf)
		words.push_back(utf32ToUtf8(currentWord));

	// Exploring all children for what might come next in the loop below
	// "const auto& [ch, child]" this is called structured binding, very cool
	for (const auto& [ch, child] : node->children)
	{
		currentWord.push_back(ch);
		prefixCollection(child.get(), currentWord, words);
		currentWord.pop_back(); // undoing the previous step after exploring it
	}
}

void TrieDictionary::insert(const std::string& value)
{
	std::u32string utf32Str = normalizeToUtf32(value);
	insertRecurs(utf32Str);
}

bool TrieDictionary::remove(const std::string& value)
{
	std::u32string utf32Str = normalizeToUtf32(value);
	return removeRecurs(treeRoot.get(), utf32Str, 0);
}

void TrieDictionary::clear()
{
	treeRoot.get()->children.clear();
}

bool TrieDictionary::contains(const std::string& value) const
{
	const TrieNode* root = treeRoot.get();

	for (char32_t ch : value)
	{
		auto it = root->children.find(ch);
		if (it == root->children.end())
			return false;

		root = it->second.get();
	}
	return root->isLeaf;
}

const std::vector<std::string> TrieDictionary::inclusiveSearch(const std::string& value)
{
	std::vector<std::string> foundWords = std::vector<std::string>();
	std::u32string utf32Str = normalizeToUtf32(value);

	const TrieNode* current = treeRoot.get();
	std::u32string currentWord;

	for (char32_t ch : utf32Str)
	{
		auto it = current->children.find(ch);
		if (it == current->children.end())
			break;

		current = it->second.get();
		currentWord += ch;

		if (current->isLeaf)
			foundWords.push_back(utf32ToUtf8(currentWord));
	}

	/* We only want to return the foundWords IF the full word actually exists
		essentially, do not display partial matches from traversal if an exact match is absent */
	if (current->isLeaf && currentWord == utf32Str)
		return foundWords;
	else
		return {};
}

const std::vector<std::string> TrieDictionary::exclusiveSearch(const std::string& value)
{
	std::vector<std::string> foundWords = std::vector<std::string>();
	std::u32string utf32Str = normalizeToUtf32(value);

	const TrieNode* current = treeRoot.get();

	// Traverse the entire prefix
	for (char32_t ch : utf32Str)
	{
		auto it = current->children.find(ch);
		if (it == current->children.end())
			return {};

		current = it->second.get();
	}

	// Collect every completion to the prefix
	std::u32string currentWord = utf32Str;
	prefixCollection(current, currentWord, foundWords);

	return foundWords;
}

const TrieNode* TrieDictionary::root() const
{
	return treeRoot.get();
}

const bool TrieDictionary::isLeaf(TrieNode* node) const
{
	return node->children.size() == 0;
}
