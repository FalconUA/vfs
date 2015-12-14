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
			description = "Показывает эту инструкцию, или инструкцию для конкретного приложения в текущей виртуальной системе. Для детальной инструкции пропишите 'help help'\n";

			help_text = description + "Синтаксис: help [utility_name] без квадратных скобочек, где utility_name - название утилиты от которой хотите извлечь инструкцию. При пустом utility_name, данная команда покажет краткое описание всех установленных приложении в данной виртуальной системе.\n";
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
			if (param != ""){
				std::map<std::string, virt::os::utility*>::iterator it = 
					working_os->utilities.find(param);
				if (it != working_os->utilities.end())
					return working_os->utilities[param]->help_text + "\n";
			}
			
			for (std::map<std::string, virt::os::utility*>::iterator it = working_os->utilities.begin(); it != working_os->utilities.end(); it++){
				ss << std::endl << ">>>> " << it->first << std::endl;
			    ss << it->second->description;
			}

			ss << std::endl << ">>>> exit" << std::endl << "Выходит из текущего консоля." << std::endl << std::endl;

			return ss.str();
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
