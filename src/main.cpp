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
#include "interpolation.hpp"

int main() {
	auto then = std::chrono::high_resolution_clock::now();

	std::cout << nl::cubicInterpolation(1.0f, 8.0f, 27.0f, 64.0f, 0.5f, 1.0f) << "\n";

	std::cout << "main() ended, " << (std::chrono::high_resolution_clock::now() - then).count() / 1000 << " us elapsed...\n";
};