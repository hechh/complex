#include <iostream>
#include <string>
#include <type_traits>
#include <array>
#include "ParseFile.h"


std::string path("F:\\workspace\\Project2\\Project2\\test.proto");

int main() 
{
	ParseFile file(path);

	std::vector<std::string> vecTemp;
	file.PutFileData(vecTemp);
	//std::map<int, std::string> mapStr;
	//Utils::MultiSplit(vecTemp[0],"=",mapStr);
	//std::vector<int> vecInt;
	//std::map<int, std::string> mapStr;
	//std::vector<std::string> vecStr;
	//std::string str("adnafd==akd,;kjadspoikle=adfa");
//	Utils::MultiSplit(str,"=",vecStr);


	//Utils::Find(str,"=",vecInt);
//	Utils::Find(str,"=",vecInt);
	system("pause");
	return 0;
}