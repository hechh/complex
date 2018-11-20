#pragma once
#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <memory>
#include <vector>
#include <atomic>
#include <map>
#include <fstream>
#include "Utils.h"
#include "Traits_Type.h"

using namespace type_traits;
using namespace tools;

class ParseFile {
public:
	ParseFile(std::string filepath);
	void PutFileData(std::vector<std::string>&);

private:
	void GetLine(std::fstream& fs, std::string& strline);
	void ParseLine(const std::string& strline,std::map<std::string,std::map<std::string,std::string>>& mapData);
	void ParseLine(std::string& strline,std::map<std::string, std::map<std::string,type_traits::Type>>& mapData);

private:
	std::fstream FileStream_;
};

ParseFile::ParseFile(std::string filepath) : FileStream_(filepath, std::ios_base::binary | std::ios_base::in) {
	if (!FileStream_.is_open()) {
		FileStream_.open(filepath, std::ios_base::in);
	}
}

void ParseFile::GetLine(std::fstream& fs, std::string& strline) {
	strline.clear();
	std::atomic<bool> bflag1 = true;
	std::atomic<bool> bflag2 = true;
	while ((bflag1 || bflag2) && !fs.eof()) {
		std::string strlinetmp;
		char chtemp[2048] = { 0 };
		fs.getline(chtemp, 2048, '\n');
		strlinetmp = chtemp;
		if (Utils::Split(strline,"message",Back)) {
			bflag1 = false;
		}
		if (!bflag1) {
			Utils::DelAnnotation(strlinetmp);
			strline += strlinetmp;
		}
		if (strlinetmp.find("}") != std::string::npos) {
			bflag2 = false;
		}
	}
	Utils::DelSpace(strline);
}

void ParseFile::PutFileData(std::vector<std::string>& vecFileData) {
	while (!FileStream_.eof()) {
		std::string strline;
		GetLine(this->FileStream_, strline);
		if (strline.size() > 0) {
			vecFileData.push_back(strline);
		}
	}
}

void ParseFile::ParseLine(const std::string& strline,std::map<std::string,std::map<std::string,std::string>>& mapData) {
	std::vector<std::string> vecStr;
	std::vector<std::string> vecStr2;
	std::vector<std::string> vecStr3;
	std::string strTmp(strline);

	Utils::Split(strTmp,"}",Front);
	Utils::MultiSplit(strTmp,"{",vecStr);
	
	std::string strTmp01(vecStr.front());
	std::string strTmp02(vecStr.back());

	Utils::DelSpace(strTmp01);
	Utils::MultiSplit(strTmp02,";",vecStr2);

	std::stringstream os;
	for (auto& tmp : vecStr2) {
		Utils::Split(tmp,"=",Front);
		os.str(" ");
		os << tmp;
		std::string strKey;
		std::string strValue;
		os >> strValue >> strKey;
		mapData[strTmp01][strKey] = strValue;
	}
}
