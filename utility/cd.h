#ifndef __VIRTUAL_UTILITY_CD_HEADER__
#define __VIRTUAL_UTILITY_CD_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class cd: public virt::os::utility {
	public:
		cd(virt::operatingsystem* os):
				utility(os) {
			description = "Move into the directory in parameter. See \"help cd\" for more information.";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			sh->shell_iterator.move_to(param);
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
