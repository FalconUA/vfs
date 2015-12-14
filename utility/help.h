#ifndef __VIRTUAL_UTILITY_HELP_HEADER__
#define __VIRTUAL_UTILITY_HELP_HEADER__

#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class help: public virt::os::utility {
	public:
		help(virt::operatingsystem* os):
				utility(os) {
			description = "Showing this help. See \"help help\" for more information.";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			std::stringstream ss;
			for (std::map<std::string, virt::os::utility*>::iterator it = working_os->utilities.begin(); it != working_os->utilities.end(); it++){
				ss << std::endl << std::setw(10) << it->first << " - ";
			    ss << it->second->description << std::endl;
			}

			return ss.str();
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
