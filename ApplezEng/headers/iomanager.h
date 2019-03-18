#pragma once

#include <vector>
namespace ApplezEng
{
	class iomanager
	{
		// static class, only 1 instance of the class
		// only need 1 iomanager, no need to have multiple
	public:
		// buffer is another name for an array
		// pass in a reference of a buffer
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}