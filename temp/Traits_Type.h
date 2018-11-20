#pragma once

#include <type_traits>
#include <memory>
#include <iostream>


namespace type_traits{

class Type{
public:
	Type() {}
	virtual ~Type() {}
};

template<typename T>
class Type_T {
public:
	using type_value = T;
};

template<typename T>
class Type_T<T*>{
public:
	using type_value = T;
};

template<typename T>
class Type_T<T**>{
public:
	using type_value = T;
};

template<typename T>
class Remove_ptr {
public:
	using value_type =typename Type_T<T>::type_value;
};

template<typename T>
class Remove_ref {
public:
	using type_value = T;
};
template<typename T>
class Remove_ref<T&> {
public:
	using type_value = T;
};
template<typename T>
class Remove_ref<T&&> {
public:
	using type_value = T;
};

template<typename T>
class Traits_Type : public Type
{
public:
	using type = Traits_Type<T>;
	using type_value = T;
	const std::string type_name;
public:
	Traits_Type():type_name(typeid(T).name()){
		spT_.reset(new type_value());
		memset(spT_.get(),0,sizeof(type_value));
	}
	~Traits_Type() {}
	operator type_value()const {  
		return *(spT_.get());
	}
	type_value operator()()const {
		return *(spT_.get());
	}

private:
	static std::shared_ptr<type_value> spT_;
};
template<typename T>std::shared_ptr<T> Traits_Type<T>::spT_ = nullptr;

template<typename T>
void RegisterClass(T,std::map<std::string,std::shared_ptr<Type>>& mapClass) {
	auto tmp = std::make_shared<Traits_Type<typename Remove_ref<T>::type_value>>();
	//mapClass[tmp->type_name].reset(tmp);
}

}
