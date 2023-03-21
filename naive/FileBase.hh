#ifndef FILE_BASE_HH
#define FILE_BASE_HH

#include <filesystem>

class FileBase : public std::filesystem::directory_entry
{
public:
	FileBase(const std::filesystem::path& path)
		: std::filesystem::directory_entry(path)
	{
	}
};

#endif
