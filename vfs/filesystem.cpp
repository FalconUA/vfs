#include <string>
#include <sstream>
#include "filesystem.h"


virt::filesystem::filesystem(){}
virt::filesystem::~filesystem(){}

virt::filesystem::dir_iterator virt::filesystem::root(){
	return virt::filesystem::dir_iterator(*this, fs_root);
}

virt::filesystem::dir_iterator virt::filesystem::directory(std::string absolute_path){
	std::stringstream ss(absolute_path);
	std::string token;

	virt::filesystem::dir_iterator iterator = this->root();	
	iterator.move_to(absolute_path);
	return iterator;
}

virt::filesystem::dir_iterator::dir_iterator(virt::filesystem& fs, virt::fs::directory& dir):
	working_fs(&fs), working_dir(&dir) {}

virt::fs::directory* virt::filesystem::dir_iterator::get_working_dir(){
	return this->working_dir;
}

bool virt::filesystem::dir_iterator::move_to(std::string path){
	std::stringstream ss(path);
	std::string token;

	virt::filesystem::dir_iterator iterator = 
		(path[0] == '/')? (this->working_fs->root()) : (*this);
	

	while (std::getline(ss, token, '/')){
		if (token == "")
			continue;
		if (iterator.working_dir->has_child(token))
			iterator.working_dir = iterator.working_dir->child_dir(token);
		else 
			return false;
	}

	this->working_dir = iterator.working_dir;
	return true;
}

virt::filesystem::dir_iterator& virt::filesystem::dir_iterator::operator= 
		(const virt::filesystem::dir_iterator& c){
	if (this != &c){
		this->working_fs = c.working_fs;
		this->working_dir = c.working_dir;
	}
	return *this;
}

