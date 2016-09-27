#include "Compressor.h"
#include "TreeNode.h"

#include <iostream>
using std::cout;
using std::endl;

using std::string;

using std::map;
using std::multimap;
using std::pair;

#include <bitset>
using std::bitset;

Compressor::Compressor()
{
	uncompressedString = "";
	compressedString = "";
	decompressedString = "";
} // end default constructor

Compressor::Compressor(string text)
{
	uncompressedString = text;
	compressedString = "";
	decompressedString = "";
} // end initializer constructor

Compressor::~Compressor()
{
	deleteTree();
} // end deconstructor

void Compressor::insertString(std::string text)
{
	uncompressedString = text;
} // end insertString

void Compressor::addToString(std::string text)
{
	uncompressedString += text;
} // end addToString

void Compressor::countCharactersInString()
{
	for each (char c in uncompressedString)
	{
		charCount[c] += 1;
	} // end for
	// add null character
	charCount['\0'] += 1;
} // end countCharactersInString

void Compressor::pushCharsIntoQueue()
{
	// push all characters that were counted at least once into the queue
	for (size_t i = 0; i < 256; ++i)
	{
		if (charCount[i] > 0)
		{
			char c = i;
			queue.insert(pair<int, TreeNode *>(charCount[i], new TreeNode(c)));
		}
	} // end for
} // end pushCharsIntoQueue

void Compressor::createTree()
{
	multimap<int, TreeNode *>::iterator one;
	multimap<int, TreeNode *>::iterator two;

	while (queue.size() > 1)
	{
		one = queue.begin(); // get the first
		two = ++queue.begin(); // and second item from the queue

		// combine both leaves into a branch and push it back into the priority queue with their counts combined as int
		queue.insert(pair<int, TreeNode *>(one->first + two->first, new TreeNode(one->second, two->second)));

		// pop the individual leaves from the queue
		queue.erase(one);
		queue.erase(two);
	} // end while

	root = queue.begin()->second;
} // end createTree

void Compressor::fillSymbolTable()
{
	if (root != 0)
	{
		short i = 1; // stores the path traversed through the tree in binary

		fillSymbolTableRecursive(root, i);
	}
} // end fillSymbolTable

void Compressor::fillSymbolTableRecursive(TreeNode * node, short i) // private / utility function
{
	// traverse the tree recursively and when you reach a leave, store the char value and taken path in the symbol table
	if (node->hasChildren)
	{
		i = i << 1; // shit all bits in the path so far one to the left, putting a new 0 on the end
		fillSymbolTableRecursive(node->left, i);
		i = i | 1; // after resolving the left node, change the 0 at the end of the path into 1
		fillSymbolTableRecursive(node->right, i);
	}
	else
	{
		symbolTable.insert(pair<char, short>(node->character, i));
	}
} // end utility function fillSymbolTable

void Compressor::compressString()
{
	compressedString = "";

	bool read;
	char bitCounter = 0; // to count bits per byte
	char compressedChar = 0;

	short treePath;

	// add null character to end of string
	uncompressedString += '\0';

	for each (char uncompressedChar in uncompressedString)
	{
		// find this character in the symbol table and get the path
		treePath = symbolTable.find(uncompressedChar)->second;

		// find the beginning of the tree path, indicated by a leading 1 which is to be ignored
		read = false;
		for (char i = 15; i >= 0; --i)
		{
			if (!read)
			{
				// if position i in the bits of treePath is 1, start reading from the next bit to 0
				if (treePath & 1 << i)
				{
					read = true;
				}
			}
			else
			{
				compressedChar = (compressedChar << 1) + ((treePath & 1 << i) >> i);
				if (bitCounter < 7)
				{
					++bitCounter;
				}
				else
				{
					compressedString += compressedChar;
					bitCounter = 0;
				}
			}
		} // end for
	} // end for each

	// move the last bits into place and write them to the compressed string
	if (bitCounter != 0)
	{
		compressedChar = compressedChar << (8 - bitCounter);
		compressedString += compressedChar;
	}

	// remove previously added null character from the end of the string
	uncompressedString = uncompressedString.substr(0, uncompressedString.length() - 1);
} // end compressString

void Compressor::decompressString()
{
	decompressedString = "";

	TreeNode * currentNode = root;

	for each (char compressedChar in compressedString)
	{
		// follow the path in the tree to get the character
		for (char bitCounter = 7; bitCounter >= 0;)
		{
			if (currentNode->hasChildren)
			{
				if (compressedChar & 1 << bitCounter)
				{
					currentNode = currentNode->right;
				}
				else
				{
					currentNode = currentNode->left;
				}

				--bitCounter;
			}
			else
			{
				if (currentNode->character != '\0')
				{
					decompressedString += currentNode->character;
					currentNode = root;
				}
				else
				{
					break;
				}
			}
		} // end for
	} // end for each

	// put the last character into the string if necessary
	if (!currentNode->hasChildren && currentNode->character != '\0')
	{
		decompressedString += currentNode->character;
	}
} // end decompressString

void Compressor::deleteTree()
{
	if (root != 0)
	{
		deleteTreeRecursive(root);
		root = 0;
	}
} // end deleteTree

void Compressor::deleteTreeRecursive(TreeNode * node) // private / utility function
{
	if (node->hasChildren)
	{
		deleteTreeRecursive(node->left);
		deleteTreeRecursive(node->right);
	}

	delete node;
} // end deleteTreeRecursive

void Compressor::recreateTree()
{
	root = new TreeNode();
	TreeNode * currentNode;

	bool read;
	short treePath;

	for (map<char, short>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
	{
		currentNode = root;
		treePath = i->second;

		// find the beginning of the tree path, indicated by a leading 1 which is to be ignored
		read = false;
		for (char i = 15; i >= 0; --i)
		{
			if (!read)
			{
				// if position i in the bits of treePath is 1, start reading from the next bit to 0
				if (treePath & 1 << i)
				{
					read = true;
				}
			}
			else
			{
				currentNode->hasChildren = true;

				if (treePath & 1 << i)
				{
					if (currentNode->right == 0)
					{
						currentNode->right = new TreeNode();
					}
					currentNode = currentNode->right;
				}
				else
				{
					if (currentNode->left == 0)
					{
						currentNode->left = new TreeNode();
					}
					currentNode = currentNode->left;
				}
			}
		} // end inner for

		// write character to the node that was added last
		currentNode->character = i->first;
	} // end outer for
} // end recreateTree


  // printing debug functions

void Compressor::printUncompressedString()
{
	cout << "Uncompressed string:\n";
	cout << uncompressedString << endl;
} // end printUncompressedString

void Compressor::printCharCount()
{
	cout << "Printing charachter count array.\n";
	for (size_t i = 0; i < 256; ++i)
	{
		cout << i << " = " << charCount[i] << "\t\t";
	} // end for
	cout << endl;
} // end function printCharcount

void Compressor::printCharCountChar()
{
	cout << "Printing charachter count array with characters.\n";
	cout << "Skipping first 32 unprintable chars.\n";
	for (size_t i = 32; i < 256; ++i)
	{
		char c = i;

		cout << c << " = " << charCount[i] << "\t\t";
	} // end for
	cout << endl;
} // end function printCharcount

void Compressor::printQueue()
{
	cout << "Printing character priority queue.\n";
	for (multimap<int, TreeNode *>::iterator i = queue.begin(); i != queue.end(); ++i)
	{
		if (!i->second->hasChildren)
		{
			cout << i->second->character << " : " << i->first << endl;
		}
		else
		{
			cout << "Branch : " << i->first << endl;
		}
	} // end for
} // end function printQueue

void Compressor::traverseTree()
{
	cout << "Traversing tree and printing path with leading 1.\n";
	if (root != 0)
	{
		short i = 1;

		traverseTreeRecursive(root, i);
	}
} // end traverseTree

void Compressor::traverseTreeRecursive(TreeNode * node, short i) // private / utility function
{
	if (node->hasChildren)
	{
		i = i << 1;
		traverseTreeRecursive(node->left, i);
		i = i | 1;
		traverseTreeRecursive(node->right, i);
	}
	else
	{
		bitset<16> x(i);
		cout << x << " : " << node->character << "\n";
	}
} //end utility function traverseTreeRecursive


void Compressor::printSymbolTable()
{
	cout << "Printing symbol table.\n";
	cout << "Ignore leading 1." << endl;
	for (map<char, short>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
	{
		bitset<16> x(i->second);
		cout << i->first << " : " << x << endl;
	} // end for
} // end function printQueue

void Compressor::printCompressedString()
{
	cout << "Compressed string:\n";
	cout << compressedString << endl;
} // end printCompressedString

void Compressor::printDecompressedString()
{
	cout << "Decompressed string:\n";
	cout << decompressedString << endl;
} // end printDecompressedString