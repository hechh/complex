#pragma once
#ifndef _DEFINE_H_
#define _DEFINE_H_

#include <string>

namespace TypeSpace {

enum position_e {
	Front = 0,
	Back
};

struct proto_s {
	bool bRepeated_;
	std::string strType_;
	proto_s()
		:bRepeated_(false),strType_("") {
	}
	proto_s operator=(const proto_s& tmp) {
		bRepeated_ = tmp.bRepeated_;
		strType_ = tmp.strType_;
		return *this;
	}
	proto_s(const proto_s& tmp) {
		bRepeated_ = tmp.bRepeated_;
		strType_ = tmp.strType_;
	}
	void Clear() {
		bRepeated_ = false;
		strType_.clear();
	}
};


}





#endif
