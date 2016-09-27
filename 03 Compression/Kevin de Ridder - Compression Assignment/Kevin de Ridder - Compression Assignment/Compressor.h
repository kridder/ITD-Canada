#pragma once

#include <string>
#include <map>

class TreeNode;

class Compressor
{
public:
	Compressor();
	Compressor(std::string text);
	~Compressor();
	void insertString(std::string text);
	void addToString(std::string text);
	void countCharactersInString();
	void pushCharsIntoQueue();
	void createTree();
	void fillSymbolTable();
	void compressString();
	void decompressString();
	void deleteTree();
	void recreateTree();

	// printing debug functions
	void printUncompressedString();
	void printCharCount();
	void printCharCountChar();
	void printQueue();
	void traverseTree();
	void printSymbolTable();
	void printCompressedString();
	void printDecompressedString();
protected:
	std::string uncompressedString;
	int charCount[256] = {0};
	std::multimap<int, TreeNode *> queue;
	TreeNode * root;
	std::map<char, short> symbolTable;
	std::string compressedString;
	std::string decompressedString;

	// utility functions
	void fillSymbolTableRecursive(TreeNode * node, short i);
	void traverseTreeRecursive(TreeNode * node, short i);
	void deleteTreeRecursive(TreeNode * node);
};