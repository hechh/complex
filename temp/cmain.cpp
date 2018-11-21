#include "ParseProtoFile.h"
#include "Define.h"
#include <vector>
#include <map>


std::string path("F:\\workspace\\Project2\\Project2\\test.proto");


int main() 
{
	//std::string str("11");
	//int i = 0;
	//for (; str[i] == '1';i++);
	std::vector<std::string> vecStr;
	std::map<std::string,std::map<std::string,TypeSpace::proto_s>> tmp;
	ParseProtoFile test(path);
	test.GetFileData(vecStr);
	test.ParseLine(vecStr,tmp);
	//std::map<int, TypeSpace::proto_s> test;
	//test[0]=TypeSpace::proto_s();
	system("pause");
	return 0;
}