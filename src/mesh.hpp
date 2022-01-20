#ifndef MESH_INCLUDED
#define MESH_INCLUDED

#include <vector>

#include "vector.hpp"

namespace nl {
	template<typename T, u32 X> class mesh {
	public:
		std::vector<vector<T, X>> arr;

		constexpr mesh() = default;
		constexpr mesh(const std::vector<vector<T, X>>& srcArr) {
			arr = srcArr;
		};

		constexpr u32 size() { return arr.size(); };
		constexpr u32 size() const { return arr.size(); };

		std::vector<T> rawArr() {
			std::vector<T> out;
			u32 l = size() * X;
			for (u64 i = 0; i < l; i++) {
				out.push_back(arr[i / X][i % X]);
			};
			return out;
		};
	};
};

template<typename T, nl::u32 X> nl::mesh<T, X> operator+(nl::mesh<T, X> lmesh, const nl::mesh<T, X>& rmesh) {
	nl::mesh<T, X> res = lmesh;
	for (nl::u32 i = 0; i < rmesh.size(); i++) {
		res.arr.push_back(rmesh.arr[i]);
	};
	return res;
};

#endif