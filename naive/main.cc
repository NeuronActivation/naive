#include "Directory.hh"
#include "FileProperties.hh"

#include <termos/Termos.hh>
#include <termos/Debug.hh>
#include <termos/Menu.hh>

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
