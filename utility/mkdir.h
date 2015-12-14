#ifndef __VIRTUAL_UTILITY_MKDIR_HEADER__
#define __VIRTUAL_UTILITY_MKDIR_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class mkdir: public virt::os::utility {
	public:
		mkdir(virt::operatingsystem* os):
				utility(os) {
			description = "Создаёт папку с заданным именем в текущей папке. Для более детальной информации пропишите 'help mkdir'.\n";

			help_text = description + "Синтаксис: mkdir [foldername], где [foldername] (писать без квадратных скобочек) это название папки которую хотите создать. Будьте внимательны: не допускаются названия с символами '/' и ' ', а так же запрещаются названия '', '.', '..'!\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = static_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			if (param.find('/') != std::string::npos || param.find(' ') != std::string::npos)
				return ("Invalid character '/' or ' ' in filename");

			if (param == "" || param == "." || param == "..")
				return ("Invalid file name. See 'help mkdir' for more information");

			bool res = sh->shell_iterator.get_working_dir()->add_subdir(param, false);
			if (!res)
				return "Cannot create file: file already exists";
			return "";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
