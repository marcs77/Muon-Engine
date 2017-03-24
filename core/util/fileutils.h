#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "../common.h"
#include <string.h>

namespace muon {
	
	std::string read_file(const char* filepath);
	std::string get_directory(std::string path);
}

#endif // !FILEUTILS_H
