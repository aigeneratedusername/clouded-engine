#pragma once
#include "platform/platform.h"

#include <variant>

template <typename T, typename E>
class Result {
public:
	Result(const T& value) : data(value){}
	Result(const pu32 error) : data(error){}

	bool 	is_ok()  const { return std::holds_alternative<T>(data); }
	bool 	is_err() const { return !is_ok(); }
	T& 		unwrap() { return std::get<T>(data); }
	pu32 	error()  { return std::get<E>(data); }
private:
	std::variant<T, E> data;
};
