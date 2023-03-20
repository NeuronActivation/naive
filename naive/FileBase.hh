#ifndef FILE_BASE_HH
#define FILE_BASE_HH

#include <filesystem>

class FileBase
{
public:
	FileBase(const std::filesystem::path& path) : path(path)
	{
	}

	std::filesystem::path path;
};

#endif
