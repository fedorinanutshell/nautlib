//used only for tests

#include <iostream>
#include <chrono>

#include "base.hpp"
#include "amath.hpp"
#include "freeSpace.hpp"
#include "space.hpp"
#include "matrix.hpp"
#include "vector.hpp"

int main() {
	auto then = std::chrono::high_resolution_clock::now();

	const nl::freeSpace<double> fsp = nl::freeSpace<double>(0.5, 3, 4, 5);
	std::cout << fsp;

	std::cout << "main() ended, " << (std::chrono::high_resolution_clock::now() - then).count() / 1000 << " us elapsed...\n";
};