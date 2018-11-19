#pragma once

#include <string>
#include <iostream>
#include <type_traits>
#include <memory>
#include <vector>
#include <atomic>
#include <map>
#include <fstream>

class ParseFile {
public:
	ParseFile(std::string filepath);
	void PutFileData(std::vector<std::string>&);

private:
	void GetLine(std::fstream& fs, std::string& strline);
	void DelAnnotation(std::string& strTmp);
	void ParseLine(std::string& strline, std::map<std::string, std::vector<std::string>>& mapData);
	void DelSpace(size_t& pos1,size_t& pos2,std::string& str);
	void MultiSplit(std::string& strline,std::string spstr,std::map<int,std::string>& mapStr);
	void Split(std::string& strline,std::string spstr,std::map<int,std::string>& mapData);

private:
	std::fstream FileStream_;
};

void ParseFile::DelAnnotation(std::string& strTmp) {
	size_t pos = 0;
	if ((pos = strTmp.find("//")) != std::string::npos) {
		strTmp.resize(pos);
	}
}

ParseFile::ParseFile(std::string filepath): FileStream_(filepath, std::ios_base::binary | std::ios_base::in) {
	if (!FileStream_.is_open()) {
		FileStream_.open(filepath,std::ios_base::in);
	}
}

void ParseFile::GetLine(std::fstream& fs, std::string& strline) {
	strline.clear();
	std::atomic<bool> bflag1 = true;
	std::atomic<bool> bflag2 = true;
	while ((bflag1 || bflag2) && !fs.eof()) {
		std::string strlinetmp;
		char chtemp[1024] = { 0 };
		fs.getline(chtemp, 1024, '\n');
		strlinetmp = chtemp;
		if (strlinetmp.find("message") != std::string::npos) {
			bflag1 = false;
		}
		if(!bflag1){
			DelAnnotation(strlinetmp);
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

void ParseFile::Split(std::string& strline, std::string spstr, std::map<int, std::string>& mapData){
	size_t pos = strline.find(spstr);
	mapData[1] = strline.substr(0,pos);
	size_t tmp = pos + spstr.size();
	mapData[2] = strline.substr(tmp,strline.size()-tmp);
}

void ParseFile::MultiSplit(std::string& strline, std::string spstr,std::map<int,std::string>& mapStr) {
	std::vector<int> vecInt;
	vecInt.push_back(-((int)spstr.size()));
	for (size_t pos = 0; pos = strline.substr(pos,strline.size()-pos).find(spstr) && pos != std::string::npos; vecInt.push_back(pos),pos += spstr.size());
	vecInt.push_back(strline.size());
	std::sort(vecInt.begin(), vecInt.end(), [](int a, int b) { return (a<b); });
	int index = 0;
	for (int i = 0; i < vecInt.size()-1; i++) {
		int ibegin = vecInt[i] + spstr.size();
		int icount = vecInt[i+1] - ibegin;
		if (icount > 0) {
			mapStr[++index] = strline.substr(ibegin, icount);
		}
	}
}

void ParseFile::DelSpace(size_t& pos1, size_t& pos2, std::string& str) {
	for (; str[pos1] == ' ';++pos1);
	for (; str[pos2] == ' '; --pos2);
	str = str.substr(pos1,pos2+1);
}

void ParseFile::ParseLine(std::string& strline, std::map<std::string, std::vector<std::string>>& mapData) {

}

