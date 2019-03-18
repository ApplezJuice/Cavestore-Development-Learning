#pragma once

#include <string>
namespace ApplezEng
{
	// not in a class so we need to tell the compiler to look elsewhere
	extern void fatalError(std::string errorString);
}