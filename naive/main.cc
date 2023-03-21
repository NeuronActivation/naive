#include "FileTree.hh"
#include "Directory.hh"
#include "FileProperties.hh"

#include <termos/Termos.hh>
#include <termos/Debug.hh>

int main()
{
	TermosUI ui(Termos::Split::Horizontally);
	
	auto& fileTree = ui.add <FileTree> (".");
	auto& right = ui.add <Termos::View> (Termos::Split::Vertically);

	auto& properties = right.add <FileProperties> ();
	auto& debug = right.add <Termos::Logger> ();

	Termos::setDebugLogger(debug);

	fileTree.onSelect = [&properties](Termos::MenuEntry& entry)
	{
		FileBase& file = dynamic_cast <FileBase&> (entry);
		properties.show(file);
	};

	ui.run();
}
