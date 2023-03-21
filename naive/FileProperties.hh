#ifndef FILE_PROPERTIES_HH
#define FILE_PROPERTIES_HH

#include "FileBase.hh"

#include <termos/Widget.hh>

class FileProperties : public Termos::Widget
{
public:
	void show(FileBase& file);

	void onRender(Termos::Render& render) override;

private:
	FileBase* selected = nullptr;
};

#endif
