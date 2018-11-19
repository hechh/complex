#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <memory>
#include <vector>
#include <atomic>
#include <map>
#include <fstream>
#include "Utils.h"



class ParseFile {
public:
	ParseFile(std::string filepath);
	void PutFileData(std::vector<std::string>&);

private:
	void GetLine(std::fstream& fs, std::string& strline);
	void ParseLine(std::string& strline, std::map<std::string, std::vector<std::string>>& mapData);

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
		if (strlinetmp.find("message") != std::string::npos) {
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


void ParseFile::ParseLine(std::string& strline, std::map<std::string, std::vector<std::string>>& mapData) {
	std::vector<std::string> vecStr;
	std::vector<std::string> vecStr2;
	std::vector<std::string> vecStr3;

	std::string strTemp(strline.substr(0, strline.find("}")));
	Utils::Split(strTemp, "{", vecStr);

	Utils::Split(vecStr.front(), " ", vecStr2);
	Utils::MultiSplit(vecStr.back(), ";", vecStr3);

	std::string strTemp(vecStr2.back());
	for (auto& tmp : vecStr3) {
		mapData[Utils::DelSpace(0, strTemp.size()-1,strTemp)].push_back(Utils::DelSpace(0,tmp.size()-1,tmp));
	}
}

