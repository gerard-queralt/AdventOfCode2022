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

std::vector<std::string> CppFileReader::InputAsLines(const std::string& inputContents)
{
	return SplitStringAtChar(inputContents, '\n');
}

std::vector<std::string> CppFileReader::InputAsLines(int day)
{
	std::string fileContents = ReadInputOfDay(day);
	return InputAsLines(fileContents);
}

std::vector<std::string> CppFileReader::SplitStringAtChar(const std::string& string, char splitAt)
{
	std::vector<std::string> splitString {""};
	for (char c : string)
	{
		if (c != splitAt)
		{
			int lastIndex = splitString.size() - 1;
			splitString[lastIndex].push_back(c);
		}
		else
		{
			//this will cause an extra line to be added
			splitString.push_back("");
		}
	}
	//remove the extra line
	splitString.pop_back();
	return splitString;
}