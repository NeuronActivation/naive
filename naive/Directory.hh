#ifndef DIRECTORY_HH
#define DIRECTORY_HH

#include "FileBase.hh"
#include "File.hh"

#include <termos/Submenu.hh>

class Directory : public Termos::Submenu, public FileBase
{
public:
	Directory(const std::filesystem::path& path);

private:
	void readFiles();

	bool initialized = false;
};

#endif
