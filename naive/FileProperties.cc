#include "FileProperties.hh"

#include <cstdlib>
#include <fstream>

void FileProperties::show(FileBase& file)
{
	selected = &file;
	render();
}

void FileProperties::onRender(Termos::Render& render)
{
	if(!selected)
		return;

	std::string fileType = selected->is_directory() ? "directory" : "file";
	render.text("Properties for " + fileType + selected->path().native(), 0, 0);
}
