#include <iostream>
#include <string>
#include <type_traits>
#include <array>
#include "ParseFile.h"
#include "Traits_Type.h"
#include <sstream>

using namespace tools;

std::string path("F:\\workspace\\Project2\\Project2\\test.proto");

class A {};
class B:A { };
class C {};

int main() 
{
	//std::map<std::string, Type&> mapClass;
	//type_traits::RegisterClass<A>(mapClass);



/*
	std::stringstream os;
	os << "this     is";
	std::string strtmp1;
	std::string strtmp2;
	os >> strtmp1;
	os >> strtmp2;
	std::cout << strtmp1 << std::endl;
	std::cout << os.str() << std::endl;	
	*/
	//std::map<int, type_traits::Type*> mapData;
	Traits_Type<bool> temp1;
	Traits_Type<int> temp2;
	Traits_Type<double> temp3;
	Traits_Type<float> temp4;
	Traits_Type<int*> temp5;
	Traits_Type<std::string> temp6;
	
	//mapData[1]=&temp1;
	//mapData[2]=&temp2;
	//mapData[3]=&temp3;
	//mapData[4]=&temp4;
	//mapData[5]=&temp5;
	//mapData[6]=&temp6;

	
	//decltype(temp1)::type_name strTmp("this is a test!");
	//std::cout << "mapData = " << dynamic_cast<>(*mapData[1])<< std::endl;
	std::cout << "temp1 = " << typeid(decltype(temp1())).name() << std::endl;
	std::cout << "temp2 = " << typeid(decltype(temp2())).name() << std::endl;
	std::cout << "temp3 = " << typeid(decltype(temp3())).name() << std::endl;
	std::cout << "temp4 = " << typeid(decltype(temp4())).name() << std::endl;
	std::cout << "temp5 = " << typeid(decltype(temp5())).name() << std::endl;
	//std::cout << "temp6 = " << typeid(decltype(temp6())).name() << std::endl;
	//std::cout << "strTmp = " << Traits_Type<double>().type_name << std::endl;


	system("pause");
	return 0;
}