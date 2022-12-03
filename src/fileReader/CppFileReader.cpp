#include "CppFileReader.h"

#include <fstream>

std::string CppFileReader::ReadInputOfDay(int day)
{
    std::ifstream file;
	std::string fileContents = "";
	std::string fileLine;

	std::string dayInputPath = std::string("..\\day" + std::to_string(day) + "\\input.txt");
	file.open(dayInputPath);

	if (file.is_open()) {
		while (std::getline(file, fileLine)) {
			fileContents += fileLine + "\n";
		}
		file.close();
	}

	return fileContents;
}