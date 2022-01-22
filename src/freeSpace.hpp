#pragma once

#include <vector>
#include <iostream>

#include "base.hpp"
#include "vector.hpp"

namespace nl {
	using fspCoord = vec3<u32>;

	template<typename T> class freeSpace {
	private:
		std::vector<T> vec;

		u32 l;
		u32 h;
		u32 d;

		constexpr u32 resize(u32 x, u32 y, u32 z) {
			l = x; h = y; d = z;
			vec.resize(x * y * z);
			return x * y * z;
		};

		constexpr T& ref(u32 i) { return vec[i]; };
		constexpr T ref(u32 i) const { return vec[i]; };

		constexpr T& ref(u32 ix, u32 iy, u32 iz) {
			if (ix < l || iy < h || iz < d) {
				return ref(iy * d * l + iz * l + ix);
			}
			else {
				resize(ix, iy, iz);
				ref(iy * d * l + iz * l + ix) = T();
				return ref(iy * d * l + iz * l + ix);
			};
		};
		constexpr T ref(u32 ix, u32 iy, u32 iz) const {
			if (ix < l || iy < h || iz < d) {
				return ref(iy * d * l + iz * l + ix);
			}
			else {
				return T();
			};
		};

		constexpr T& ref(const fspCoord& ic) {
			return ref(ic[0], ic[1], ic[2]);
		};
		constexpr T ref(const fspCoord& ic) const {
			return ref(ic[0], ic[1], ic[2]);
		};
	public:
		constexpr std::vector<T> toVec() { return vec; };
		constexpr std::vector<T> toVec() const { return vec; };

		constexpr u32 length() { return l; };
		constexpr u32 length() const { return l; };
		constexpr u32 height() { return h; };
		constexpr u32 height() const { return h; };
		constexpr u32 depth() { return d; };
		constexpr u32 depth() const { return d; };

		constexpr u32 volume() { return vec.size(); };
		constexpr u32 volume() const { return vec.size(); };

		constexpr T& operator[](u32 i) { return ref(i); };
		constexpr T operator[](u32 i) const { return ref(i); };

		constexpr T& operator()(u32 ix, u32 iy, u32 iz) { return ref(ix, iy, iz); };
		constexpr T operator()(u32 ix, u32 iy, u32 iz) const { return ref(ix, iy, iz); };

		constexpr T& operator[](const fspCoord& ic) { return ref(ic); };
		constexpr T operator[](const fspCoord& ic) const { return ref(ic); };

		constexpr freeSpace(const freeSpace& srcFSP) { vec = srcFSP.vec; };

		constexpr void forEach(auto fun) {
			for (u32 iy = 0; iy < h; iy++) {
				for (u32 iz = 0; iz < d; iz++) {
					for (u32 ix = 0; ix < l; ix++) {
						fun(ref(ix, iy, iz), ix, iy, iz);
					};
				};
			};
		};
		constexpr void forEach(auto fun) const {
			for (u32 iy = 0; iy < h; iy++) {
				for (u32 iz = 0; iz < d; iz++) {
					for (u32 ix = 0; ix < l; ix++) {
						fun(ref(ix, iy, iz), ix, iy, iz);
					};
				};
			};
		};

		constexpr freeSpace(const std::vector<T>& srcVec, u32 x, u32 y, u32 z) {
			resize(x, y, z);
			auto constr = [&srcVec](T& val, u32 ix, u32 iy, u32 iz) { val = srcVec(iy * z * x + iz * x + ix); };
			forEach(constr);
		}

		constexpr freeSpace(const T& fill, u32 x, u32 y, u32 z) {
			resize(x, y, z);
			auto fillf = [&fill](T& val, u32 ix, u32 iy, u32 iz) { val = fill; };
			forEach(fillf);
		};
	};
};

template<typename T> std::ostream& operator<<(std::ostream& out, const nl::freeSpace<T>& fsp) {
	auto log = [&out, &fsp](const T& val, nl::u32 ix, nl::u32 iy, nl::u32 iz) mutable { out << val << (ix == (fsp.length() - 1) ? (iy == (fsp.height() - 1) ? (iz == (fsp.depth() - 1) ? "" : "\n\n") : "\n") : " "); };
	fsp.forEach(log);
	return out << "\n";
};