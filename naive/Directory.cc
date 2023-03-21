#include "Directory.hh"

#include <termos/Debug.hh>

Directory::Directory(const std::filesystem::path& path,
					std::function <void(Directory&)>& inotifyRegister)
	: Termos::Submenu(path.filename()), FileBase(path), inotifyRegister(inotifyRegister)
{
	onExpand = std::bind(&Directory::readFiles, this);
}

void Directory::handleEvent(inotify_event* event)
{
	DBG_LOG("Event for", path());
}

void Directory::readFiles()
{
	if(initialized)
		return;

	for(auto& entry : std::filesystem::directory_iterator(path()))
	{
		if(entry.is_directory())
			add <Directory> (entry.path(), inotifyRegister);

		else add <File> (entry.path());
	}

	inotifyRegister(*this);
	initialized = true;
}
