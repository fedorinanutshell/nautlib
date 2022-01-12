#ifndef SPACE_INCLUDED
#define SPACE_INCLUDED

#include <array>
#include <iostream>

#include "base.hpp"
#include "vector.hpp"

namespace nl {
	template<u32 X, u32 Y, u32 Z> class spaceCoord {
	public:
		vec3<u32> coord;

		constexpr u32 length() { return X; };
		constexpr u32 width() { return Y; };
		constexpr u32 depth() { return Z; };
		constexpr u32 volume() { return X * Y * Z; };

		constexpr spaceCoord() { coord = vec3<u32>({ 0, 0, 0 }); };
		constexpr spaceCoord(const spaceCoord& srcCoord) { coord = srcCoord.coord; };
		constexpr spaceCoord(const vec3<u32>& srcCoord) { coord = srcCoord; };
		constexpr spaceCoord(const std::array<u32, 3>& srcArr) { coord = vec3<u32>(srcArr); };

		constexpr u32& ix() { return coord[0]; };
		constexpr u32& iy() { return coord[1]; };
		constexpr u32& iz() { return coord[2]; };

		constexpr u32 ix() const { return coord[0]; };
		constexpr u32 iy() const { return coord[1]; };
		constexpr u32 iz() const { return coord[2]; };

		constexpr u32 i() { return iz() * X * Y + iy() * X + ix(); };
		constexpr u32 i() const { return iz() * X * Y + iy() * X + ix(); };
	};

	template<typename T, u32 X, u32 Y, u32 Z> class space {
	private:
		std::array<T, X * Y * Z> arr;

		constexpr T& ref(const u32& i) { return arr[i]; };
		constexpr T ref(const u32& i) const { return arr[i]; };

		constexpr T& ref(const u32& ix, const u32& iy, const u32& iz) { return ref(iz * X * Y + iy * X + ix); };
		constexpr T ref(const u32& ix, const u32& iy, const u32& iz) const { return ref(iz * X * Y + iy * X + ix); };

		constexpr T& ref(const spaceCoord<X, Y, Z>& ic) { return ref(ic.ix(), ic.iy(), ic.iz()); };
		constexpr T ref(const spaceCoord<X, Y, Z>& ic) const { return ref(ic.ix(), ic.iy(), ic.iz()); };
	public:
		constexpr std::array<T, X * Y * Z> toArr() { return arr; };
		constexpr std::array<T, X* Y* Z> toArr() const { return arr; };

		constexpr T& operator[](const u32& i) { return ref(i); };
		constexpr T operator[](const u32& i) const { return ref(i); };

		constexpr T& operator()(const spaceCoord<X, Y, Z>& ic) { return ref(ic); };
		constexpr T operator()(const spaceCoord<X, Y, Z>& ic) const { return ref(ic); };

		constexpr T& operator()(const u32& ix, const u32& iy, const u32& iz) { return ref(ix, iy, iz); };
		constexpr T operator()(const u32& ix, const u32& iy, const u32& iz) const { return ref(ix, iy, iz); };

		constexpr u32 length() { return X; };
		constexpr u32 width() { return Y; };
		constexpr u32 depth() { return Z; };
		constexpr u32 volume() { return X * Y * Z; };
		constexpr u32 length() const { return X; };
		constexpr u32 width() const { return Y; };
		constexpr u32 depth() const { return Z; };
		constexpr u32 volume() const { return X * Y * Z; };

		constexpr space(const space& srcSp) { arr = srcSp.arr; };
		constexpr space(const std::array<T, X * Y * Z> srcArr) { arr = srcArr; };

		constexpr void forEach(auto fun) {
			for (u32 iz = 0; iz < Z; iz++) {
				for (u32 iy = 0; iy < Y; iy++) {
					for (u32 ix = 0; ix < X; ix++) {
						fun(ref(ix, iy, iz), ix, iy, iz);
					};
				};
			};
		};
		constexpr void forEach(auto fun) const {
			for (u32 iz = 0; iz < Z; iz++) {
				for (u32 iy = 0; iy < Y; iy++) {
					for (u32 ix = 0; ix < X; ix++) {
						fun(ref(ix, iy, iz), ix, iy, iz);
					};
				};
			};
		};

		constexpr space(const T& srcVal) {
			auto init = [&srcVal](T& val, const u32& ix, const u32& iy, const u32& iz) { val = srcVal; };
			forEach(init);
		};
	};
};

template<typename T, nl::u32 X, nl::u32 Y, nl::u32 Z> std::ostream& operator<<(std::ostream& out, const nl::space<T, X, Y, Z>& rsp) {
	auto log = [&out](const T& val, const nl::u32& ix, const nl::u32& iy, const nl::u32& iz) mutable { out << val << (ix == (X - 1) ? (iy == (Y - 1) ? (iz == (Z - 1) ? "" : "\n\n") : "\n") : " "); };
	rsp.forEach(log);
	return out << "\n";
};

#endif