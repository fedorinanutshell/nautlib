#pragma once

#include <string>
#include <sstream>
#include <fstream>

namespace nl {
	std::string getFile(const std::string& path) {
		std::fstream file(path);
		std::stringstream stream;
		stream << file.rdbuf();
		return stream.str();
	};

	void storeFile(const std::string& path, const std::string& contents) {
		std::fstream file(path, std::ios::trunc | std::ios::in | std::ios::out);
		file << contents;
	};
};