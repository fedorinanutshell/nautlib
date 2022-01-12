#ifndef MATRIX_INCLUDED
#define MATRIX_INCLUDED

#include <array>
#include <iostream>

#include "base.hpp"
#include "vector.hpp"

namespace nl {
	template<u32 X, u32 Y> class matrixCoord {
	public:
		vec2<u32> coord;

		constexpr u32 length() { return X; };
		constexpr u32 width() { return Y; };
		constexpr u32 area() { return X * Y; };

		constexpr matrixCoord() { coord = vec2<u32>({ 0, 0 }); };
		constexpr matrixCoord(const matrixCoord& srcCoord) { coord = srcCoord.coord; };
		constexpr matrixCoord(const vec2<u32>& srcCoord) { coord = srcCoord; };
		constexpr matrixCoord(const std::array<u32, 2>& srcArr) { coord = vec2<u32>(srcArr); };

		constexpr u32& ix() { return coord[0]; };
		constexpr u32& iy() { return coord[1]; };

		constexpr u32 ix() const { return coord[0]; };
		constexpr u32 iy() const { return coord[1]; };

		constexpr u32 i() { return iy() * X + ix(); };
		constexpr u32 i() const { return iy() * X + ix(); };
	};

	template<typename T, u32 X, u32 Y> class matrix {
	private:
		std::array<T, X * Y> arr;

		constexpr T& ref(const u32& i) { return arr[i]; };
		constexpr T ref(const u32& i) const { return arr[i]; };

		constexpr T& ref(const u32& ix, const u32& iy) { return ref(iy * X + ix); };
		constexpr T ref(const u32& ix, const u32& iy) const { return ref(iy * X + ix); };

		constexpr T& ref(const matrixCoord<X, Y>& ic) { return ref(ic.ix(), ic.iy()); };
		constexpr T ref(const matrixCoord<X, Y>& ic) const { return ref(ic.ix(), ic.iy()); };
	public:
		constexpr std::array<T, X * Y> toArr() { return arr; };
		constexpr std::array<T, X * Y> toArr() const { return arr; };

		constexpr T& operator[](const u32& i) { return ref(i); };
		constexpr T operator[](const u32& i) const { return ref(i); };

		constexpr T& operator[](const matrixCoord<X, Y>& ic) { return ref(ic); };
		constexpr T operator[](const matrixCoord<X, Y>& ic) const { return ref(ic); };

		constexpr T& operator()(const u32& ix, const u32& iy) { return ref(ix, iy); };
		constexpr T operator()(const u32& ix, const u32& iy) const { return ref(ix, iy); };

		constexpr u32 length() { return X; };
		constexpr u32 width() { return Y; };
		constexpr u32 area() { return X * Y; };
		constexpr u32 length() const { return X; };
		constexpr u32 width() const { return Y; };
		constexpr u32 area() const { return X * Y; };

		constexpr matrix(const matrix& srcMat) { arr = srcMat.arr; };
		constexpr matrix(const std::array<T, X * Y> srcArr) { arr = srcArr; };

		constexpr void forEach(auto fun) {
			for (u32 iy = 0; iy < Y; iy++) {
				for (u32 ix = 0; ix < X; ix++) {
					fun(ref(ix, iy), ix, iy);
				};
			};
		};
		constexpr void forEach(auto fun) const {
			for (u32 iy = 0; iy < Y; iy++) {
				for (u32 ix = 0; ix < X; ix++) {
					fun(ref(ix, iy), ix, iy);
				};
			};
		};

		constexpr matrix() {
			auto init = [](T& val, const u32& ix, const u32& iy) { val = static_cast<T>(0); };
		};
		constexpr matrix(const T& srcVal) {
			auto init = [&srcVal](T& val, const u32& ix, const u32& iy) { val = srcVal; };
		};
		constexpr matrix(const T& srcVal, const T& other) {
			auto init = [&srcVal](T& val, const u32& ix, const u32& iy) { val = ix == iy ? srcVal : other; };
		};

		template<typename TT> constexpr matrix(matrix<TT, X, Y> srcMat) {
			auto init = [&srcMat](T& val, const u32& ix, const u32& iy) { val = static_cast<T>(srcMat.ref(ix, iy)); };
		};
		template<typename TT> constexpr matrix(std::array<TT, X * Y> srcArr) {
			auto init = [&srcArr](T& val, const u32& ix, const u32& iy) { val = static_cast<T>(srcArr[iy * X + ix]); };
		};

		constexpr matrix<T, X, Y>& operator+=(const matrix<T, X, Y>& rmat) {
			auto sum = [&rmat](T& val, const u32& ix, const u32& iy) { val += rmat.ref(ix, iy); };
			forEach(sum);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator-=(const matrix<T, X, Y>& rmat) {
			auto sub = [&rmat](T& val, const u32& ix, const u32& iy) { val -= rmat.ref(ix, iy); };
			forEach(sub);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator*=(const T& rval) {
			auto mult = [&rval](T& val, const u32& ix, const u32& iy) { val *= rval; };
			forEach(mult);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator/=(const T& rval) {
			auto div = [&rval](T& val, const u32& ix, const u32& iy) { val /= rval; };
			forEach(div);
			return *this;
		};

		template<u32 L, u32 H> constexpr matrix<T, L, H> zone(const u32& x, const u32& y) {
			matrix<T, L, H> res;
			auto crop = [this](T& val, const u32& ix, const u32& iy) { val = this->ref(ix + x, iy + y); };
			res.forEach(crop);
			return res;
		};

		template<u32 L, u32 H> constexpr matrix<T, L, H> zone(const u32& x, const u32& y) const {
			matrix<T, L, H> res;
			auto crop = [this, &x, &y](T& val, const u32& ix, const u32& iy) { val = this->ref(ix + x, iy + y); };
			res.forEach(crop);
			return res;
		};

		constexpr vector<T, X * Y> toVector() {
			vector<T, X * Y> res;
			auto copy = [&res](const T& val, const u32& ix, const u32& iy) mutable { res[iy * X + ix] = val; };
			forEach(copy);
			return res;
		};

		constexpr vector<T, X* Y> toVector() const {
			vector<T, X* Y> res;
			auto copy = [&res](const T& val, const u32& ix, const u32& iy) mutable { res[iy * X + ix] = val; };
			forEach(copy);
			return res;
		};

		constexpr matrix(const vector<T, X * Y>& vec) {
			auto init = [&vec](T& val, const u32& ix, const u32& iy) { val = vec[iy * X + ix]; };
			forEach(init);
		};
	};
};

template<typename T, nl::u32 X, nl::u32 Y> std::ostream& operator<<(std::ostream& out, const nl::matrix<T, X, Y>& rmat) {
	auto log = [&out](const T& val, const nl::u32& ix, const nl::u32& iy) mutable { out << val << ((ix == (X - 1)) ? "\n" : " "); };
	rmat.forEach(log);
	return out;
};

template<typename T, nl::u32 X, nl::u32 YX, nl::u32 Y> nl::matrix<T, X, Y> operator&(const nl::matrix<T, X, YX>& lmat, const nl::matrix<T, YX, Y>& rmat) {
	nl::matrix<T, X, Y> res;
	auto dotProd = [&lmat, &rmat](T& val, const nl::u32& ix, const nl::u32& iy) { val = lmat.zone<1, YX>(ix, 0).toVector() & rmat.zone<YX, 1>(0, iy).toVector(); };
	res.forEach(dotProd);
	return res;
};

#endif