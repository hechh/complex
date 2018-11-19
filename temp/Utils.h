#ifndef _UTILS_H_
#define _UTILS_H_

class Utils {
public:
	static void DelAnnotation(std::string& strTmp);
	static std::string& DelSpace(size_t pos1, size_t pos2, std::string& str);
	static void MultiSplit(const std::string& strline, std::string spstr, std::map<int, std::string>& mapStr);
	static void Split(const std::string& strline, std::string spstr, std::map<int, std::string>& mapData);
	static void Find(const std::string& strline, std::string strfind, std::vector<int>& vecInt);
	static void MultiSplit(const std::string& strline,std::string spstr,std::vector<std::string>& vecStr);
	static void Split(const std::string& strline, std::string spstr, std::vector<std::string>& vecStr);

private:
};

void Utils::MultiSplit(const std::string& strline, std::string spstr, std::vector<std::string>& vecStr) {
	std::string strTemp(strline);
	for (;; ) {
		int	pos = strTemp.find(spstr);
		if (pos != std::string::npos) {
			vecStr.push_back(strTemp.substr(0, pos));
			strTemp = strTemp.substr(pos + spstr.size(), std::string::npos);
		}
		else {
			vecStr.push_back(strTemp);
			break;
		}
	}
}
void Utils::Split(const std::string& strline, std::string spstr, std::vector<std::string>& vecStr) {
	size_t pos = strline.find(spstr);
	if (pos != std::string::npos && pos > 0) {
		vecStr.push_back(strline.substr(0, strline.find(spstr)));
		vecStr.push_back(strline.substr(pos + spstr.size(), std::string::npos));
	}
}

void Utils::Find(const std::string& strline, std::string strfind, std::vector<int>& vecInt) {
	std::string strTemp(strline);
	std::map<int, std::string> vecTemp;
	MultiSplit(strline, strfind, vecTemp);
	for (int i = 0; i < vecTemp.size() - 1; i++) {
		if (i == 0) {
			vecInt.push_back(vecTemp[i].size());
		}
		else
			vecInt.push_back(vecTemp[i].size() + strfind.size() + vecInt.back());
	}
}
void Utils::DelAnnotation(std::string& strTmp) {
	size_t pos = 0;
	if ((pos = strTmp.find("//")) != std::string::npos) {
		strTmp.resize(pos);
	}
}

void Utils::Split(const std::string& strline, std::string spstr, std::map<int, std::string>& mapData) {
	size_t pos = strline.find(spstr);
	if (pos != std::string::npos && pos > 0) {
		mapData[1] = strline.substr(0, strline.find(spstr));
		mapData[2] = strline.substr(pos + spstr.size(), std::string::npos);
	}
}

void Utils::MultiSplit(const std::string& strline, std::string spstr, std::map<int, std::string>& mapStr) {
	std::string strTemp(strline);
	int i = 0;
	for (;; ) {
		int	pos = strTemp.find(spstr);
		if (pos != std::string::npos) {
			mapStr[i++] = strTemp.substr(0, pos);
			strTemp = strTemp.substr(pos + spstr.size(), std::string::npos);
		}
		else {
			mapStr[i++] = strTemp;
			break;
		}
	}
}

std::string& Utils::DelSpace(size_t pos1, size_t pos2, std::string& str) {
	size_t postmp1 = pos1;
	size_t postmp2 = pos2;
	const std::string strTable("\r\t\n ");
	std::vector<int> vecInt;
	Find(str,"\r",vecInt);
	Find(str,"\t",vecInt);
	Find(str,"\n",vecInt);
	std::sort(vecInt.begin(), vecInt.end(), [](int a, int b) { return (a < b); });
	for (auto tmp : vecInt) {
		str[tmp] = ' ';
	}
		
	for (;str[postmp1] == ' '; ++postmp1);
	for (;str[postmp2] == ' '; --postmp2);
	if(postmp2 > postmp1)
		str = str.substr(postmp1, postmp2-postmp1+1);
	return str;
}

#endif
