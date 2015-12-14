#include <iostream>
#include <string>
#include <map>
#include "../virtualfs.h"
#include "operatingsystem.h"

virt::operatingsystem::operatingsystem() {}
virt::operatingsystem::~operatingsystem() {}

bool virt::operatingsystem::install_utility(std::string name, virt::os::utility* new_utility){
	if (utilities.find(name) != utilities.end())
		return false;

	utilities[name] = new_utility;
	return true;
}

bool virt::operatingsystem::remove_utility(std::string name){
	if (utilities.find(name) == utilities.end())
		return false;

	utilities.erase(name);
	return true;
}

virt::os::utility* virt::operatingsystem::app(std::string name){
	std::map<std::string, virt::os::utility*>::iterator it = utilities.find(name);
	if (it == utilities.end()){
		return NULL;
	}

	return utilities[name];
}

std::string virt::operatingsystem::launch_utility(std::string name, std::string commands){
	if (utilities.find(name) == utilities.end())
		return "";

	return utilities[name]->launch(commands);
}
