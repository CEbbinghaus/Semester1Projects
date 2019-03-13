#pragma once
#include <string>
#include <sstream>

class FileIO
{
	const char name[9] = "Settings";
public:
	bool write(std::stringstream& buffer);
	bool read(std::stringstream& buffer);
	bool setSize(int size);
};

