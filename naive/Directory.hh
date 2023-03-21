#ifndef DIRECTORY_HH
#define DIRECTORY_HH

#include "FileBase.hh"
#include "File.hh"

#include <sys/inotify.h>
#include <termos/Submenu.hh>

#include <functional>

class Directory : public Termos::Submenu, public FileBase
{
public:
	Directory(	const std::filesystem::path& path,
				std::function <void(Directory&)>& inotifyRegister);

	void handleEvent(inotify_event* event);

private:
	void readFiles();

	void addEntry(const std::filesystem::directory_entry& path);
	Termos::MenuEntry* findEntry(const char* name);

	std::function <void(Directory&)>& inotifyRegister;
	bool initialized = false;
};

#endif
