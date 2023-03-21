#include "FileTree.hh"

#include <termos/Debug.hh>
#include <sys/inotify.h>
#include <unistd.h>

#include <climits>

FileTree::FileTree(const std::filesystem::path& root)
{
	inotifyRegister = std::bind(&FileTree::watchDirectory, this, std::placeholders::_1);
	add <Directory> (root, inotifyRegister);
}

void FileTree::watchDirectory(Directory& file)
{
	if(inotify == 0)
	{
		inotify = inotify_init();
		inotifyMask = IN_CREATE | IN_DELETE;

		if(inotify < 0)
		{
			DBG_LOG("iinotify_init failed");
			return;
		}

		pfd.fd = inotify;
		pfd.events = POLLIN;
	}

	if(inotify <= 0)
		return;

	int wd = inotify_add_watch(inotify, file.path().relative_path().c_str(), inotifyMask);
	
	if(wd <= 0)
	{
		DBG_LOG("inotify_add_watch failed for", file.path());
		return;
	}

	wds[wd] = &file;
}

void FileTree::onUpdate(double delta)
{
	if(inotify <= 0)
		return;

	elapsed += delta;
	if(elapsed >= 1)
	{
		if(poll(&pfd, 1, 0) > 0)
		{
			constexpr size_t bufMax = (10 * (sizeof(inotify_event) + NAME_MAX + 1));
			char buffer[bufMax] __attribute__ ((aligned(8)));

			int numRead = read(inotify, buffer, bufMax);
			for (char* p = buffer; p < buffer + numRead;)
			{
				inotify_event* event = reinterpret_cast <inotify_event*> (p);
				auto directory = wds.find(event->wd);

				if(directory != wds.end())
					directory->second->handleEvent(event);

				p += sizeof(struct inotify_event) + event->len;
			}
		}

		elapsed = 0;
	}
}
