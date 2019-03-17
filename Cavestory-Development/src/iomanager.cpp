#include "headers/iomanager.h"

#include <fstream>

bool iomanager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	// file path, flags passed in binary format
	// std::ios::binary says we are reading in via a binary format
	std::ifstream file(filePath, std::ios::binary);

	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// successfully opened the file, now we need to read the entire file into the buffer
	// assume the buffer is 0
	// need to determine how big the file is via seek g and tell g, seek to the very end of the file, and see how many bytes the file is

	//seek to the end
	// first thing is a byte offset
	// so seek to 0 bytes at the end of the file
	file.seekg(0, std::ios::end);

	// get the file size
	// returns an int of how many bytes are before the current location, which we are at the end of the file
	int fileSize = file.tellg();

	// now seek back to the beginning to read the file
	file.seekg(0, std::ios::beg);

	// at the top of every file there is a file header, we don't want to read that in our file size
	// reduce the filesize by any header bytes that might be present
	fileSize -= file.tellg();

	// read in the file into the buffer
	buffer.resize(fileSize);
	// get the address of the first element in the array then how many bytes we want to read
	file.read((char *)&(buffer[0]), fileSize);
	file.close();
	return true;
}