#ifndef FILE_TREE_HH
#define FILE_TREE_HH

#include "Directory.hh"

#include <poll.h>
#include <termos/Menu.hh>

#include <unordered_map>

class FileTree : public Termos::Menu
{
public:
	FileTree(const std::filesystem::path& root);

private:
	void onUpdate(double delta) override;

	void watchDirectory(Directory& file);
	std::function <void(Directory&)> inotifyRegister;

	double elapsed;
	int inotify = 0;
	int inotifyMask = 0;

	pollfd pfd;
	std::unordered_map <int, Directory*> wds;
};

#endif
