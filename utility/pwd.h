#ifndef __VIRTUAL_UTILITY_PWD_HEADER__
#define __VIRTUAL_UTILITY_PWD_HEADER__

#include <string>
#include "../virtualfs.h"
#include "../virtualos.h"
#include "shell.h"

namespace virt {
namespace util {

	class pwd: public virt::os::utility {
	public:
		pwd(virt::operatingsystem* os):
				utility(os) {
			description = "Выводит полный путь от корня файловой системы до текущей папки. Для детальной информации пропишите 'help pwd'.\n";

			help_text = description + "Синтаксис: pwd - без параметров. Папка '/' означает корневой каталог файловой системы.\n";
		}

		std::string launch(std::string param){
			virt::util::shell* sh;
			if ((sh = dynamic_cast<virt::util::shell*>(working_os->app("shell"))) == NULL)
				return "ERROR: No module named \"shell\" found!";

			while (param[0] == ' ')
				param.erase(0, 1);
			while (param[param.length()-1] == ' ')
				param.erase(param.length()-1, 1);

			return sh->shell_iterator.get_working_dir()->path() + "\n";
		}
	};

} // end of namespace util
} // end of namespace virt

#endif
