#include <string>
#include <map>
#include <stack>
#include "directory.h"


virt::fs::directory::directory():
	parent(NULL), name("")
{
	subdir[""] = this;
	subdir["."] = this;
	subdir[".."] = this;
}

virt::fs::directory::directory(virt::fs::directory* dir_parent, std::string dir_name):
	parent(dir_parent), name(dir_name)
{
	subdir[""] = this;
	subdir["."] = this;
	subdir[".."] = this->parent;
}

virt::fs::directory::~directory(){
	for (std::map<std::string, virt::fs::directory*>::iterator it = subdir.begin();
			it != subdir.end(); it++)
		if ((*it).first != "." && (*it).first != ".." && (*it).first != "")
			delete (*it).second;
	for (std::map<std::string, virt::fs::file*>::iterator it = files.begin();
			it != files.end(); it++)
		delete (*it).second;
}

std::string virt::fs::directory::path(){
	std::stack<std::string> mark;
	virt::fs::directory* it = this;
	while (it->parent != NULL && it->parent != it){
		mark.push(it->name);
		it = it->parent;
	}
	std::string full_path("");
	while (!mark.empty()){
		full_path = full_path + mark.top() + "/";
		mark.pop();
	}
	return "/" + full_path;
}

std::string virt::fs::directory::get_name(){
	return name;
}

bool virt::fs::directory::has_child(std::string name){
	return (this->subdir.find(name) != this->subdir.end());
}

virt::fs::directory* virt::fs::directory::child_dir(std::string name){
	return this->subdir[name];
}

bool virt::fs::directory::add_subdir(std::string dirname, bool forced){
	if (!forced)
		if (subdir.find(dirname) != subdir.end())
			return false; 

	if (files.find(dirname) != files.end())
		return false;

	virt::fs::directory* new_subdir = new virt::fs::directory(this, dirname);
	this->remove_subdir(dirname);
	this->subdir[dirname] = new_subdir;
	return true;
}

void virt::fs::copy_content(virt::fs::directory* source, virt::fs::directory* destination){
	
	for (std::map<std::string, virt::fs::file*>::iterator it = source->files.begin(); 
			it != source->files.end(); it++)
		destination->add_file(it->second->get_name(), it->second->content, true);

	for (std::map<std::string, virt::fs::directory*>::iterator it = source->subdir.begin();
			it != source->subdir.end(); it++){
		if (it->first == "" || it->first == "." || it->first == "..")
			continue;

		destination->add_subdir(it->second->get_name(), false);
		virt::fs::copy_content(it->second, destination->subdir[it->second->name]);
	}
}

bool virt::fs::move_subdir(std::string dirname, virt::fs::directory* source, virt::fs::directory* destination){
	if (dirname == "" || dirname == "." || dirname == "..")
		return false;

	std::map<std::string, virt::fs::directory*>::iterator it = source->subdir.find(dirname);
	if (it == source->subdir.end())
		return false;

	virt::fs::directory* temp = (*it).second;

	destination->remove_subdir(dirname); 
	destination->subdir[dirname] = temp;

	source->subdir.erase(dirname);
	return true;
}

bool virt::fs::directory::remove_subdir(std::string dirname){
	std::map<std::string, virt::fs::directory*>::iterator it = subdir.find(dirname);
	if (it == subdir.end())
		return false;
	
	delete (*it).second;
	subdir.erase(dirname);
	return true;
}

bool virt::fs::directory::add_file(std::string filename, std::string content, bool forced){
	if (!forced)
		if (this->files.find(filename) != this->files.end())
			return false;

	if (this->subdir.find(filename) != this->subdir.end())
		return false;

	virt::fs::file* temp = new virt::fs::file(this, filename);
	temp->content = content;
	this->remove_file(filename);
	this->files[filename] = temp;
	return true;
}

bool virt::fs::directory::remove_file(std::string filename){
	std::map<std::string, virt::fs::file*>::iterator it = files.find(filename);
	if (it == files.end())
		return false;
	
	delete (*it).second;
	files.erase(filename);
	return true;

}
