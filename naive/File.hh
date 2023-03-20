#ifndef FILE_HH
#define FILE_HH

#include "FileBase.hh"

#include <termos/MenuEntry.hh>

class File : public Termos::MenuEntry, public FileBase
{
public:
	File(const std::filesystem::path& path) : Termos::MenuEntry(path.filename()), FileBase(path)
	{
	}

	void onTrigger() override
	{
	}

private:
	const char* getPrefix() override { return "- "; }
};

#endif
