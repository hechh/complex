#include <iostream>
#include <string>
#include <type_traits>
#include <array>
#include "ParseFile.h"


std::string path("C:\\Users\\huayun02\\Desktop\\test.proto");

int main() 
{
	ParseFile file(path);

	std::vector<std::string> vecTemp;
	file.PutFileData(vecTemp);

	system("pause");
	return 0;
}