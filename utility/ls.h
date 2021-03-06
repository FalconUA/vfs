#ifndef __VIRTUAL_UTILITY_LS_HEADER__
#define __VIRTUAL_UTILITY_LS_HEADER__

#include <string>
#include <map>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class ls: public virt::os::utility {
	public:
		ls(virt::operatingsystem* os):
				utility(os) {
			description = "Выводит список всех файлов и папок в текущей папке. Для детальной информации пропишите 'help ls'.\n";

			help_text = description + "Синтаксис: ls - без дополнительных параметров. Обратите внимание, что папка '.' обозначает текущую папку, а папка '..' обозначает предыдущую. Для корня файловой системы '..' обращает в самого себя, т.е. в корень.\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			std::string ret = "";
			for (std::map<std::string, virt::fs::directory*>::iterator it = sh->shell_iterator.get_working_dir()->subdir.begin(); it != sh->shell_iterator.get_working_dir()->subdir.end(); it++)
				ret += it->first + "  ";
			for (std::map<std::string, virt::fs::file*>::iterator it = sh->shell_iterator.get_working_dir()->files.begin(); it != sh->shell_iterator.get_working_dir()->files.end(); it++)
				ret += it->first + "  ";

			ret += "\n";
			return ret;
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
