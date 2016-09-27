#include "FileCompressor.h"

using std::string;

using std::map;
using std::multimap;
using std::pair;

#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ios;

#include <fstream>
using std::ifstream;
using std::ofstream;

FileCompressor::FileCompressor()
{
	uncompressedFilename = "";
	compressedFilename = "";
	compressedString = "";
	decompressedString = "";
} // end default constructor

FileCompressor::FileCompressor(std::string uncompressedFilename, std::string compressedFilename)
{
	this->uncompressedFilename = uncompressedFilename;
	this->compressedFilename = compressedFilename;
	compressedString = "";
	decompressedString = "";
} // end initializer constructor

FileCompressor::~FileCompressor()
{

} // end destructor

void FileCompressor::setUncompressedFile(std::string filename)
{
	uncompressedFilename = filename;
} // end insertFile

void FileCompressor::setCompressedFile(std::string filename)
{
	compressedFilename = filename;
} // end setOutputFile

void FileCompressor::compressFile()
{
	string substring;
	uncompressedString = "";

	// open file to read
	ifstream inputFile(uncompressedFilename, ios::in);
	if (!inputFile)
	{
		cerr << "ERROR: Source file could not be opened.\n";
		return;
	}

	// read file into uncompressed string
	while (!inputFile.eof() && inputFile)
	{
		getline(inputFile, substring);
		uncompressedString += substring + '\n';
	} // end while

	inputFile.close();

	// remove last added '\n' from the end of the string
	uncompressedString = uncompressedString.substr(0, uncompressedString.length() - 1);

	countCharactersInString();
	pushCharsIntoQueue();
	createTree();
	fillSymbolTable();
	compressString();

	// open file for writing
	ofstream outputFile(compressedFilename, ios::out | ios::binary);
	if (!outputFile)
	{
		cerr << "ERROR: Destination file could not be opened.\n";
		return;
	}

	// write symbol table to file
	for (map<char, short>::iterator i = symbolTable.begin(); i != symbolTable.end(); ++i)
	{
		outputFile << i->first;
		outputFile.write(reinterpret_cast<const char *>(&i->second), sizeof(i->second)); // write short in char (write in bytes instead of ints)

	} // end for
	// end symbol table with null character
	outputFile << '\0';

	outputFile << compressedString;

	outputFile.close();

	cout << "File compressed successfully.\n";
} // end compressFile

void FileCompressor::decompressFile()
{
	char c;
	short s;
	bool nullCount = false;

	string substring;
	compressedString = "";
	symbolTable.clear();
	deleteTree();

	// open file to read
	ifstream inputFile(compressedFilename, ios::in | ios::binary);
	if (!inputFile)
	{
		cerr << "ERROR: Source file could not be opened.\n";
		return;
	}

	// read symbol table
	while (!inputFile.eof() && inputFile)
	{
		// read character
		inputFile.get(c);
		if (c == '\0')
		{
			if (nullCount) // check if an earlier null character was encountered (there is one in the table that should be read)
			{
				break;
			}
			else
			{
				nullCount = true;
			}
		}

		// read index (short)
		inputFile.read(reinterpret_cast<char *>(&s), sizeof(s)); // read short in char (read in bytes instead of ints)

		symbolTable.insert(pair<char, short>(c, s));
	} // end while

	// read file into compressed string
	while (!inputFile.eof() && inputFile)
	{
		getline(inputFile, substring);
		compressedString += substring + '\n';
	} // end while

	inputFile.close();

	// remove last added '\n' from the end of the string
	compressedString = compressedString.substr(0, compressedString.length() - 1);

	recreateTree();
	decompressString();

	// write decompressed string to ouput file
	ofstream outputFile(uncompressedFilename, ios::out);
	if (!outputFile)
	{
		cerr << "ERROR: Destination file could not be opened.\n";
		return;
	}

	outputFile << decompressedString;

	outputFile.close();

	cout << "File decompressed successfully.\n";
} // end readCompressedFile