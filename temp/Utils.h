#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <map>
#include <vector>

namespace tools {

	class Utils {
	public:
		static void DelAnnotation(std::string& strTmp);
		static void DelTab(std::string& str);
		static void DelSpace(std::string& str);
		static void GetKeyValue(std::string& str,std::string& strKey,std::string& strValue);
		static void Find(const std::string& strline, std::string strfind, std::vector<int>& vecInt);

		static void MultiSplit(const std::string& strline, std::string spstr, std::map<int, std::string>& mapStr);
		static void MultiSplit(const std::string& strline, std::string spstr, std::vector<std::string>& vecStr);
		static void Split(const std::string& strline, std::string spstr, std::vector<std::string>& vecStr);
		static void Split(const std::string& strline, std::string spstr, std::map<int, std::string>& mapData);
		static bool Split(std::string& strline, std::string spstr, int position = 0);
	};


}
#endif
