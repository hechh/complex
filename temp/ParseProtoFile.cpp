#include <atomic>
#include "Utils.h"
#include "Define.h"
#include "ParseProtoFile.h"


using namespace tools;
using namespace TypeSpace;


void ParseProtoFile::GetAllType(std::map<std::string, std::map<std::string, proto_s>>& mapData, std::list<proto_s>& lstType) {
	proto_s tmp_s;
	for (auto& tmp01 : mapData) {
		tmp_s.bRepeated_ = false;
		tmp_s.strType_ = tmp01.first;
		lstType.push_back(tmp_s);
		tmp_s.Clear();
		for (auto& tmp02 : tmp01.second) {
			lstType.push_back(tmp02.second);
		}
	}
}

ParseProtoFile::ParseProtoFile(std::string filepath) : FileStream_(filepath, std::ios_base::binary | std::ios_base::in) {
	if (!FileStream_.is_open()) {
		FileStream_.open(filepath, std::ios_base::in);
	}
}

void ParseProtoFile::GetLine(std::fstream& fs, std::string& strline) {
	strline.clear();
	std::atomic<bool> bflag1 = true;
	std::atomic<bool> bflag2 = true;
	while ((bflag1 || bflag2) && !fs.eof()) {
		std::string strlinetmp;
		char chtemp[2048] = { 0 };
		fs.getline(chtemp, 2048, '\n');
		strlinetmp = chtemp;
		if (Utils::Split(strlinetmp, "message", Back)) {
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

void ParseProtoFile::GetFileData(std::vector<std::string>& vecFileData) {
	while (!FileStream_.eof()) {
		std::string strline;
		GetLine(this->FileStream_, strline);
		if (strline.size() > 0) {
			Utils::DelTab(strline);
			Utils::DelSpace(strline);
			vecFileData.push_back(strline);
		}
	}
}

void ParseProtoFile::ParseLine(const std::vector<std::string>& vecline, std::map<std::string, std::map<std::string, proto_s>>& mapData)
{
	std::vector<std::string> vecStr;
	std::vector<std::string> vecStr2;
	for (auto strTmp : vecline) {
		Utils::Split(strTmp, "}", Front);
		Utils::MultiSplit(strTmp, "{", vecStr);

		std::string strTmp01(vecStr.front());
		std::string strTmp02(vecStr.back());
		vecStr.clear();
		Utils::DelSpace(strTmp01);
		Utils::MultiSplit(strTmp02, ";", vecStr2);
		proto_s tmp_s;
		std::string strKey;
		for (auto& tmp : vecStr2) {
			Utils::Split(tmp, "=", Front);
			Utils::DelSpace(tmp);
			if (tmp.size() < 1) {
				continue;
			}
			if (tmp.find("repeated") != std::string::npos) {
				tmp_s.bRepeated_ = true;
				Utils::Split(tmp, "repeated", Back);
			}
			Utils::GetKeyValue(tmp, strKey, tmp_s.strType_);
			mapData[strTmp01][strKey] = tmp_s;
			tmp_s.Clear();
			strKey.clear();
		}
		vecStr2.clear();
	}
}
