#pragma once
#include "platform/platform.h"

#include <variant>

template <typename T, pu32 E>
class Result {
public:
	Result(const T& value) : data(value){}
	Result(const pu32 error) : data(error){}

	bool 	is_ok()  const { return std::holds_alternative<T>(data); }
	bool 	is_err() const { return !is_ok(); }
	T& 		unwrap() { return std::get<T>(data); }
	pu32 	error()  { return std::get<pu32>(data); }
private:
	std::variant<T, pu32> data;
};
