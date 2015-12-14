#include <string>
#include "directory.h"
#include "file.h"

virt::fs::file::file():
	parent(NULL), name(""), content("") {};
virt::fs::file::file(virt::fs::directory* dir_parent, std::string file_name):
	parent(dir_parent), name(file_name), content("") {};

std::string virt::fs::file::path(){
	return parent->path() + name;
}

std::string virt::fs::file::get_name(){
	return name;
}
