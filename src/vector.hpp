#pragma once

#include <array>
#include <iostream>
#include <unordered_set>

#include "base.hpp"

namespace nl {
	template<typename T, u32 X> class vector {
	private:
		std::array<T, X> arr;

		constexpr T& ref(u32 i) {
			return arr[i];
		};
		constexpr T ref(u32 i) const {
			return arr[i];
		};
	public:
		constexpr std::array<T, X> toArr() { return arr; };
		constexpr std::array<T, X> toArr() const { return arr; };

		constexpr T& operator[](u32 i) {
			return ref(i);
		};
		constexpr T operator[](u32 i) const {
			return ref(i);
		};

		constexpr T& operator()(u32 ix) {
			return ref(ix);
		};
		constexpr T operator()(u32 ix) const {
			return ref(ix);
		};

		constexpr u32 length() {
			return X;
		};
		constexpr u32 length() const {
			return X;
		};

		constexpr vector(const vector& srcVec) { arr = srcVec.arr; };
		constexpr vector(const std::array<T, X>& srcArr) { arr = srcArr; };

		constexpr void forEach(auto fun) {
			for (u32 ix = 0; ix < X; ix++) {
				fun(ref(ix), ix);
			};
		};
		constexpr const void forEach(auto fun) const {
			for (u32 ix = 0; ix < X; ix++) {
				fun(ref(ix), ix);
			};
		};

		constexpr vector() {
			auto init = [](T& val, u32 ix) { val = static_cast<T>(0); };
			forEach(init);
		};

		constexpr vector(const T& srcVal) {
			auto init = [&srcVal](T& val, u32 ix) { val = srcVal; };
			forEach(init);
		};

		template<typename TT> constexpr vector(const vector<TT, X>& src) {
			auto init = [&src](T& val, u32 ix) { val = static_cast<T>(src[ix]); };
			forEach(init);
		};

		template<typename TT> constexpr vector(const std::array<TT, X>& srcArr) {
			auto init = [&srcArr](T& val, u32 ix) { val = static_cast<T>(srcArr[ix]); };
			forEach(init);
		};

		constexpr T scalar() {
			T res = 0;
			auto sqrElem = [&res](const T& val, u32 ix) mutable { res += (val * val); };
			forEach(sqrElem);
			return static_cast<T>(std::sqrt(res));
		};

		constexpr T scalar() const {
			T res = 0;
			auto sqrElem = [&res](const T& val, u32 ix) mutable { res += (val * val); };
			forEach(sqrElem);
			return static_cast<T>(std::sqrt(res));
		};

		void normalize() {
			T scal = scalar();
			auto normal = [&scal](T& val, u32 ix) { val /= scal; };
			forEach(normal);
		};

		constexpr vector<T, X> normalized() {
			vector<T, X> res(arr);
			T scal = scalar();
			auto normal = [&scal](T& val, u32 ix) { val /= scal; };
			res.forEach(normal);
			return res;
		};

		constexpr vector<T, X> normalized() const {
			vector<T, X> res(arr);
			T scal = scalar();
			if (scal == static_cast<T>(0)) scal = static_cast<T>(1);
			auto normal = [&scal](T& val, u32 ix) { val /= scal; };
			res.forEach(normal);
			return res;
		};

		constexpr vector<T, X>& operator+=(const vector<T, X>& rvec) {
			auto sum = [&rvec](T& val, u32 ix) { val += rvec[ix]; };
			forEach(sum);
			return *this;
		};

		constexpr vector<T, X>& operator-=(const vector<T, X>& rvec) {
			auto sub = [&rvec](T& val, u32 ix) { val -= rvec[ix]; };
			forEach(sub);
			return *this;
		};

		constexpr vector<T, X>& operator*=(T rval) {
			auto mult = [&rval](T& val, u32 ix) { val *= rval; };
			forEach(mult);
			return *this;
		};

		constexpr vector<T, X>& operator/=(T rval) {
			auto div = [&rval](T& val, u32 ix) { val /= rval; };
			forEach(div);
			return *this;
		};
		
		constexpr T dotprod(const vector<T, X>& rvec) {
			T prod = static_cast<T>(0);
			auto getProd = [&prod, &rvec](const T& val, u32 ix) { prod += val * rvec[ix]; };
			forEach(getProd);
			return prod;
		};

		constexpr T dotprod(const vector<T, X>& rvec) const {
			T prod = static_cast<T>(0);
			auto getProd = [&prod, &rvec](const T& val, u32 ix) { prod += val * rvec[ix]; };
			forEach(getProd);
			return prod;
		};

		constexpr vector<T, X>& operator%=(const vector<T, X>& rvec) {
			return (*this) *= normalized().dotprod(rvec.normalized());
		};

		template<u32 Y> constexpr vector(const vector<T, Y>& src) {
			auto resize = [&src](T& val, u32 ix) { val = ix < Y ? src[ix] : static_cast<T>(0); };
			forEach(resize);
		};

		template<u32 Y> constexpr vector(const vector<T, Y>& src, const T& fillRest) {
			auto resize = [&src, &fillRest](T& val, u32 ix) { val = ix < Y ? src[ix] : fillRest; };
			forEach(resize);
		};

		template<u32 Y> constexpr vector(const std::array<T, Y>& srcArr) {
			auto resize = [&srcArr](T& val, u32 ix) { val = ix < Y ? srcArr[ix] : static_cast<T>(0); };
			forEach(resize);
		};

		template<u32 Y> constexpr vector(const std::array<T, Y>& srcArr, const T& fillRest) {
			auto resize = [&srcArr, &fillRest](T& val, u32 ix) { val = ix < Y ? srcArr[ix] : fillRest; };
			forEach(resize);
		};

		void store(T* target) {
			auto mod = [&target](const T& val, u32 ix) mutable { target[ix] = val; };
			forEach(mod);
		};

		void store(T* target) const {
			auto mod = [&target](const T& val, u32 ix) mutable { target[ix] = val; };
			forEach(mod);
		};

		constexpr vector<T, X + 1> homogeneous() {
			return vector<T, X + 1>(normalized(), scalar());
		};

		constexpr vector<T, X + 1> homogeneous() const {
			return vector<T, X + 1>(normalized(), scalar());
		};

		constexpr vector<T, X - 1> cartesian() {
			return vector<T, X - 1>(arr) * ref(X - 1);
		};

		constexpr vector<T, X - 1> cartesian() const {
			return vector<T, X - 1>(arr) * ref(X - 1);
		};
	};
};

template<typename T, nl::u32 X> std::ostream& operator<<(std::ostream& out, const nl::vector<T, X> rvec) {
	auto log = [&out](const T& val, nl::u32 ix) { out << val << " "; };
	rvec.forEach(log);
	return out << "\n";
};

template<typename T, nl::u32 X> constexpr T operator~(const nl::vector<T, X>& vec) {
	return vec.scalar();
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator!(const nl::vector<T, X>& vec) {
	return vec.normalized();
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator+(nl::vector<T, X> lvec, const nl::vector<T, X>& rvec) {
	return lvec += rvec;
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator-(nl::vector<T, X> lvec, const nl::vector<T, X>& rvec) {
	return lvec -= rvec;
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator*(nl::vector<T, X> lvec, T rval) {
	return lvec *= rval;
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator/(nl::vector<T, X> lvec, T rval) {
	return lvec /= rval;
};

template<typename T, nl::u32 X> constexpr nl::vector<T, X> operator%(nl::vector<T, X> lvec, const nl::vector<T, X>& rvec) {
	return lvec %= rvec;
};

template<typename T, nl::u32 X> constexpr T operator&(const nl::vector<T, X>& lvec, const nl::vector<T, X>& rvec) {
	return lvec.dotprod(rvec);
};

template<typename T, nl::u32 X> constexpr T operator|(const nl::vector<T, X>& lvec, const nl::vector<T, X>& rvec) {
	return (!lvec) & (!rvec);
};

template<typename T, nl::u32 X> constexpr bool operator||(const nl::vector<T, X>& lvec, const nl::vector<T, X>& rvec) {
	return (lvec | rvec) == static_cast<T>(1);
};

namespace nl {
	template<typename T, u32 X, u32 Y> constexpr vector<T, X + Y> combine(const nl::vector<T, X>& lvec, const nl::vector<T, Y>& rvec) {
		vector<T, X + Y> res;
		auto comb = [&lvec, &rvec](T& val, const u32& ix) { val = ix < X ? lvec[ix] : rvec[ix - X]; };
		res.forEach(comb);
		return res;
	};

	template<typename T, u32 X, u32 Y, u32 Z> constexpr vector<T, X + Y + Z> combine(const vector<T, X>& lvec, const vector<T, Y>& mvec, const vector<T, Z>& rvec) {
		vector<T, X + Y + Z> res;
		auto comb = [&lvec, &mvec, &rvec](T& val, const u32& ix) { val = ix < X ? lvec[ix] : (ix < X + Y ? mvec[ix - X] : rvec[ix - X - Y]); };
		res.forEach(comb);
		return res;
	};

	template<typename T> using vec2 = vector<T, 2>;
	template<typename T> using vec3 = vector<T, 3>;
	template<typename T> using vec4 = vector<T, 4>;
	template<typename T> using vec5 = vector<T, 5>;
	template<typename T> using vec6 = vector<T, 6>;
};

template<typename T, nl::u32 X> constexpr bool operator==(const nl::vector<T, X>& lvec, const nl::vector<T, X>& rvec) {
	bool equal = true;
	auto comp = [&rvec, &equal](const T& val, nl::u32 ix) mutable { equal &= (val == rvec[ix]); };
	lvec.forEach(comp);
	return equal;
};

template<typename T, nl::u32 X> struct std::equal_to<nl::vector<T, X>> {
	bool operator()(const nl::vector<T, X>& lvec, const nl::vector<T, X>& rvec) const {
		bool equal = true;
		auto comp = [&rvec, &equal](const T& val, nl::u32 ix) mutable { equal &= (val == rvec[ix]); };
		lvec.forEach(comp);
		return equal;
	};
};

template<typename T, nl::u32 X> struct std::hash<nl::vector<T, X>> {
	std::size_t operator()(nl::vector<T, X> const& vec) const {
		std::size_t res;
		auto hash = [&res](const T& val, nl::u32 ix) mutable { res = (res << 19) ^ (res >> 13); res ^= std::hash<T>{}(val); };
		vec.forEach(hash);
		return res;
	};
};