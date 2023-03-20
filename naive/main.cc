#include <termos/TabbedView.hh>
#include <termos/Termos.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

#include <filesystem>

class FileBase
{
public:
	FileBase(const std::filesystem::path& path) : path(path)
	{
	}

	std::filesystem::path path;
};

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

class Directory : public Termos::Submenu, public FileBase
{
public:
	Directory(const std::filesystem::path& path) : Termos::Submenu(path.filename()), FileBase(path)
	{
		for(auto& entry : std::filesystem::directory_iterator(path))
		{
			if(entry.is_directory())
				add <Directory> (entry.path());

			else add <File> (entry.path());
		}
	}
};

class FileProperties : public Termos::Widget
{
public:

private:
};

int main()
{
	TermosUI ui(Termos::Split::Horizontally);
	
	auto& fileTree = ui.add <Termos::Menu> ();
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& properties = right.add <FileProperties> ();
	auto& debug = right.add <Termos::Logger> ();

	Termos::setDebugLogger(debug);
	fileTree.add <Directory> (".");

	fileTree.onSelect = [&properties](Termos::MenuEntry& entry)
	{
		FileBase& file = dynamic_cast <FileBase&> (entry);
		DBG_LOG("file", file.path.relative_path());
	};

	ui.run();
}
