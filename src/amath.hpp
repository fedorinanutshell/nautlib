#ifndef AMATH_INCLUDED
#define AMATH_INCLUDED

#include <numeric>

#include "base.hpp"

namespace nl {
	template<typename T> constexpr T afract(const T& x) {
		return x - std::floor(x);
	};

	template<typename T> constexpr T amod(const T& x, const T& y) {
		T div = x / y;
		return afract(div);
	};
};

#endif