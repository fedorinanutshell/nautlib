#pragma once

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

		constexpr T& ref(u32 i) { return arr[i]; };
		constexpr T ref(u32 i) const { return arr[i]; };

		constexpr T& ref(u32 ix, u32 iy) { return ref(iy * X + ix); };
		constexpr T ref(u32 ix, u32 iy) const { return ref(iy * X + ix); };

		constexpr T& ref(const matrixCoord<X, Y>& ic) { return ref(ic.ix(), ic.iy()); };
		constexpr T ref(const matrixCoord<X, Y>& ic) const { return ref(ic.ix(), ic.iy()); };
	public:
		constexpr std::array<T, X * Y> toArr() { return arr; };
		constexpr std::array<T, X * Y> toArr() const { return arr; };

		constexpr T& operator[](u32 i) { return ref(i); };
		constexpr T operator[](u32 i) const { return ref(i); };

		constexpr T& operator[](const matrixCoord<X, Y>& ic) { return ref(ic); };
		constexpr T operator[](const matrixCoord<X, Y>& ic) const { return ref(ic); };

		constexpr T& operator()(u32 ix, u32 iy) { return ref(ix, iy); };
		constexpr T operator()(u32 ix, u32 iy) const { return ref(ix, iy); };

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
			auto init = [](T& val, u32 ix, u32 iy) { val = static_cast<T>(0); };
			forEach(init);
		};
		constexpr matrix(const T& srcVal) {
			auto init = [&srcVal](T& val, u32 ix, u32 iy) { val = srcVal; };
			forEach(init);
		};
		constexpr matrix(const T& srcVal, const T& other) {
			auto init = [&srcVal, &other](T& val, u32 ix, u32 iy) { val = ix == iy ? srcVal : other; };
			forEach(init);
		};

		template<typename TT> constexpr matrix(matrix<TT, X, Y> srcMat) {
			auto init = [&srcMat](T& val, u32 ix, u32 iy) { val = static_cast<T>(srcMat.ref(ix, iy)); };
			forEach(init);
		};
		template<typename TT> constexpr matrix(std::array<TT, X * Y> srcArr) {
			auto init = [&srcArr](T& val, u32 ix, u32 iy) { val = static_cast<T>(srcArr[iy * X + ix]); };
			forEach(init);
		};

		constexpr matrix<T, X, Y>& operator+=(const matrix<T, X, Y>& rmat) {
			auto sum = [&rmat](T& val, u32 ix, u32 iy) { val += rmat.ref(ix, iy); };
			forEach(sum);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator-=(const matrix<T, X, Y>& rmat) {
			auto sub = [&rmat](T& val, u32 ix, u32 iy) { val -= rmat.ref(ix, iy); };
			forEach(sub);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator*=(T rval) {
			auto mult = [&rval](T& val, u32 ix, u32 iy) { val *= rval; };
			forEach(mult);
			return *this;
		};

		constexpr matrix<T, X, Y>& operator/=(T rval) {
			auto div = [&rval](T& val, u32 ix, u32 iy) { val /= rval; };
			forEach(div);
			return *this;
		};

		template<u32 L, u32 H> constexpr matrix<T, L, H> zone(u32 x, u32 y) {
			matrix<T, L, H> res;
			auto crop = [this](T& val, u32 ix, u32 iy) { val = this->ref(ix + x, iy + y); };
			res.forEach(crop);
			return res;
		};

		template<u32 L, u32 H> constexpr matrix<T, L, H> zone(u32 x, u32 y) const {
			matrix<T, L, H> res;
			auto crop = [this, &x, &y](T& val, u32 ix, u32 iy) { val = this->ref(ix + x, iy + y); };
			res.forEach(crop);
			return res;
		};

		constexpr vector<T, X * Y> toVector() {
			vector<T, X * Y> res;
			auto copy = [&res](const T& val, u32 ix, u32 iy) mutable { res[iy * X + ix] = val; };
			forEach(copy);
			return res;
		};

		constexpr vector<T, X * Y> toVector() const {
			vector<T, X * Y> res;
			auto copy = [&res](const T& val, u32 ix, u32 iy) mutable { res[iy * X + ix] = val; };
			forEach(copy);
			return res;
		};

		constexpr matrix(const vector<T, X * Y>& vec) {
			auto init = [&vec](T& val, u32 ix, u32 iy) { val = vec[iy * X + ix]; };
			forEach(init);
		};

		void store(T* target) {
			auto mod = [&target](const T& val, u32 ix, u32 iy) mutable { target[iy * X + ix] = val; };
			forEach(mod);
		};
		void store(T* target) const {
			auto mod = [&target](const T& val, u32 ix, u32 iy) mutable { target[iy * X + ix] = val; };
			forEach(mod);
		};
	};
};

template<typename T, nl::u32 X, nl::u32 Y> std::ostream& operator<<(std::ostream& out, const nl::matrix<T, X, Y>& rmat) {
	auto log = [&out](const T& val, nl::u32 ix, nl::u32 iy) mutable { out << val << ((ix == (X - 1)) ? "\n" : " "); };
	rmat.forEach(log);
	return out;
};

template<typename T, nl::u32 X, nl::u32 YX, nl::u32 Y> nl::matrix<T, X, Y> operator&(const nl::matrix<T, X, YX>& lmat, const nl::matrix<T, YX, Y>& rmat) {
	nl::matrix<T, X, Y> res;
	auto dotProd = [&lmat, &rmat](T& val, nl::u32 ix, nl::u32 iy) { val = lmat.zone<1, YX>(ix, 0).toVector() & rmat.zone<YX, 1>(0, iy).toVector(); };
	res.forEach(dotProd);
	return res;
};

namespace nl {
	template<typename T> using mat1x1 = matrix<T, 1, 1>;
	using mat1x1coord = matrixCoord<1, 1>;
	template<typename T> using mat1x2 = matrix<T, 1, 2>;
	using mat1x2coord = matrixCoord<1, 2>;
	template<typename T> using mat1x3 = matrix<T, 1, 3>;
	using mat1x3coord = matrixCoord<1, 3>;
	template<typename T> using mat1x4 = matrix<T, 1, 4>;
	using mat1x4coord = matrixCoord<1, 4>;

	template<typename T> using mat2x1 = matrix<T, 2, 1>;
	using mat2x1coord = matrixCoord<2, 1>;
	template<typename T> using mat2x2 = matrix<T, 2, 2>;
	using mat2x2coord = matrixCoord<2, 2>;
	template<typename T> using mat2x3 = matrix<T, 2, 3>;
	using mat2x3coord = matrixCoord<2, 3>;
	template<typename T> using mat2x4 = matrix<T, 2, 4>;
	using mat2x4coord = matrixCoord<2, 4>;

	template<typename T> using mat3x1 = matrix<T, 3, 1>;
	using mat3x1coord = matrixCoord<3, 1>;
	template<typename T> using mat3x2 = matrix<T, 3, 2>;
	using mat3x2coord = matrixCoord<3, 2>;
	template<typename T> using mat3x3 = matrix<T, 3, 3>;
	using mat3x3coord = matrixCoord<3, 3>;
	template<typename T> using mat3x4 = matrix<T, 3, 4>;
	using mat3x4coord = matrixCoord<3, 4>;

	template<typename T> using mat4x1 = matrix<T, 4, 1>;
	using mat4x1coord = matrixCoord<4, 1>;
	template<typename T> using mat4x2 = matrix<T, 4, 2>;
	using mat4x2coord = matrixCoord<4, 2>;
	template<typename T> using mat4x3 = matrix<T, 4, 3>;
	using mat4x3coord = matrixCoord<4, 3>;
	template<typename T> using mat4x4 = matrix<T, 4, 4>;
	using mat4x4coord = matrixCoord<4, 4>;

	mat4x4<float> scalingMatrix(float x, float y, float z) {
		mat4x4<float> out(1.0, 0.0);
		out(0, 0) = x;
		out(1, 1) = y;
		out(2, 2) = z;
		return out;
	};

	mat4x4<float> xRotationMatrix(float angle) {
		mat4x4<float> out(1.0, 0.0);
		out(1, 1) = std::cos(angle);
		out(2, 1) = -std::sin(angle);
		out(1, 2) = std::sin(angle);
		out(2, 2) = std::cos(angle);
		return out;
	};

	mat4x4<float> yRotationMatrix(float angle) {
		mat4x4<float> out(1.0, 0.0);
		out(0, 0) = std::cos(angle);
		out(2, 0) = std::sin(angle);
		out(0, 2) = -std::sin(angle);
		out(2, 2) = std::cos(angle);
		return out;
	};

	mat4x4<float> zRotationMatrix(float angle) {
		mat4x4<float> out(1.0, 0.0);
		out(0, 0) = std::cos(angle);
		out(1, 0) = -std::sin(angle);
		out(0, 1) = std::sin(angle);
		out(1, 1) = std::cos(angle);
		return out;
	};

	mat4x4<float> perspectiveMatrix(float FOV, float aspect, float near, float far) {
		mat4x4<float> out(0.0, 0.0);
		float f = 1.0f / std::tanf(FOV / 2.0);
		float range = 1 / (near - far);

		out(0, 0) = f / aspect;
		out(1, 1) = f;
		out(2, 2) = (near + far) * range;
		out(2, 3) = -1.0;
		out(3, 2) = near * far * range * 2.0;
		return out;
	};

	mat4x4<float> orthoMatrix() {
		mat4x4<float> out(1.0, 0.0);
		out(2, 2) = 0.0;
		return out;
	};
};