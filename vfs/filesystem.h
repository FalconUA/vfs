#ifndef __VIRTUAL_FILE_SYSTEM_FILESYSTEM__
#define __VIRTUAL_FILE_SYSTEM_FILESYSTEM__

#include <string>
#include "directory.h"
#include "file.h"

namespace virt {
	
	class filesystem {
	private:
		virt::fs::directory fs_root;

	public:
		filesystem();
		~filesystem();	

		class dir_iterator {
		private:
			dir_iterator();
			virt::filesystem* working_fs;
			virt::fs::directory* working_dir;	
		public:
			dir_iterator(virt::filesystem& fs, virt::fs::directory& dir);
			fs::directory* get_working_dir();
			bool move_to(std::string path);

			virt::filesystem::dir_iterator& operator= (const virt::filesystem::dir_iterator& c);
		};

		virt::filesystem::dir_iterator root();
		virt::filesystem::dir_iterator directory(std::string absolute_path);
	};	

} // end of namespace virt

#endif 
