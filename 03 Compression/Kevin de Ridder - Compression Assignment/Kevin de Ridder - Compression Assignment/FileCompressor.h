#pragma once

#include "TreeNode.h"
#include "Compressor.h"

#include <string>
#include <map>

class FileCompressor : public Compressor
{
public:
	FileCompressor();
	FileCompressor(std::string uncompressedFilename, std::string compressedFilename);
	~FileCompressor();
	void setUncompressedFile(std::string filename);
	void setCompressedFile(std::string filename);
	void compressFile();
	void decompressFile();
private:
	std::string uncompressedFilename;
	std::string compressedFilename;
};