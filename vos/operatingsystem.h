#ifndef __VIRT_OPERATING_SYSTEM_HEADER__
#define __VIRT_OPERATING_SYSTEM_HEADER__

#include <map>
#include <string>
#include "../virtualfs.h"
#include "utility.h"

namespace virt {

	class operatingsystem {
	public:
		std::map<std::string, virt::os::utility*> utilities;

		operatingsystem();
		~operatingsystem();

		virt::filesystem fs;

		// короче тут хотел впихнуть метапрограммисткие штучки типа
		// template <class T>
		// typename std::enable_if<std::is_base_of<your_base_class, T>::value, void>::type
		// т.к. будет меньше гемора с утечками памяти, 
		// но понял что это будет звездец как сложно объяснять
		bool install_utility(std::string name, virt::os::utility* new_utility);
		bool remove_utility(std::string name);

		virt::os::utility* app(std::string name);
		std::string launch_utility(std::string name, std::string commands);
	};

} // end of namespace virt

#endif
