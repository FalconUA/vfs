#ifndef __VIRTUAL_FILE_SYSTEM_DIRECTORY__
#define __VIRTUAL_FILE_SYSTEM_DIRECTORY__

#include <map>
#include <string>
#include "file.h"

namespace virt {
namespace fs {

	class file;

	class directory {
	protected:
		virt::fs::directory* parent;
		std::string name;

		friend void copy_content(virt::fs::directory* source, virt::fs::directory* destination);
		friend bool move_subdir
			(std::string dirname, virt::fs::directory* source, virt::fs::directory* destination);

	public:

		std::map<std::string, virt::fs::directory*> subdir;
		std::map<std::string, virt::fs::file*> files;

		directory();
		directory(directory* dir_parent, std::string dir_name);
		~directory();
		
		std::string path();
		std::string get_name();

		bool has_child(std::string childname);
		virt::fs::directory* child_dir(std::string childname);

		bool add_subdir(std::string dirname, bool forced=false);		
		bool remove_subdir(std::string dirname);

		bool add_file(std::string filename, std::string content="", bool forced=false);
		bool remove_file(std::string filename);
	};


	void copy_content(virt::fs::directory* source, virt::fs::directory* destination);
	bool move_subdir(std::string dirname, 
		virt::fs::directory* source, virt::fs::directory* destination);

} // end of namespace fs
} // end of namespace virt

#endif
