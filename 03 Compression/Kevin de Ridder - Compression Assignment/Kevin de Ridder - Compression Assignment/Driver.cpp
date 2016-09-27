#include "FileCompressor.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

void oldTestMain();

int main()
{
	FileCompressor fileCompressor;
	int userInput;
	string stringInput;

	while (true)
	{
		cout << "1: Compress file.\n"
			"2: Decompress file.\n"
			"0: Quit.\n\n";
		cin >> userInput;
		cout << endl;

		if (userInput == 0)
		{
			break;
		}
		else if (userInput == 1)
		{
			cin.ignore(1000, '\n');

			cout << "Enter the filename of the source file:\n";
			getline(cin, stringInput);
			cout << endl;

			fileCompressor.setUncompressedFile(stringInput);

			cout << "Enter the filename of the destination file:\n";
			getline(cin, stringInput);
			cout << endl;

			fileCompressor.setCompressedFile(stringInput);

			fileCompressor.compressFile();
			cout << endl;
		}
		else if (userInput == 2)
		{
			cin.ignore(1000, '\n');

			cout << "Enter the filename of the source file:\n";
			getline(cin, stringInput);
			cout << endl;

			fileCompressor.setCompressedFile(stringInput);

			cout << "Enter the filename of the destination file:\n";
			getline(cin, stringInput);
			cout << endl;

			fileCompressor.setUncompressedFile(stringInput);

			fileCompressor.decompressFile();
			cout << endl;
		}
		else if (userInput == 3) // for debugging
		{
			cin.ignore(1000, '\n');
			oldTestMain();
		}
	}

	return 0;
} // end main

void oldTestMain()
{
	cout << "==============================================================\n";
	cout << "String Compressing:\n";
	cout << endl;

	Compressor compressor;

	compressor.printCharCount();
	cout << endl;

	compressor.insertString("Hello world, how are you doing?");
	compressor.countCharactersInString();

	compressor.printCharCount();
	cout << endl;

	compressor.printCharCountChar();
	cout << endl;

	compressor.pushCharsIntoQueue();
	compressor.printQueue();
	cout << endl;

	compressor.createTree();

	compressor.printQueue();
	cout << endl;

	compressor.traverseTree();
	cout << endl;

	compressor.fillSymbolTable();
	compressor.printSymbolTable();
	cout << endl;

	compressor.compressString();

	compressor.printUncompressedString();
	cout << endl;

	compressor.printCompressedString();
	cout << endl;

	compressor.decompressString();

	compressor.printDecompressedString();
	cout << endl;

	cout << "Press enter to continue to file compression...\n";
	getchar();

	cout << "==============================================================\n";
	cout << "File Compressing:\n";
	cout << endl;

	FileCompressor fileCompressor("Input.txt", "CompressedOutput.txt");

	fileCompressor.compressFile();
	cout << endl;

	fileCompressor.printUncompressedString();
	cout << endl;

	fileCompressor.printCharCountChar();
	cout << endl;

	fileCompressor.printSymbolTable();
	cout << endl;

	fileCompressor.printCompressedString();
	cout << endl;

	fileCompressor.decompressString();

	fileCompressor.printDecompressedString();
	cout << endl;

	cout << "Press enter to continue to file decompression...\n";
	getchar();

	cout << "==============================================================\n";
	cout << "File Decompressing:\n";
	cout << endl;

	fileCompressor.setUncompressedFile("DecompressedOutput.txt");

	fileCompressor.decompressFile();
	cout << endl;

	fileCompressor.printSymbolTable();
	cout << endl;

	fileCompressor.printCompressedString();
	cout << endl;

	fileCompressor.printDecompressedString();
	cout << endl;
}