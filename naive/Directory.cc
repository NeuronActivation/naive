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
	DBG_LOG("event for", event->name, "in", path());

	if(event->mask & IN_CREATE)
		addEntry(std::filesystem::directory_entry(event->name));

	if(event->mask & IN_DELETE)
	{
		MenuEntry* entry = findEntry(event->name);
		entry->setHighlight(Termos::Color::Red);
	}
}

Termos::MenuEntry* Directory::findEntry(const char* name)
{
	for(size_t i = 0; i < entryCount(); i++)
	{
		FileBase& file = dynamic_cast <FileBase&> ((*this)[i]);

		if(file.path().filename() == name)
			return &((*this)[i]);
	}

	return nullptr;
}

void Directory::addEntry(const std::filesystem::directory_entry& entry)
{
	if(entry.is_directory())
		add <Directory> (entry.path(), inotifyRegister);

	else add <File> (entry.path());
}

void Directory::readFiles()
{
	if(initialized)
		return;

	for(auto& entry : std::filesystem::directory_iterator(path()))
		addEntry(entry);

	inotifyRegister(*this);
	initialized = true;
}
