#include "Directory.hh"

Directory::Directory(const std::filesystem::path& path)
	: Termos::Submenu(path.filename()), FileBase(path)
{
	onExpand = std::bind(&Directory::readFiles, this);
}

void Directory::readFiles()
{
	if(initialized)
		return;

	for(auto& entry : std::filesystem::directory_iterator(path))
	{
		if(entry.is_directory())
			add <Directory> (entry.path());

		else add <File> (entry.path());
	}

	initialized = true;
}
