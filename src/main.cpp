//used only for tests

#include <iostream>
#include <chrono>
#include <vector>

#include "base.hpp"
#include "amath.hpp"
#include "freespace.hpp"
#include "space.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "random.hpp"

int main() {
	auto then = std::chrono::high_resolution_clock::now();

	//std::vector<float> in;
	//std::vector<float> f;
	//std::vector<float> s;

	for (nl::u16 i = 0; i < 4096; i++) {
		auto nf = nl::random_u16(i);
		//float ns = nl::randomfloat_normal(nl::randombase_u32(i));
		//in.push_back(i);
		//f.push_back(nf);
		//s.push_back(ns);
		std::cout << nl::u64(i) << " " << nl::u64(nf) << "\n";
	};

	//std::cout << "\n";

	//std::sort(in.begin(), in.end());
	//std::sort(f.begin(), f.end());
	//std::sort(s.begin(), s.end());

	//for (nl::s32 j = 0; j < 4096; j++) {
	//	std::cout << in[j] << " " << f[j] << " " << s[j] << "\n";
	//};

	std::cout << "main() ended, " << (std::chrono::high_resolution_clock::now() - then).count() / 1000 << " us elapsed...\n";
};