#ifndef __VIRTUAL_OPERATING_SYSTEM_UTILITY_HEADER__
#define __VIRTUAL_OPERATING_SYSTEM_UTILITY_HEADER__

#include <string>
#include "operatingsystem.h"
#include "../virtualfs.h"

namespace virt {

	class operatingsystem;

namespace os {

	class utility {
	protected:
		utility();
		virt::operatingsystem* working_os;

	public:
		std::string description;
		std::string help_text;

		utility(virt::operatingsystem* os):
			working_os(os){};
		virtual std::string launch(std::string param) = 0;
	};

} // end of namespace os
} // end of namespace virt

#endif
