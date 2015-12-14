#ifndef __VIRTUAL_FILE_SYSTEM_ITERATOR__
#define __VIRTUAL_FILE_SYSTEM_ITERATOR__

#include <string>
#include "filesystem.h"
#include "directory.h"

namespace virt {
namespace fs {

	class iterator {
	private:
		iterator();

		virt::filesystem& working_fs;
		virt::fs::directory* working_dir;

	public:
		iterator(virt::filesystem& fs, virt::fs::directory* dir);
		iterator(virt::filesystem& fs, std::string path);

		fs::directory* get_working_dir();
		bool move_to(std::string path);
	};

} // end of namespace fs
} // end of namespace virt

#endif
