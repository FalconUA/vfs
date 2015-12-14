#ifndef __VIRTUAL_FILE_SYSTEM_FILE__
#define __VIRTUAL_FILE_SYSTEM_FILE__

#include <string>
#include "directory.h"

namespace virt {
namespace fs {

	class directory;

	class file {
	protected:
		virt::fs::directory* parent;
		std::string name;
	public:
		file();
		file(virt::fs::directory* dir_parent, std::string file_name);

		std::string path();
		std::string get_name();

		std::string content;
	};

} // end of namespace fs
} // end of namespace virt

#endif
