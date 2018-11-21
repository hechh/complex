#pragma once

#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <map>

namespace TypeSpace {
	struct proto_s;
}



class ParseProtoFile {
public:
	ParseProtoFile(std::string filepath);
	void GetFileData(std::vector<std::string>&);
	void ParseLine(const std::vector<std::string>& veclinge, std::map<std::string,std::map<std::string, TypeSpace::proto_s>>& mapData);
	void GetAllType(std::map<std::string, std::map<std::string, TypeSpace::proto_s>>& mapData, std::list<TypeSpace::proto_s>& lstType);

private:
	void GetLine(std::fstream& fs, std::string& strline);

private:
	std::fstream FileStream_;
};






